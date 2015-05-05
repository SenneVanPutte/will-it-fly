#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkContourFilter.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkLabeledDataMapper.h>
#include <vtkPlaneSource.h>
#include <vtkLookupTable.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkActor2D.h>

#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>

#include <vtkMath.h>

#include <vector>
#include <algorithm>

int main()
{
	int pointThreshold = 10;

	double xmin = -10, xmax = 10, ymin = -10, ymax = 10;
	int nx = 20, ny = 20, ncont = 20;

	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkContourFilter> contours = vtkSmartPointer<vtkContourFilter>::New();


	vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();
	plane->SetXResolution(nx);
	plane->SetYResolution(ny);
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

	for(int i = 0; i < plane->GetOutput()->GetNumberOfPoints(); i++)
	{
		pointys->GetPoint(i, vecy);
		veld->InsertNextTuple1(vecy[0]*vecy[0] + vecy[1]*vecy[1]);
		veldcomp.push_back(vecy[0]*vecy[0] + vecy[1]*vecy[1]);
	}

	double minimum = *std::min_element(veldcomp.begin(), veldcomp.end());
	double maximum = *std::max_element(veldcomp.begin(), veldcomp.end());
	//cout << "min/max: " << minimum << ", " << maximum << endl;
	plane->GetOutput()->GetPointData()->SetScalars(veld);
	polyData = plane->GetOutput();
	contours->SetInputConnection(plane->GetOutputPort());
	contours->GenerateValues(ncont, minimum, maximum);
	pointThreshold = 0;

	// Connect the segments of the conours into polylines
	vtkSmartPointer<vtkStripper> contourStripper = vtkSmartPointer<vtkStripper>::New();
	contourStripper->SetInputConnection(contours->GetOutputPort());
	contourStripper->Update();

	int numberOfContourLines = contourStripper->GetOutput()->GetNumberOfLines();

	std::cout << "There are "
	          << numberOfContourLines << " contours lines."
	          << std::endl;

	vtkPoints * points = contourStripper->GetOutput()->GetPoints();
	vtkCellArray * cells = contourStripper->GetOutput()->GetLines();
	vtkDataArray * scalars = contourStripper->GetOutput()->GetPointData()->GetScalars();

	// Create a polydata that contains point locations for the contour
	// line labels
	vtkSmartPointer<vtkPolyData> labelPolyData = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> labelPoints = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkDoubleArray> labelScalars = vtkSmartPointer<vtkDoubleArray>::New();
	labelScalars->SetNumberOfComponents(1);
	labelScalars->SetName("Isovalues");

	vtkIdType * indices;
	vtkIdType numberOfPoints;
	unsigned int lineCount = 0;

	for(cells->InitTraversal(); cells->GetNextCell(numberOfPoints, indices); lineCount++)
	{
		if(numberOfPoints < pointThreshold)
		{
			continue;
		}

		std::cout << "Line " << lineCount << ": " << std::endl;

		// Compute the point id to hold the label

		// Mid point or a random point
		vtkIdType midPointId = indices[numberOfPoints / 2];
		midPointId = indices[static_cast<vtkIdType>(vtkMath::Random(0, numberOfPoints))];
		//vtkMath::Random(0, numberOfPoints)
		double midPoint[3];
		points->GetPoint(midPointId, midPoint);//midPointId, midPoint
		std::cout << "\tmidPoint is " << midPointId << " with coordinate "
		          << "("
		          << midPoint[0] << ", "
		          << midPoint[1] << ", "
		          << midPoint[2] << ")"
		          << " and value " << scalars->GetTuple1(midPointId)
		          << std::endl;
		labelPoints->InsertNextPoint(midPoint);//midPoint
		labelScalars->InsertNextTuple1(scalars->GetTuple1(midPointId));//midPointId
	}

	labelPolyData->SetPoints(labelPoints);
	labelPolyData->GetPointData()->SetScalars(labelScalars);

	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contourStripper->GetOutputPort());
	contourMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> isolines = vtkSmartPointer<vtkActor>::New();
	isolines->SetMapper(contourMapper);

	vtkSmartPointer<vtkLookupTable> surfaceLUT = vtkSmartPointer<vtkLookupTable>::New();
	surfaceLUT->SetRange(polyData->GetPointData()->GetScalars()->GetRange());
	surfaceLUT->Build();

	vtkSmartPointer<vtkPolyDataMapper> surfaceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
	surfaceMapper->SetInput(polyData);
#else
	surfaceMapper->SetInputData(polyData);
#endif
	surfaceMapper->ScalarVisibilityOn();
	surfaceMapper->SetScalarRange(polyData->GetPointData()->GetScalars()->GetRange());
	surfaceMapper->SetLookupTable(surfaceLUT);

	vtkSmartPointer<vtkActor> surface = vtkSmartPointer<vtkActor>::New();
	surface->SetMapper(surfaceMapper);

	// The labeled data mapper will place labels at the points
	vtkSmartPointer<vtkLabeledDataMapper> labelMapper = vtkSmartPointer<vtkLabeledDataMapper>::New();
	labelMapper->SetFieldDataName("Isovalues");
#if VTK_MAJOR_VERSION <= 5
	labelMapper->SetInput(labelPolyData);
#else
	labelMapper->SetInputData(labelPolyData);
#endif
	labelMapper->SetLabelModeToLabelScalars();
	labelMapper->SetLabelFormat("%6.2f");

	vtkSmartPointer<vtkActor2D> isolabels = vtkSmartPointer<vtkActor2D>::New();
	isolabels->SetMapper(labelMapper);

	// Create a renderer and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	// Create an interactor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actors to the scene
	renderer->AddActor(isolines);
	renderer->AddActor(isolabels);
//  renderer->AddActor(surface);

	// Render the scene (lights and cameras are created automatically)
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
