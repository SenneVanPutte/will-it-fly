#include <iostream>

#include "vtkCubeAxesActor.h"

#include "vtkVersion.h"
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph3D.h>
#include "vtkSmartPointer.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkMath.h"
#include "vtkSphereSource.h"

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkArrowSource.h"
#include "vtkCellDataToPointData.h"
#include "vtkPlaneSource.h"


#include "vtkStreamLine.h"
#include "vtkCellData.h"
#include "vtkCellCenters.h"
#include "vtkStructuredGrid.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkInteractorStyleImage.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"

#include "vtkStructuredGridWriter.h"
#include "vtkAssignAttribute.h"


vtkSmartPointer<vtkActor>  maakPunt(float x, float y)
{
	double startPoint[3];
	double scale = 0.05;
	startPoint[0] = x / scale;
	startPoint[1] = y / scale;
	startPoint[2] = 0;
	vtkSmartPointer<vtkSphereSource> sphereStartSource =
	    vtkSmartPointer<vtkSphereSource>::New();
	sphereStartSource->SetCenter(startPoint);
	vtkSmartPointer<vtkPolyDataMapper> sphereStartMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereStartMapper->SetInputConnection(sphereStartSource->GetOutputPort());
	vtkSmartPointer<vtkActor> sphereStart = vtkSmartPointer<vtkActor>::New();
	sphereStart->SetMapper(sphereStartMapper);
	sphereStart->GetProperty()->SetColor(1.0, 0.3, 0.3);
	sphereStart->SetScale(scale);
	return sphereStart;
}

void plotVector(float grens, int bin)
{
	std::cout << "Creating grid... " << std::endl;

	// grid dimensions
	static int dims[3] = { bin, bin , 1 };
	int size = dims[0] * dims[1] * dims[2];

	// vectors
	vtkSmartPointer< vtkFloatArray > vectors = vtkSmartPointer< vtkFloatArray >::New();
	vectors->SetNumberOfComponents(3);
	vectors->SetNumberOfTuples(size);

	// points
	vtkSmartPointer< vtkPoints > points = vtkSmartPointer< vtkPoints >::New();
	points->Allocate(size);

	// fill in data
	float x[3];
	float v[3];
	float stapgrootte = (2 * grens) / bin;
	std::cout << "x in [" << -grens << "," << grens << "]" << endl;
	std::cout << "y in [" << -grens << "," << grens << "]" << endl;
	std::cout << "stapgrootte: " << stapgrootte << endl;

	for(int j = 0; j < dims[1]; j++)
	{
		float jOffset = j * dims[0];

		for(int i = 0; i < dims[0]; i++)
		{
			x[0] = j * stapgrootte - (dims[1] / 2) * stapgrootte;
			x[1] = i * stapgrootte - (dims[0] / 2) * stapgrootte;
			v[0] = (x[0]);
			v[1] = (x[1]);
			x[2] = 0;
			v[2] = 0;
//            v[0] = (x[0]-(dims[0]/2)*stapgrootte)/sqrt(pow(x[0]-(dims[0]/2)*stapgrootte,2)+pow(x[1]-(dims[1]/2)*stapgrootte,2));
//            v[1] = (x[1]-(dims[1]/2)*stapgrootte)/sqrt(pow(x[0]-(dims[0]/2)*stapgrootte,2)+pow(x[1]-(dims[1]/2)*stapgrootte,2));
			float offset = i + jOffset;
			points->InsertPoint(offset , x);
			vectors->InsertTuple(offset , v);
		}
	}

	// combine into structured grid data set
	vtkSmartPointer< vtkStructuredGrid> grid =
	    vtkSmartPointer< vtkStructuredGrid>::New();
	grid->SetDimensions(dims);
	grid->SetPoints(points);
	grid->GetPointData()->SetVectors(vectors);

	//Write grid to file
	vtkSmartPointer< vtkStructuredGridWriter > gridwriter = vtkSmartPointer< vtkStructuredGridWriter >::New();
	gridwriter->SetInput(grid);
	gridwriter->SetFileName("./structuredGridVectorVeld.vtk");
	gridwriter->Update();

	//Arrow stuff

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

	vtkSmartPointer<vtkRenderer> renderer =
	    vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkPolyDataMapper> mapper =
	    vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(glyph3D->GetOutputPort());

	vtkSmartPointer<vtkActor> superquadricActor =
	    vtkSmartPointer<vtkActor>::New();
	superquadricActor->SetMapper(mapper);

	vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =
	    vtkSmartPointer<vtkCubeAxesActor>::New();
	cubeAxesActor->SetBounds(glyph3D->GetOutput()->GetBounds());
	cubeAxesActor->SetCamera(renderer->GetActiveCamera());


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

	renderer->AddActor2D(cubeAxesActor);
	renderer->AddActor2D(superquadricActor);
	renderer->AddActor2D(maakPunt(0, 0));
	renderer->ResetCamera();
	//renderer->GetActiveCamera()->Azimuth(0);
	//renderer->GetActiveCamera()->Elevation(0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
	    vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
	    vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkInteractorStyleImage> imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindow->GetInteractor()->SetInteractorStyle(imageStyle);

	renderWindow->Render();
	renderWindowInteractor->Start();
	//screenshot pakken
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(renderWindow);
	windowToImageFilter->SetMagnification(2); //set the resolution of the output image (3 times the current resolution of vtk render window)
	windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
	windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
	windowToImageFilter->Update();

	vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->SetFileName("printvanvtk.png");
	writer->Write();
	renderWindow->Render();
	renderer->ResetCamera();
	renderWindow->Render();
	renderWindowInteractor->Start();
	renderWindowInteractor->Start();

}

void plotStreamLines(float grens, int bin)
{
	/////////////////////////////////////////////
	/////////////WERKT NOG NIET//////////////////
	/////////////////////////////////////////////

	std::cout << "Creating grid... " << std::endl;

	// grid dimensions
	static int dims[3] = { bin, bin , 1 };
	int size = dims[0] * dims[1] * dims[2];

	// vectors
	vtkSmartPointer< vtkFloatArray > vectors = vtkSmartPointer< vtkFloatArray >::New();
	vectors->SetNumberOfComponents(3);
	vectors->SetNumberOfTuples(size);

	// points
	vtkSmartPointer< vtkPoints > points = vtkSmartPointer< vtkPoints >::New();
	points->Allocate(size);

	// fill in data
	float x[3];
	float v[3];
	float stapgrootte = (2 * grens) / bin;
	std::cout << "x in [" << -grens << "," << grens << "]" << endl;
	std::cout << "y in [" << -grens << "," << grens << "]" << endl;
	std::cout << "stapgrootte: " << stapgrootte << endl;

	for(int j = 0; j < dims[1]; j++)
	{
		float jOffset = j * dims[0];

		for(int i = 0; i < dims[0]; i++)
		{
			x[0] = j * stapgrootte - (dims[1] / 2) * stapgrootte;
			x[1] = i * stapgrootte - (dims[0] / 2) * stapgrootte;
			v[0] = (x[0]);
			v[1] = (x[1]);
			x[2] = 0;
			v[2] = 0;
//            v[0] = (x[0]-(dims[0]/2)*stapgrootte)/sqrt(pow(x[0]-(dims[0]/2)*stapgrootte,2)+pow(x[1]-(dims[1]/2)*stapgrootte,2));
//            v[1] = (x[1]-(dims[1]/2)*stapgrootte)/sqrt(pow(x[0]-(dims[0]/2)*stapgrootte,2)+pow(x[1]-(dims[1]/2)*stapgrootte,2));
			float offset = i + jOffset;
			points->InsertPoint(offset , x);
			vectors->InsertTuple(offset , v);
		}
	}

	// combine into structured grid data set
	vtkSmartPointer< vtkStructuredGrid> grid =
	    vtkSmartPointer< vtkStructuredGrid>::New();
	grid->SetDimensions(dims);
	grid->SetPoints(points);
	grid->GetPointData()->SetVectors(vectors);

	//Write grid to file
	vtkSmartPointer< vtkStructuredGridWriter > gridwriter = vtkSmartPointer< vtkStructuredGridWriter >::New();
	gridwriter->SetInput(grid);
	gridwriter->SetFileName("./structuredGridVectorVeld.vtk");
	gridwriter->Update();

	//Starten met code voor de Streamlines.

	// Source of the streamlines
	vtkSmartPointer<vtkPlaneSource> seeds = vtkSmartPointer<vtkPlaneSource>::New();
	seeds->SetXResolution(4);
	seeds->SetYResolution(4);
	seeds->SetOrigin(2, -2, 26);
	seeds->SetPoint1(2, 2, 26);
	seeds->SetPoint2(2, -2, 32);

	//Vector Data is on the structured grid cell centers:
	vtkSmartPointer<vtkCellCenters> gridCellCenters = vtkSmartPointer<vtkCellCenters>::New();
	gridCellCenters->SetInput(grid);
	std::cout << "test" << std::endl;

	//SetAtrribute

//	vtkSmartPointer<vtkAssignAttribute> aa = vtkSmartPointer<vtkAssignAttribute>::New();
//	aa->SetInputConnection(gridCellCenters->GetOutputPort());
//	aa->Assign(vtkDataSetAttributes::SCALARS, vtkDataSetAttributes::VECTORS, vtkAssignAttribute::POINT_DATA);
//	gridCellCenters->SetInput(aa->GetOutput());
//	std::cout <<"test1" <<std::endl;


	// Streamline itself
	vtkSmartPointer<vtkStreamLine> streamLine = vtkSmartPointer<vtkStreamLine>::New();

	streamLine->SetInputConnection(gridCellCenters->GetOutputPort());
	streamLine->SetSource(seeds->GetOutput());

	std::cout << "test" << std::endl;

	//streamLine->SetStartPosition(2,-2,30);
	// as alternative to the SetSource(), which can handle multiple
	// streamlines, you can set a SINGLE streamline from
	// SetStartPosition()
	streamLine->SetMaximumPropagationTime(200);
	streamLine->SetIntegrationStepLength(.2);
	streamLine->SetStepLength(.001);
	streamLine->SetNumberOfThreads(1);
	streamLine->SetIntegrationDirectionToForward();
	streamLine->VorticityOn();

	std::cout << "test2" << std::endl;
	vtkSmartPointer<vtkPolyDataMapper> streamLineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	streamLineMapper->SetInputConnection(streamLine->GetOutputPort());

	vtkSmartPointer<vtkActor> streamLineActor = vtkSmartPointer<vtkActor>::New();
	streamLineActor->SetMapper(streamLineMapper);
	streamLineActor->VisibilityOn();

	// Create the RenderWindow, Renderer and Actors
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
	    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	renderer->AddActor(streamLineActor);

	// Add the actors to the renderer, set the background and size
	renderer->SetBackground(0.1, 0.2, 0.4);
	renderWindow->SetSize(300, 300);
	interactor->Initialize();
	std::cout << "test3" << std::endl;
	renderWindow->Render();

	interactor->Start();

}
//
//int main(int, char *[]) {
//	//Eerste argument: de grenzen van het grid (wordt symmetrisch rond (0,0) genomen, dus 1 geeft [-1,1] voor x en y.
//	//Tweede argument: aantal punten met een pijl.
//	plotVector(1,21);
//	//plotStreamLines(1,21);
//}
