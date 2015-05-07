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
#include "vtkColorTransferFunction.h"
#include <vtkPolyDataMapper.h>
#include "vtkDataSetMapper.h"
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
	<<< <<< < HEAD
	grid->GetPointData()->SetScalars(data1);

	vtkSmartPointer<vtkStructuredGridWriter> writer = vtkSmartPointer<vtkStructuredGridWriter>::New();
	writer->SetFileName("grid.vtk");
	writer->SetInput(grid);
	writer->Write();
	== == == =
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
} * /

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
	if((filename.size() > 1) && (filename.find('.') == std::string::npos))
	{
		/// Enkel uitvoeren als de filename geen extensie heeft.

		if(one_is_zero(psi_bins))
		{
			write_to_file(construct_psi_grid(), filename + "-psi.vtk");
		}

		if(one_is_zero(phi_bins))
		{
			write_to_file(construct_phi_grid(), filename + "-phi.vtk");
		}

		if(one_is_zero(velocity_bins))
		{
			write_to_file(construct_velocity_grid(), filename + "-velocity.vtk");
		}
	}
	else
	{
		vtkSmartPointer<vtkRenderer> renderer = vtkRenderer::New();

		vtkSmartPointer<vtkRenderWindow> renWin = vtkRenderWindow::New();
		renWin->AddRenderer(renderer);
		renWin->SetSize(1000 , 1000);

		vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkInteractorStyleTrackballCamera::New();

		vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkRenderWindowInteractor::New();

		iren->SetInteractorStyle(style);
		iren->SetRenderWindow(renWin);

		renderer->SetBackground(0, 0, 0);     // stelt de kleur van de achtergrond in
		renderer->ResetCamera();

		renWin->AddRenderer(renderer);
		iren->SetRenderWindow(renWin);

		if(one_is_zero(psi_bins))
		{
			vtkSmartPointer<vtkStructuredGrid> psi_grid = construct_psi_grid();

			vtkSmartPointer<vtkDataSetMapper> mapperveld = vtkDataSetMapper::New();
			mapperveld->SetInput(psi_grid);

			vtkSmartPointer<vtkColorTransferFunction> lut = vtkColorTransferFunction::New();

			double values[2];

			psi_grid->GetPointData()->GetScalars()->GetRange(values);

			std::cout << values[0] << std::endl;

			lut->AddRGBPoint(values[0], 0, 0, 1);
			lut->AddRGBPoint(values[1], 1, 0, 0);

			mapperveld->SetLookupTable(lut);

			vtkSmartPointer<vtkActor> actorveld = vtkActor::New();
			actorveld->SetMapper(mapperveld);

			renderer->AddActor(actorveld);
		}

		if(one_is_zero(phi_bins))
		{
			vtkSmartPointer<vtkStructuredGrid> phi_grid = construct_phi_grid();

			vtkSmartPointer<vtkDataSetMapper> mapperveld = vtkDataSetMapper::New();
			mapperveld->SetInput(phi_grid);

			vtkSmartPointer<vtkColorTransferFunction> lut = vtkColorTransferFunction::New();
			double minvalue = -1;
			double maxvalue = 1;
			lut->AddRGBPoint(minvalue, 0, 0, 1);
			lut->AddRGBPoint(maxvalue, 1, 0, 0);

			mapperveld->SetLookupTable(lut);

			vtkSmartPointer<vtkActor> actorveld = vtkActor::New();
			actorveld->SetMapper(mapperveld);

			renderer->AddActor(actorveld);
		}

		if(one_is_zero(velocity_bins))
		{
			vtkSmartPointer<vtkStructuredGrid> velocity_grid = construct_velocity_grid();

			vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();

			vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
			glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
			//glyph3D->SetVectorModeToUseVector();
#if VTK_MAJOR_VERSION <= 5
			glyph3D->SetInput(velocity_grid);
#else
			glyph3D->SetInputData(input);
#endif

			glyph3D->SetColorMode(2);
			glyph3D->SetScaleModeToScaleByVector();
			//glyph3D->OrientOff();
			glyph3D->SetScaleFactor(.1);
			glyph3D->Update();



			vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			mapper->SetInputConnection(glyph3D->GetOutputPort());

			vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
			actor->SetMapper(mapper);
			actor->GetProperty()->SetRepresentationToSurface();

			renderer->AddActor(actor);
		}

		renWin->Render();
		iren->Initialize();
		iren->Start();

		iren->GetRenderWindow()->Finalize();

		// Stop the interactor
		iren->TerminateApp();
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
		>>> >>> > 505c8fedaac5f2b2c9337964f3d52386e1354b1f

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

		<<< <<< < HEAD

		for(int i = 0; i < plane->GetOutput()->GetNumberOfPoints(); i++)
		{
			pointys->GetPoint(i, vecy);
			pos.x = vecy[0];
			pos.y = vecy[1];
			double testval = 0;
			== == == =
			    double delta =
			        (scalarRange[1] - scalarRange[0]) /
			        static_cast<double>(numberOfContours - 1);
			std::cout << "2" << std::endl;
			// Keep the clippers alive
			std::vector<vtkSmartPointer<vtkClipPolyData> > clippersLo;
			std::vector<vtkSmartPointer<vtkClipPolyData> > clippersHi;
			>>> >>> > 505c8fedaac5f2b2c9337964f3d52386e1354b1f

			if(psiorphi == true)
			{
				testval = flow->get_psi(pos);
			}

			<<< <<< < HEAD
			else
			{
				testval = flow->get_phi(pos);
			}

			== == == =

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
			>>> >>> > 505c8fedaac5f2b2c9337964f3d52386e1354b1f

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

			<<< <<< < HEAD
			clippersHi.push_back(vtkSmartPointer<vtkClipPolyData>::New());
			clippersHi[i]->SetValue(valueHi);
			clippersHi[i]->SetInputConnection(clippersLo[i]->GetOutputPort());
			clippersHi[i]->GenerateClippedOutputOn();
			clippersHi[i]->InsideOutOn();
			clippersHi[i]->Update();
			== == == =
			    double delta =
			        (scalarRange[1] - scalarRange[0]) /
			        static_cast<double>(numberOfContours - 1);
			std::cout << "2" << std::endl;
			// Keep the clippers alive
			std::vector<vtkSmartPointer<vtkClipPolyData> > clippersLo;
			std::vector<vtkSmartPointer<vtkClipPolyData> > clippersHi;
			>>> >>> > 505c8fedaac5f2b2c9337964f3d52386e1354b1f

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

		<<< <<< < HEAD

		if(psi_bins.x != 0 && psi_bins.y != 0)
		{
			contour_plot(true, 20);
			== == == =
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
		>>> >>> > 505c8fedaac5f2b2c9337964f3d52386e1354b1f
	}

	if(phi_bins.x != 0 && phi_bins.y != 0)
	{
		contour_plot(false, 20);
	}

	createGrid(100, 100, true);

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

		field->InsertNextTuple(v);
	}

	return combine_grid(velocity_bins, points, field);
}


} // namespace wif_viz
