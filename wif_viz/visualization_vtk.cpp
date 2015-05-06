#include "visualization_vtk.hpp"
#include "visualization.hpp"

#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkAppendPolyData.h>
#include <vtkClipPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkContourFilter.h>

#include <vtkFloatArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkScalarsToColors.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlaneSource.h>
#include <vtkDoubleArray.h>

#include <vtkStructuredGrid.h>
#include <vtkStructuredGridWriter.h>
#include <vtkImageWriter.h>

#include <vector>
#include <algorithm>

namespace wif_viz
{


visualization_vtk_c::visualization_vtk_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	visualization_c(flow, min_range, max_range), actors()
{
	//this-> actors = vtkSmartPointer<vtkActor>::New();
}


visualization_vtk_c::~visualization_vtk_c()
{
	//
}

void visualization_vtk_c::createGrid(int nX, int nY, bool psiorphi) //vtkSmartPointer<vtkStructuredGrid>
{

	double xmin = min_range.x, xmax = max_range.x, ymin = min_range.y, ymax = max_range.y;
	int nx = nX;
	int ny = nY;
	int nz = 1;

	double xscale = (xmax - xmin) / (nx);
	double yscale = (ymax - ymin) / (ny);

	wif_core::vector_2d_c pos;
	double f;

	vtkPoints * points = vtkPoints::New();

	vtkDoubleArray * data1 = vtkDoubleArray::New();
	data1->SetNumberOfComponents(1);
	data1->SetName("myscalars");

	for(int iz = 0; iz < nz; iz++)
	{
		for(int iy = 0; iy < ny; iy++)
		{
			for(int ix = 0; ix < nx; ix++)
			{
				double x = ix * xscale + xmin;
				double y = iy * yscale + ymin;
				pos.x = x;
				pos.y = y;

//flow->get_psi(pos);
				double vx = 2 * x ;
				double vy = 2 * y ;

				if(psiorphi == true)
				{
					f = flow->get_psi(pos);
				}
				else
				{
					f = flow->get_phi(pos);
				}

				points->InsertNextPoint(x, y, iz);
				data1->InsertNextValue(f);

			}
		}
	}

	vtkSmartPointer<vtkStructuredGrid> grid = vtkSmartPointer<vtkStructuredGrid>::New();
	grid->SetDimensions(nx, ny, nz);
	grid->SetPoints(points);
	grid->GetPointData()->SetScalars(data1);

	vtkSmartPointer<vtkStructuredGridWriter> writer = vtkSmartPointer<vtkStructuredGridWriter>::New();
	writer->SetFileName("grid.vtk");
	writer->SetInput(grid);
	writer->Write();

	points->Delete();
	data1->Delete();

	//return grid;
}


void visualization_vtk_c::contour_plot(bool psiorphi, int contlines)//true geeft psi, false geeft phi
{
	double xmin = min_range.x, xmax = max_range.x, ymin = min_range.y, ymax = max_range.y;
	int nx, ny, ncont = contlines;

	if(psiorphi == true)
	{
		nx = round(abs(psi_bins.x));
		ny = round(abs(psi_bins.y));
	}
	else
	{
		nx = round(abs(phi_bins.x));
		ny = round(abs(phi_bins.y));
	}

	int pointThreshold = 10;
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

	vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();
	plane->SetXResolution(nx);
	plane->SetYResolution(ny);

	std::cout << nx << ny << std::endl;

	plane->SetOrigin(xmin, ymin, 0);
	plane->SetPoint1(xmax, ymin, 0);
	plane->SetPoint2(xmin, ymax, 0);
	plane->Update();
	vtkPoints * pointys = plane->GetOutput()->GetPoints();

	vtkSmartPointer<vtkDoubleArray> veld = vtkSmartPointer<vtkDoubleArray>::New();
	veld->SetNumberOfComponents(1);
	veld->SetName("Isovalues");

	std::vector<double> veldcomp;
	double vecy[3];
	wif_core::vector_2d_c pos, vel;

	for(int i = 0; i < plane->GetOutput()->GetNumberOfPoints(); i++)
	{
		pointys->GetPoint(i, vecy);
		pos.x = vecy[0];
		pos.y = vecy[1];
		double testval = 0;

		if(psiorphi == true)
		{
			testval = flow->get_psi(pos);
		}
		else
		{
			testval = flow->get_phi(pos);
		}

		if(testval > 500)
		{
			testval = 1;
		}

		if(testval < -500)
		{
			testval = -1;
		}

		veld->InsertNextTuple1(testval);
		veldcomp.push_back(testval);
	}

	double minimum = *std::min_element(veldcomp.begin(), veldcomp.end());
	double maximum = *std::max_element(veldcomp.begin(), veldcomp.end());
	//cout << "min/max: " << minimum << ", " << maximum << endl;
	plane->GetOutput()->GetPointData()->SetScalars(veld);
	polyData = plane->GetOutput();
	//contours->SetInputConnection(plane->GetOutputPort());
	//contours->GenerateValues(ncont, minimum, maximum);
	pointThreshold = 0;

	double scalarRange[2];
	plane->GetOutput()->GetPointData()->GetScalars()->GetRange(scalarRange);

	vtkSmartPointer<vtkAppendPolyData> appendFilledContours = vtkSmartPointer<vtkAppendPolyData>::New();

	int numberOfContours = ncont;

	double delta =
	    (scalarRange[1] - scalarRange[0]) /
	    static_cast<double>(numberOfContours - 1);

	// Keep the clippers alive
	std::vector<vtkSmartPointer<vtkClipPolyData> > clippersLo;
	std::vector<vtkSmartPointer<vtkClipPolyData> > clippersHi;

	for(int i = 0; i < numberOfContours; i++)
	{
		double valueLo = scalarRange[0] + static_cast<double>(i) * delta;
		double valueHi = scalarRange[0] + static_cast<double>(i + 1) * delta;
		clippersLo.push_back(vtkSmartPointer<vtkClipPolyData>::New());
		clippersLo[i]->SetValue(valueLo);

		if(i == 0)
		{
			clippersLo[i]->SetInputConnection(plane->GetOutputPort());
		}
		else
		{
			clippersLo[i]->SetInputConnection(clippersHi[i - 1]->GetOutputPort(1));
		}

		clippersLo[i]->InsideOutOff();
		clippersLo[i]->Update();

		clippersHi.push_back(vtkSmartPointer<vtkClipPolyData>::New());
		clippersHi[i]->SetValue(valueHi);
		clippersHi[i]->SetInputConnection(clippersLo[i]->GetOutputPort());
		clippersHi[i]->GenerateClippedOutputOn();
		clippersHi[i]->InsideOutOn();
		clippersHi[i]->Update();

		if(clippersHi[i]->GetOutput()->GetNumberOfCells() == 0)
		{
			continue;
		}

		vtkSmartPointer<vtkFloatArray> cd = vtkSmartPointer<vtkFloatArray>::New();
		cd->SetNumberOfComponents(1);
		cd->SetNumberOfTuples(clippersHi[i]->GetOutput()->GetNumberOfCells());
		cd->FillComponent(0, valueLo);

		clippersHi[i]->GetOutput()->GetCellData()->SetScalars(cd);
		appendFilledContours->AddInputConnection(clippersHi[i]->GetOutputPort());
	}

	vtkSmartPointer<vtkCleanPolyData> filledContours = vtkSmartPointer<vtkCleanPolyData>::New();
	filledContours->SetInputConnection(appendFilledContours->GetOutputPort());

	vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	lut->SetNumberOfTableValues(numberOfContours + 1);
	lut->Build();
	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(filledContours->GetOutputPort());
	contourMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	contourMapper->SetScalarModeToUseCellData();
	contourMapper->SetLookupTable(lut);

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);
	contourActor->GetProperty()->SetInterpolationToFlat();

	vtkSmartPointer<vtkContourFilter> contours = vtkSmartPointer<vtkContourFilter>::New();
	contours->SetInputConnection(filledContours->GetOutputPort());
	contours->GenerateValues(numberOfContours, scalarRange[0], scalarRange[1]);

	vtkSmartPointer<vtkPolyDataMapper> contourLineMapperer = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourLineMapperer->SetInputConnection(contours->GetOutputPort());
	contourLineMapperer->SetScalarRange(scalarRange[0], scalarRange[1]);
	contourLineMapperer->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> contourLineActor = vtkSmartPointer<vtkActor>::New();
	contourLineActor->SetMapper(contourLineMapperer);
	contourLineActor->GetProperty()->SetLineWidth(2);

	// The usual renderer, render window and interactor
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderWindowInteractor>
	iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	ren1->SetBackground(.1, .2, .3);
	renWin->AddRenderer(ren1);
	iren->SetRenderWindow(renWin);

	// Add the actors
	ren1->AddActor(contourActor);
	ren1->AddActor(contourLineActor);

	// Begin interaction
	renWin->Render();
	iren->Start();

}

void visualization_vtk_c::draw(const std::string & filename)
{
	if(velocity_bins.x != 0 && velocity_bins.y != 0)
	{
		std::cout << "test" << endl;
	}

	if(psi_bins.x != 0 && psi_bins.y != 0)
	{
		contour_plot(true, 20);
	}

	if(phi_bins.x != 0 && phi_bins.y != 0)
	{
		contour_plot(false, 20);
	}

	createGrid(100, 100, true);

}


} // namespace wif_viz
