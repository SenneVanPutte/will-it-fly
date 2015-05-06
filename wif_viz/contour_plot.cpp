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
				testval = 1;
			if(testval < -500)
				testval = -1;
			
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
