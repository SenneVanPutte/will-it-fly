#include "visualization_vtk.hpp"

namespace wif_viz
{


visualization_vtk_c::visualization_vtk_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	visualization_c(flow, min_range, max_range), actors(vtkSmartPointer<vtkActor>::New())
{
	//this-> actors = vtkSmartPointer<vtkActor>::New();
}


visualization_vtk_c::~visualization_vtk_c()
{
	//
}

visualization_vtk_c::set_velocityarrows(const vector_2d_c & bins)
{
	std::cout << "Creating grid... " << std::endl;

	// grid dimensions
	static int dims[3] = { bins.x, bins.y , 1 };
	int size = dims[0] * dims[1] * dims[2];

	// vectors
	vtkSmartPointer< vtkFloatArray > vectors = vtkSmartPointer< vtkFloatArray >::New();
	vectors->SetNumberOfComponents(3);
	vectors->SetNumberOfTuples(size);

	// points
	vtkSmartPointer< vtkPoints > points = vtkSmartPointer< vtkPoints >::New();
	points->Allocate(size);

	// fill in data
	vector_2d_c pos,vel;
	float x[3];
	float v[3];
	float stapgroottex = (2 * grens) / dims[0], stapgroottey = (2 * grens) / dims[1];
	std::cout << "x in [" << -grens << "," << grens << "]" << endl;
	std::cout << "y in [" << -grens << "," << grens << "]" << endl;
	std::cout << "stapgrootte: " << stapgrootte << endl;
	
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

	actors.push_back(cubeAxesActor);
	actors.push_back(superquadricActor);
	
	//renderer->AddActor2D(cubeAxesActor);
	//renderer->AddActor2D(superquadricActor);
	//renderer->AddActor2D(maakPunt(0,0));
	//renderer->ResetCamera();
	//renderer->GetActiveCamera()->Azimuth(0);
	//renderer->GetActiveCamera()->Elevation(0);
}

void visualization_vtk_c::draw(const std::string & filename)
{
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	
	for(std::vector<vtkSmartPointer<vtkActor>>::iterator it = actors.begin(); it != actors.end(); ++it) 
	{
		if ( it == actors.begin())
		{
			continue;
		}
		renderer->AddActor2D(*it);
	}
	
	renderer->ResetCamera();
	
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
	
	if (filename != "")
	{
		vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
		windowToImageFilter->SetInput(renderWindow);
		windowToImageFilter->SetMagnification(2); //set the resolution of the output image (3 times the current resolution of vtk render window)
		windowToImageFilter->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
		windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
		windowToImageFilter->Update();

		vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
		writer->SetInputConnection(windowToImageFilter->GetOutputPort());
		writer->SetFileName(filename);
		std::cout << "heyooo1" << endl;
		writer->Write();
		std::cout << "heyooo" << endl;
//		renderWindow->Render();
//		renderer->ResetCamera();
//		renderWindow->Render();
//		renderWindowInteractor->Start();
		renderWindowInteractor->Start();
	}
}


} // namespace wif_viz
