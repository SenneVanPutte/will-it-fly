#include "visualization_vtk.hpp"
#include "visualization.hpp"

#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkAppendPolyData.h>
#include "vtkStructuredGridWriter.h"
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
/*
void visualization_vtk_c::set_velocityarrows(const vector_2d_c & bins)
{
	std::cout << "Creating grid... " << std::endl;

	int binsx = round(abs(bins.x));
	int binsy = round(abs(bins.y));

	// grid dimensions
	static int dims[3] = { binsx, binsy , 1 };
	int size = dims[0] * dims[1] * dims[2];

	// vectors
	vtkSmartPointer< vtkFloatArray > vectors = vtkSmartPointer< vtkFloatArray >::New();
	vectors->SetNumberOfComponents(3);
	vectors->SetNumberOfTuples(size);

	// points
	vtkSmartPointer< vtkPoints > points = vtkSmartPointer< vtkPoints >::New();
	points->Allocate(size);

	// fill in data
	double minx = min_range.x, maxx=max_range.x, miny=min_range.y, maxy=max_range.y;
	vector_2d_c pos,vel;
	float x[3];
	float v[3];
	float stapgroottex = (maxx - minx) / dims[0], stapgroottey = (maxy - miny) / dims[1];
	//std::cout << "x in [" << -grens << "," << grens << "]" << endl;
	//std::cout << "y in [" << -grens << "," << grens << "]" << endl;
	//std::cout << "stapgrootte: " << stapgrootte << endl;

	v[2] = 0;

	for(int j = 0; j < dims[1]; j++)
	{
		float jOffset = j * dims[0];

		for(int i = 0; i < dims[0]; i++)
		{
			pos.x = i * stapgroottex - (dims[0] / 2) * stapgroottex;
			pos.y = j * stapgroottey - (dims[1] / 2) * stapgroottey;
			//x[0] = i * stapgrootte - (dims[0] / 2) * stapgrootte;
			//x[1] = j * stapgrootte - (dims[1] / 2) * stapgrootte;
			vel = flow->get_velocity(pos);
			v[0] = vel.x;
			v[1] = vel.y;
//            v[0] = (x[0]-(dims[0]/2)*stapgrootte)/sqrt(pow(x[0]-(dims[0]/2)*stapgrootte,2)+pow(x[1]-(dims[1]/2)*stapgrootte,2));
//            v[1] = (x[1]-(dims[1]/2)*stapgrootte)/sqrt(pow(x[0]-(dims[0]/2)*stapgrootte,2)+pow(x[1]-(dims[1]/2)*stapgrootte,2));
			float offset = i + jOffset;
			points->InsertPoint(offset , pos.x, pos.y, 0);
			vectors->InsertTuple(offset , v);
		}
	}

	// combine into structured grid data set
	vtkSmartPointer< vtkPolyData> grid =
	    vtkSmartPointer< vtkPolyData>::New();
	//grid->SetDimensions( dims );
	grid->SetPoints(points);
	grid->GetPointData()->SetVectors(vectors);

	vtkSmartPointer<vtkArrowSource> arrowSource =
	    vtkSmartPointer<vtkArrowSource>::New();

	vtkSmartPointer<vtkGlyph3D> glyph3D =
	    vtkSmartPointer<vtkGlyph3D>::New();
	glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
	//glyph3D->SetVectorModeToUseVector();
#if VTK_MAJOR_VERSION <= 5
	glyph3D->SetInput(grid);
#else
	glyph3D->SetInputData(input);
#endif

	glyph3D->SetColorMode(2);
	glyph3D->SetScaleModeToScaleByVector();
	//glyph3D->OrientOff();
	glyph3D->SetScaleFactor(.1);
	glyph3D->Update();

//	double startPoint[3];
//	startPoint[0]=0;
//	startPoint[1]=0;
//	startPoint[2]=0;
//	vtkSmartPointer<vtkSphereSource> sphereStartSource =
//    vtkSmartPointer<vtkSphereSource>::New();
//    sphereStartSource->SetCenter(startPoint);
//  vtkSmartPointer<vtkPolyDataMapper> sphereStartMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//  sphereStartMapper->SetInputConnection(sphereStartSource->GetOutputPort());
//  vtkSmartPointer<vtkActor> sphereStart = vtkSmartPointer<vtkActor>::New();
//  sphereStart->SetMapper(sphereStartMapper);
//  sphereStart->GetProperty()->SetColor(1.0,0.3,0.3);
//  sphereStart->SetScale(0.05);

	//vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkPolyDataMapper> mapper =
	    vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(glyph3D->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
	    vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkActor> superquadricActor =
	    vtkSmartPointer<vtkActor>::New();
	superquadricActor->SetMapper(mapper);

	vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =
	    vtkSmartPointer<vtkCubeAxesActor>::New();
	cubeAxesActor->SetBounds(glyph3D->GetOutput()->GetBounds());
	//cubeAxesActor->SetCamera(renderer->GetActiveCamera());


	cubeAxesActor->DrawXGridlinesOff();
	cubeAxesActor->DrawYGridlinesOff();
	cubeAxesActor->DrawZGridlinesOff();
	cubeAxesActor->ZAxisLabelVisibilityOff();
#if VTK_MAJOR_VERSION > 5
	cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
#endif

	cubeAxesActor->XAxisMinorTickVisibilityOff();
	cubeAxesActor->YAxisMinorTickVisibilityOff();
	cubeAxesActor->ZAxisMinorTickVisibilityOff();

	actors.push_back(cubeAxesActor);
	actors.push_back(superquadricActor);

	//renderer->AddActor2D(cubeAxesActor);
	//renderer->AddActor2D(superquadricActor);
	//renderer->AddActor2D(maakPunt(0,0));
	//renderer->ResetCamera();
	//renderer->GetActiveCamera()->Azimuth(0);
	//renderer->GetActiveCamera()->Elevation(0);
}*/

uint32_t round_abs(double x)
{
	return std::round(std::abs(x));
}

bool one_is_zero(const vector_2d_c & vec)
{
	return (round_abs(vec.x) * round_abs(vec.y)) != 0;
}

void write_to_file(vtkSmartPointer<vtkStructuredGrid> grid, const std::string & name)
{
	vtkSmartPointer<vtkStructuredGridWriter> writer = vtkStructuredGridWriter::New();
	writer->SetFileName(name.c_str());
	writer->SetInput(grid);
	writer->Write();
}

void visualization_vtk_c::draw(const std::string & filename)
{
	//
	if(filename.c_str())
	{
		if(one_is_zero(psi_bins))
		{
			write_to_file(construct_psi_grid(), "psi-test.vtk");
		}

		if(one_is_zero(phi_bins))
		{
			write_to_file(construct_phi_grid(), "phi-test.vtk");
		}

		if(one_is_zero(velocity_bins))
		{
			write_to_file(construct_velocity_grid(), "velocity-test.vtk");
		}
	}
	else
	{
		//
	}

	return;


	if(velocity_bins.x != 0 && velocity_bins.y != 0)
	{
		std::cout << "test" << endl;
	}

	if(psi_bins.x != 0 && psi_bins.y)
	{
		int pointThreshold = 10;

		double xmin = min_range.x, xmax = max_range.x, ymin = min_range.y, ymax = max_range.y;
		int nx = round(abs(psi_bins.x)), ny = round(abs(psi_bins.y)), ncont = 20;

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

		for(int i = 0; i < plane->GetOutput()->GetNumberOfPoints(); i++)
		{
			double vecy[3];
			pointys->GetPoint(i, vecy);

			wif_core::vector_2d_c pos(vecy[0], vecy[1]);

			double val = flow->get_psi(pos);

			std::cout << pos << " " << val << std::endl;

			if(val > 500)
			{
				val = 1;
			}

			if(val < -500)
			{
				val = -1;
			}

			veld->InsertNextTuple1(val);//vecy[0]*vecy[0] + vecy[1]*vecy[1]);
			veldcomp.push_back(val);//vecy[0]*vecy[0] + vecy[1]*vecy[1]);
		}

		std::cout << "1" << std::endl;
		double minimum = *std::min_element(veldcomp.begin(), veldcomp.end());
		double maximum = *std::max_element(veldcomp.begin(), veldcomp.end());
		//cout << "min/max: " << minimum << ", " << maximum << endl;
		plane->GetOutput()->GetPointData()->SetScalars(veld);
		polyData = plane->GetOutput();
		//contours->SetInputConnection(plane->GetOutputPort());
		//contours->GenerateValues(ncont, minimum, maximum);
		pointThreshold = 0;






		// Read the file
		//vtkSmartPointer<vtkXMLPolyDataReader> reader =
		//vtkSmartPointer<vtkXMLPolyDataReader>::New();

		//reader->SetFileName( argv[1] );
		//reader->Update(); // Update so that we can get the scalar range


		double scalarRange[2];
		plane->GetOutput()->GetPointData()->GetScalars()->GetRange(scalarRange);

		vtkSmartPointer<vtkAppendPolyData> appendFilledContours =
		    vtkSmartPointer<vtkAppendPolyData>::New();

		int numberOfContours = ncont;

		double delta =
		    (scalarRange[1] - scalarRange[0]) /
		    static_cast<double>(numberOfContours - 1);
		std::cout << "2" << std::endl;
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

			vtkSmartPointer<vtkFloatArray> cd =
			    vtkSmartPointer<vtkFloatArray>::New();
			cd->SetNumberOfComponents(1);
			cd->SetNumberOfTuples(clippersHi[i]->GetOutput()->GetNumberOfCells());
			cd->FillComponent(0, valueLo);

			clippersHi[i]->GetOutput()->GetCellData()->SetScalars(cd);
			appendFilledContours->AddInputConnection(clippersHi[i]->GetOutputPort());
		}

		std::cout << "3" << std::endl;
		vtkSmartPointer<vtkCleanPolyData> filledContours =
		    vtkSmartPointer<vtkCleanPolyData>::New();
		filledContours->SetInputConnection(appendFilledContours->GetOutputPort());

		vtkSmartPointer<vtkLookupTable> lut =
		    vtkSmartPointer<vtkLookupTable>::New();
		lut->SetNumberOfTableValues(numberOfContours + 1);
		lut->Build();
		vtkSmartPointer<vtkPolyDataMapper> contourMapper =
		    vtkSmartPointer<vtkPolyDataMapper>::New();
		contourMapper->SetInputConnection(filledContours->GetOutputPort());
		contourMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
		contourMapper->SetScalarModeToUseCellData();
		contourMapper->SetLookupTable(lut);

		vtkSmartPointer<vtkActor> contourActor =
		    vtkSmartPointer<vtkActor>::New();
		contourActor->SetMapper(contourMapper);
		contourActor->GetProperty()->SetInterpolationToFlat();

		vtkSmartPointer<vtkContourFilter> contours =
		    vtkSmartPointer<vtkContourFilter>::New();
		contours->SetInputConnection(filledContours->GetOutputPort());
		contours->GenerateValues(numberOfContours, scalarRange[0], scalarRange[1]);

		vtkSmartPointer<vtkPolyDataMapper> contourLineMapperer =
		    vtkSmartPointer<vtkPolyDataMapper>::New();
		contourLineMapperer->SetInputConnection(contours->GetOutputPort());
		contourLineMapperer->SetScalarRange(scalarRange[0], scalarRange[1]);
		contourLineMapperer->ScalarVisibilityOff();
		std::cout << "4" << std::endl;
		vtkSmartPointer<vtkActor> contourLineActor =
		    vtkSmartPointer<vtkActor>::New();
		contourLineActor->SetMapper(contourLineMapperer);
		contourLineActor->GetProperty()->SetLineWidth(2);

		// The usual renderer, render window and interactor
		vtkSmartPointer<vtkRenderer> ren1 =
		    vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderWindow> renWin =
		    vtkSmartPointer<vtkRenderWindow>::New();
		vtkSmartPointer<vtkRenderWindowInteractor>
		iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

		ren1->SetBackground(.1, .2, .3);
		renWin->AddRenderer(ren1);
		iren->SetRenderWindow(renWin);

		// Add the actors
		ren1->AddActor(contourActor);
		ren1->AddActor(contourLineActor);
		std::cout << "5" << std::endl;
		// Begin interaction
		renWin->Render();
		iren->Start();
		std::cout << "6" << std::endl;
	}

	if(phi_bins.x != 0 && phi_bins.y)
	{

		int pointThreshold = 10;

		double xmin = min_range.x, xmax = max_range.x, ymin = min_range.y, ymax = max_range.y;
		int nx = round(abs(phi_bins.x)), ny = round(abs(phi_bins.y)), ncont = 20;

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
			//pointys->GetPoint(i,vecy);
			//veld = flow->get_psi(pos);
			double testval = flow->get_phi(pos);

			if(testval > 500)
			{
				testval = 1;
			}

			if(testval < -500)
			{
				testval = -1;
			}

			//std::cout << testval << std::endl;

			veld->InsertNextTuple1(testval);//vecy[0]*vecy[0] + vecy[1]*vecy[1]);
			veldcomp.push_back(testval);//vecy[0]*vecy[0] + vecy[1]*vecy[1]);
		}

		std::cout << "1" << std::endl;
		double minimum = *std::min_element(veldcomp.begin(), veldcomp.end());
		double maximum = *std::max_element(veldcomp.begin(), veldcomp.end());
		//cout << "min/max: " << minimum << ", " << maximum << endl;
		plane->GetOutput()->GetPointData()->SetScalars(veld);
		polyData = plane->GetOutput();
		//contours->SetInputConnection(plane->GetOutputPort());
		//contours->GenerateValues(ncont, minimum, maximum);
		pointThreshold = 0;






		// Read the file
		//vtkSmartPointer<vtkXMLPolyDataReader> reader =
		//vtkSmartPointer<vtkXMLPolyDataReader>::New();

		//reader->SetFileName( argv[1] );
		//reader->Update(); // Update so that we can get the scalar range


		double scalarRange[2];
		plane->GetOutput()->GetPointData()->GetScalars()->GetRange(scalarRange);

		vtkSmartPointer<vtkAppendPolyData> appendFilledContours =
		    vtkSmartPointer<vtkAppendPolyData>::New();

		int numberOfContours = ncont;

		double delta =
		    (scalarRange[1] - scalarRange[0]) /
		    static_cast<double>(numberOfContours - 1);
		std::cout << "2" << std::endl;
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

			vtkSmartPointer<vtkFloatArray> cd =
			    vtkSmartPointer<vtkFloatArray>::New();
			cd->SetNumberOfComponents(1);
			cd->SetNumberOfTuples(clippersHi[i]->GetOutput()->GetNumberOfCells());
			cd->FillComponent(0, valueLo);

			clippersHi[i]->GetOutput()->GetCellData()->SetScalars(cd);
			appendFilledContours->AddInputConnection(clippersHi[i]->GetOutputPort());
		}

		std::cout << "3" << std::endl;
		vtkSmartPointer<vtkCleanPolyData> filledContours =
		    vtkSmartPointer<vtkCleanPolyData>::New();
		filledContours->SetInputConnection(appendFilledContours->GetOutputPort());

		vtkSmartPointer<vtkLookupTable> lut =
		    vtkSmartPointer<vtkLookupTable>::New();
		lut->SetNumberOfTableValues(numberOfContours + 1);
		lut->Build();
		vtkSmartPointer<vtkPolyDataMapper> contourMapper =
		    vtkSmartPointer<vtkPolyDataMapper>::New();
		contourMapper->SetInputConnection(filledContours->GetOutputPort());
		contourMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
		contourMapper->SetScalarModeToUseCellData();
		contourMapper->SetLookupTable(lut);

		vtkSmartPointer<vtkActor> contourActor =
		    vtkSmartPointer<vtkActor>::New();
		contourActor->SetMapper(contourMapper);
		contourActor->GetProperty()->SetInterpolationToFlat();

		vtkSmartPointer<vtkContourFilter> contours =
		    vtkSmartPointer<vtkContourFilter>::New();
		contours->SetInputConnection(filledContours->GetOutputPort());
		contours->GenerateValues(numberOfContours, scalarRange[0], scalarRange[1]);

		vtkSmartPointer<vtkPolyDataMapper> contourLineMapperer =
		    vtkSmartPointer<vtkPolyDataMapper>::New();
		contourLineMapperer->SetInputConnection(contours->GetOutputPort());
		contourLineMapperer->SetScalarRange(scalarRange[0], scalarRange[1]);
		contourLineMapperer->ScalarVisibilityOff();
		std::cout << "4" << std::endl;
		vtkSmartPointer<vtkActor> contourLineActor =
		    vtkSmartPointer<vtkActor>::New();
		contourLineActor->SetMapper(contourLineMapperer);
		contourLineActor->GetProperty()->SetLineWidth(2);

		// The usual renderer, render window and interactor
		vtkSmartPointer<vtkRenderer> ren1 =
		    vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderWindow> renWin =
		    vtkSmartPointer<vtkRenderWindow>::New();
		vtkSmartPointer<vtkRenderWindowInteractor>
		iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();

		ren1->SetBackground(.1, .2, .3);
		renWin->AddRenderer(ren1);
		iren->SetRenderWindow(renWin);

		// Add the actors
		ren1->AddActor(contourActor);
		ren1->AddActor(contourLineActor);
		std::cout << "5" << std::endl;
		// Begin interaction
		renWin->Render();
		iren->Start();
		std::cout << "6" << std::endl;
	}

}

vtkSmartPointer<vtkPoints> visualization_vtk_c::construct_points(const vector_2d_c & binning) const
{
	uint32_t bin_x = round_abs(binning.x);
	uint32_t bin_y = round_abs(binning.y);

	uint32_t s = (bin_x + 1) * (bin_y + 1);

	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->Allocate(s);

	const vector_2d_c delta = max_range - min_range;
	const vector_2d_c delta_it(delta.x / bin_x, delta.y / bin_y);

	for(int i = 0; i <= bin_x; i++)
	{
		for(int j = 0; j <= bin_y; j++)
		{
			vector_2d_c pos(i * delta_it.x, j * delta_it.y);

			pos += min_range;

			points->InsertNextPoint(pos.x, pos.y, 0.0);
		}
	}

	return points;
}

vtkSmartPointer<vtkDoubleArray> visualization_vtk_c::construct_field(const vector_2d_c & binning, bool scalar) const
{
	uint32_t bin_x = round_abs(binning.x);
	uint32_t bin_y = round_abs(binning.y);

	vtkSmartPointer<vtkDoubleArray> vectors = vtkSmartPointer<vtkDoubleArray>::New();
	//vectors->Allocate((bin_x + 1) * (bin_y + 1));

	if(scalar)
	{
		vectors->SetNumberOfComponents(1);
		vectors->SetName("ScalarField");
	}
	else
	{
		vectors->SetNumberOfComponents(3);
		vectors->SetName("VelocityField");
	}

	return vectors;
}

vtkSmartPointer<vtkStructuredGrid> visualization_vtk_c::combine_grid(const vector_2d_c & binning, vtkSmartPointer<vtkPoints> points, vtkSmartPointer<vtkDoubleArray> field) const
{
	uint32_t bin_x = round_abs(binning.x);
	uint32_t bin_y = round_abs(binning.y);

	std::cout << "Test" << std::endl;
	vtkSmartPointer<vtkStructuredGrid> grid = vtkSmartPointer<vtkStructuredGrid>::New();

	grid->SetDimensions(bin_x + 1, bin_y + 1, 1);
	grid->SetPoints(points);

	if(field->GetNumberOfComponents() > 1)
	{
		grid->GetPointData()->SetVectors(field);
	}
	else
	{
		grid->GetPointData()->SetScalars(field);
	}

	std::cout << "Test2" << std::endl;

	return grid;
}

vtkSmartPointer<vtkStructuredGrid> visualization_vtk_c::construct_psi_grid() const
{
	vtkSmartPointer<vtkPoints> points = construct_points(psi_bins);
	vtkSmartPointer<vtkDoubleArray> field = construct_field(psi_bins, true);

	for(int i = 0; i < points->GetNumberOfPoints(); i++)
	{
		double x[3];

		points->GetPoint(i, x);

		const vector_2d_c pos(x[0], x[1]);

		double t = flow->get_psi(pos);

		//field->InsertNextTuple(&t);
		field->InsertNextValue(t);
	}

	return combine_grid(psi_bins, points, field);
}

vtkSmartPointer<vtkStructuredGrid> visualization_vtk_c::construct_phi_grid() const
{
	vtkSmartPointer<vtkPoints> points = construct_points(phi_bins);
	vtkSmartPointer<vtkDoubleArray> field = construct_field(phi_bins, true);

	for(int i = 0; i < points->GetNumberOfPoints(); i++)
	{
		double x[3];

		points->GetPoint(i, x);

		const vector_2d_c pos(x[0], x[1]);

		double t = flow->get_phi(pos);

		//field->InsertNextTuple1(t);
		field->InsertNextValue(t);
	}

	return combine_grid(phi_bins, points, field);
}

vtkSmartPointer<vtkStructuredGrid> visualization_vtk_c::construct_velocity_grid() const
{
	vtkSmartPointer<vtkPoints> points = construct_points(velocity_bins);
	vtkSmartPointer<vtkDoubleArray> field = construct_field(velocity_bins, false);

	for(int i = 0; i < points->GetNumberOfPoints(); i++)
	{
		double x[3];

		points->GetPoint(i, x);

		const vector_2d_c pos(x[0], x[1]);
		const vector_2d_c velo = flow->get_velocity(pos);
		double v[3] = {velo.x, velo.y, 0.0};

		std::cout << pos << std::endl;
		std::cout << velo << std::endl;

		field->InsertNextTuple(v);
	}

	return combine_grid(velocity_bins, points, field);
}


} // namespace wif_viz
