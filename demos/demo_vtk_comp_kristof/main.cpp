#include <iostream>


#include "vtkStructuredGrid.h"
#include "vtkSmartPointer.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkMath.h"

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkHedgeHog.h"
#include "vtkGlyph2D.h"
#include "vtkArrowSource.h"

#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include <vtkStructuredGridOutlineFilter.h>

#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkTextProperty.h>
#include <vtkCaptionActor2D.h>

int main()
{

	std::cout << "Creating grid... " << std::endl;

	// grid dimensions
	static int dims[3] = { 21, 21 , 1 };
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
	float stapgrootte = 0.1;
	std::cout << dims[1] << endl;
	std::cout << dims[0] << endl;

	for(int j = 0; j < dims[1]; j++)
	{
		float jOffset = j * dims[0];

		for(int i = 0; i < dims[0]; i++)
		{
			x[0] = j * stapgrootte;
			x[1] = i * stapgrootte;
			v[0] = 2 * (x[0] - (dims[0] / 2) * stapgrootte);
			v[1] = 2 * (x[1] - (dims[1] / 2) * stapgrootte);
			float offset = i + jOffset;
			points->InsertPoint(offset , x);
			vectors->InsertTuple(offset , v);
		}
	}

	// combine into structured grid data set
	vtkSmartPointer< vtkStructuredGrid > grid =
	    vtkSmartPointer< vtkStructuredGrid >::New();
	grid->SetDimensions(dims);
	grid->SetPoints(points);
	grid->GetPointData()->SetVectors(vectors);

	std::cout << "Writing grid... " << std::endl;



	// Display data with hedgehogs
	// We create a simple pipeline to display the data.

	vtkHedgeHog * hedgehog = vtkHedgeHog::New();
	hedgehog->SetInput(grid);
	hedgehog->SetScaleFactor(0.1);
	/*
	vtkSmartPointer<vtkStructuredGridOutlineFilter> hedgehog =
	  vtkSmartPointer<vtkStructuredGridOutlineFilter>::New();
	hedgehog->SetInput(grid);
	*/
	//
	vtkPolyDataMapper * sgridMapper = vtkPolyDataMapper::New();
	sgridMapper->SetInputConnection(hedgehog->GetOutputPort());
	vtkActor * sgridActor = vtkActor::New();
	sgridActor->SetMapper(sgridMapper);
	sgridActor->GetProperty()->SetColor(0, 0, 0);

	// Display data with arrows

	// Setup the arrows
//    vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
//    arrowSource->Update();
//
//    vtkSmartPointer<vtkGlyph2D> glyphFilter = vtkSmartPointer<vtkGlyph2D>::New();
//    glyphFilter->SetSourceConnection(arrowSource->GetOutputPort());
//    glyphFilter->OrientOn();
//    glyphFilter->SetVectorModeToUseVector();
//    #if VTK_MAJOR_VERSION <= 5
//      glyphFilter->SetInputConnection(grid->GetProducerPort());
//    #else
//      glyphFilter->SetInputData(image);
//    #endif
//    glyphFilter->Update();

	// Create the usual rendering stuff
	vtkRenderer * renderer = vtkRenderer::New();
	vtkRenderWindow * renWin = vtkRenderWindow::New();
	renWin->AddRenderer(renderer);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
	    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();


	vtkRenderWindowInteractor * iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	iren->SetInteractorStyle(style);

	renderer->AddActor(sgridActor);
	vtkSmartPointer<vtkTextProperty> textProperty =
	    vtkSmartPointer<vtkTextProperty>::New();
	textProperty->SetFontSize(5);
	textProperty->SetColor(0, 0, 0);

	/*vtkSmartPointer<vtkTransform> transform =
	vtkSmartPointer<vtkTransform>::New();
	transform->Translate(-2.5, 2.5, 0.0);*/

	vtkSmartPointer<vtkAxesActor> axes =
	    vtkSmartPointer<vtkAxesActor>::New();
	vtkTextProperty * property = vtkTextProperty::New();



//Set the color to green and font to arial.

	property->SetColor(0, 0, 0);
	property->SetFontFamilyToArial();
	/*axes->SetUserTransform(transform);*/
	axes->GetXAxisShaftProperty()->SetColor(0, 0, 0);
	axes->GetYAxisShaftProperty()->SetColor(0, 0, 0);
	axes->GetXAxisTipProperty()->SetColor(0, 0, 0);
	axes->GetYAxisTipProperty()->SetColor(0, 0, 0);
	axes->GetXAxisCaptionActor2D()->SetCaptionTextProperty(property);
	axes->GetYAxisCaptionActor2D()->SetCaptionTextProperty(property);
	//axes->GetZAxisShaftProperty()->AxisLabelsOff();
	axes->SetTotalLength(1, 1, 0);
	//axes->SetPoint1(1,1,0);
	renderer->AddActor(axes);


	/*vtkSmartPointer<vtkAxesActor> axes =
	vtkSmartPointer<vtkAxesActor>::New();

	vtkSmartPointer<vtkOrientationMarkerWidget> widget =
	vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
	axes->SetTotalLength(1, 1, 0);
	widget->SetOrientationMarker( axes );
	widget->SetInteractor( iren );
	widget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
	widget->SetEnabled( 1 );
	widget->InteractiveOn();*/

	renderer->SetBackground(1, 1, 1);
	renderer->ResetCamera();
	//renderer->GetActiveCamera()->Elevation(60.0);
	//renderer->GetActiveCamera()->Azimuth(30.0);
	//renderer->GetActiveCamera()->Zoom(1.25);
	renWin->SetSize(1200, 1200);

	// interact with data
	renWin->Render();
	iren->Start();

	// end
	return 0;
}
