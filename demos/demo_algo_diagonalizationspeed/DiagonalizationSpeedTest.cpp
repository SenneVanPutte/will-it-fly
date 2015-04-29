#include <iostream>
#include <cmath>
#include <ctime>


#include "GSLIntegrator.h"
#include "GSLDiagonalizer.h"
#include "ROOTDiagonalizer.h"



double panelFunctionGSL(double s,  void* params){
	double* myParams = (double*) params;
	double xCenteri = myParams[0];
	double yCenteri = myParams[1];
	double betaCurrenti = myParams[2];
	double betaOtherj = myParams[3];
	double xaOtherj = myParams[4];
	double yaOtherj = myParams[5];
	double panelF = ((xCenteri - (xaOtherj - s*sin(betaOtherj)))*cos(betaCurrenti) + (yCenteri - (yaOtherj + s*cos(betaOtherj)))*sin(betaCurrenti))/
					(pow(xCenteri - (xaOtherj - s*sin(betaOtherj)),2)+pow(yCenteri - (yaOtherj + s*cos(betaOtherj)),2));
	return panelF;
}

int main()
{
	double pi = 3.1415;

	// VERZONNEN WAARDEN: 8 PANELS IN OCTAGON STRUCTUUR OP CIRKEL MET STRAAL 4
	std::vector<double> xCenter = {4, 3, 0, -3, -4, -3, 0, 3};
	std::vector<double> yCenter = {0, 3, 4, 3, 0, -3, -4, -3};
	std::vector<double> beta = {0, pi/4, pi/2, 3*pi/4, pi, 5*pi/4, 3*pi/2, 7*pi/4};
	std::vector<double> xa = {4, 4, 2, -2, -4, -4, -2, 2};
	std::vector<double> ya = {-2, 2, 4, 4, 2, -2, -4, -4};
	std::vector<double> s = {4, 2*pow(2,0.5), 4, 2*pow(2,0.5), 4, 2*pow(2,0.5), 4, 2*pow(2,0.5)};

	//VERZONNEN SNELHEID UNIFORME FLOW
	double uInf = 1;

	int nRows = xCenter.size();
	int nColumns = xCenter.size();

	int nParams = 6;	//AANTAL PARAMETERS IN DE TE INTEGREREN FUNCTIE (te integreren parameter niet meegeteld !)
	double params[nParams];

	std::vector<double> Amatrix(nRows*nColumns);
	std::vector<double> bVec(nRows);

	std::string integrationMethodGSL;
	integrationMethodGSL = "qags"; //SNELSTE, ZIE INTEGRATION TESTS

	// Integralen
	GSLIntegrator myGSLIntegrator(panelFunctionGSL);

	for (int i = 0; i<nRows; i++){

		params[0] = xCenter[i];
		params[1] = yCenter[i];
		params[2] = beta[i];

		bVec[i] = -uInf*cos(beta[i]);

		for (int j = 0; j<nColumns; j++){
            if (i != j){
				params[3] = beta[j];
				params[4] = xa[j];
				params[5] = ya[j];

				myGSLIntegrator.setParams(params);

				Amatrix[i*nColumns + j] = myGSLIntegrator.integrate(0., s[j],integrationMethodGSL).result/(2.*pi);
            }
            else{
				Amatrix[i*nColumns+j] = 0.5;
            }
		}
	}




	GSLDiagonalizer myGSLDiagonalizer(Amatrix, bVec, nRows, nColumns);
	ROOTDiagonalizer myROOTDiagonalizer(Amatrix, bVec, nRows, nColumns);
	std::string diagMethod;
	std::vector<double> solutions;
	int nExecutions = 10000;
	std::clock_t start;

	std::cout << "GSL DIAGONALIZATION METHODS: " << std::endl;
	std::cout << "\n";

	diagMethod = "LU";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myGSLDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "QR";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myGSLDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "QRPT";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myGSLDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "SV";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myGSLDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "SVM";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myGSLDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "SVJ";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myGSLDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	std::cout<<"ROOT DIAGONALIZATION METHODS: " << std::endl;
	std::cout << "\n";

	diagMethod = "LU";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myROOTDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "QR";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myROOTDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	diagMethod = "SVD";
	start = std::clock();
	std::cout << "Method: " << diagMethod << std::endl;
	for (int i = 0; i < nExecutions; i++){
			solutions = myROOTDiagonalizer.diagonalize(diagMethod);
	}
	std::cout << "Result: ";
	for (int i = 0; i < nColumns; i++){
		std::cout << solutions[i] << "   ";
	}
	std::cout << "\n";
	std::cout << "Duration: " << (std::clock() - start)/(double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

    return 0;
}
