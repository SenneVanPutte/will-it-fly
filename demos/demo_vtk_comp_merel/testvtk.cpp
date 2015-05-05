#include "vtkDoubleArray.h"
#include "vtkImageData.h"
#include "vtkPoints.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredGridWriter.h"
#include "vtkImageWriter.h"
#include "vtkPointData.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkColorTransferFunction.h"
#include "vtkWriter.h"
#include "vtkCamera.h"
#include "vtkArrowSource.h"

#include<iostream>

vtkStructuredGrid * createGrid()
{

	int nx = 11;
	int ny = 11;
	int nz = 1;

	vtkPoints * points = vtkPoints::New();

	vtkDoubleArray * data1 = vtkDoubleArray::New();
	data1->SetNumberOfComponents(1);
	data1->SetName("myscalars");

	vtkDoubleArray * data2 = vtkDoubleArray::New();
	data2->SetNumberOfComponents(3);
	data2->SetName("myvectors");


	for(int iz = 0; iz < nz; iz++)
	{
		for(int iy = 0; iy < ny; iy++)
		{
			for(int ix = 0; ix < nx; ix++)
			{
				double x = ix - 5;
				double y = iy - 5;
				double f = x * x + y * y;
				double vx = 2 * x ;
				double vy = 2 * y ;

				points->InsertNextPoint(x, y, iz);
				data1->InsertNextValue(f);
				data2->InsertNextTuple3(0, 0, f); // "Tuple3" is for vector with 3 components
// vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
// arrowSource->Update();

			}
		}
	}

	vtkStructuredGrid * grid = vtkStructuredGrid::New();
	grid->SetDimensions(nx, ny, nz);
	grid->SetPoints(points);
	grid->GetPointData()->SetScalars(data1);
	grid->GetPointData()->SetVectors(data2);

	points->Delete();
	data1->Delete();
	data2->Delete();

	return grid;
}



int main()
{

	vtkStructuredGrid * sgrid = createGrid();

	vtkStructuredGridWriter * writer = vtkStructuredGridWriter::New();
	writer->SetFileName("output.vtk");
	writer->SetInput(sgrid);
	writer->Write();


	vtkColorTransferFunction * lut = vtkColorTransferFunction::New();
	double minvalue = 0;
	double maxvalue = 40;


	lut->AddRGBPoint(minvalue, 0, 0, 1);
	lut->AddRGBPoint(maxvalue, 1, 0, 0);
	lut->SetScaleToLog10();
	//lut->SetScale(40);

	// vtkDataSetMapper* mapper = vtkPolyDataMapper::New();
	vtkDataSetMapper * mapper = vtkDataSetMapper::New();
	mapper->SetInput(sgrid);
	mapper->SetLookupTable(lut);
	// mapper->SetScalarModeToUsePointFieldData();

	vtkActor * actor = vtkActor::New();
	actor->SetMapper(mapper);

	vtkRenderer * renderer = vtkRenderer::New();


	vtkRenderWindow * renWin = vtkRenderWindow::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(1000 , 1000);

	vtkInteractorStyleTrackballCamera * style = vtkInteractorStyleTrackballCamera::New();

	vtkRenderWindowInteractor * iren = vtkRenderWindowInteractor::New();

	iren->SetInteractorStyle(style);
	iren->SetRenderWindow(renWin);

	renderer->AddActor(actor);
	renderer->SetBackground(1  , 1 , 1);     // stelt de kleur van de achtergrond in
	renderer->ResetCamera();
	//renderer->GetActiveCamera()->Elevation(60.0);
	//renderer->GetActiveCamera()->Azimuth(30);
	//renderer->GetActiveCamera()->Zoom(1.25);

	renWin->Render();
	iren->Initialize();
	iren->Start();

	iren->Delete();
	style->Delete();
	renWin->Delete();
	renderer->Delete();
	actor->Delete();
	mapper->Delete();
	lut->Delete();
	writer->Delete();
	sgrid->Delete();


	return 0;
}
