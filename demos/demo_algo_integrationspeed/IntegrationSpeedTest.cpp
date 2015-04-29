#include <iostream>
#include <cmath>
#include <ctime>


#include "GSLIntegrator.h"
#include "ROOTIntegrator.h"



double panelFunctionGSL(double s,  void * params)
{
	double * myParams = (double *) params;
	double xCenteri = myParams[0];
	double yCenteri = myParams[1];
	double betaCurrenti = myParams[2];
	double betaOtherj = myParams[3];
	double xaOtherj = myParams[4];
	double yaOtherj = myParams[5];
	double panelF = ((xCenteri - (xaOtherj - s * sin(betaOtherj))) * cos(betaCurrenti) + (yCenteri - (yaOtherj + s * cos(betaOtherj))) * sin(betaCurrenti)) /
	                (pow(xCenteri - (xaOtherj - s * sin(betaOtherj)), 2) + pow(yCenteri - (yaOtherj + s * cos(betaOtherj)), 2));
	return panelF;
}

double panelFunctionROOT(double * s,  double * params)
{
	double ss = s[0];
	double xCenteri = params[0];
	double yCenteri = params[1];
	double betaCurrenti = params[2];
	double betaOtherj = params[3];
	double xaOtherj = params[4];
	double yaOtherj = params[5];
	double panelF = ((xCenteri - (xaOtherj - ss * sin(betaOtherj))) * cos(betaCurrenti) + (yCenteri - (yaOtherj + ss * cos(betaOtherj))) * sin(betaCurrenti)) /
	                (pow(xCenteri - (xaOtherj - ss * sin(betaOtherj)), 2) + pow(yCenteri - (yaOtherj + ss * cos(betaOtherj)), 2));
	return panelF;
}

int main()
{
	double pi = 3.1415;

	// VERZONNEN WAARDEN: 8 PANELS IN OCTAGON STRUCTUUR OP CIRKEL MET STRAAL 4
	std::vector<double> xCenter = {4, 3, 0, -3, -4, -3, 0, 3};
	std::vector<double> yCenter = {0, 3, 4, 3, 0, -3, -4, -3};
	std::vector<double> beta = {0, pi / 4, pi / 2, 3 * pi / 4, pi, 5 * pi / 4, 3 * pi / 2, 7 * pi / 4};
	std::vector<double> xa = {4, 4, 2, -2, -4, -4, -2, 2};
	std::vector<double> ya = { -2, 2, 4, 4, 2, -2, -4, -4};
	std::vector<double> s = {4, 2 * pow(2, 0.5), 4, 2 * pow(2, 0.5), 4, 2 * pow(2, 0.5), 4, 2 * pow(2, 0.5)};

	int nParams = 6;	//AANTAL PARAMETERS IN DE TE INTEGREREN FUNCTIE (te integreren parameter niet meegeteld !)
	double params[nParams];

	params[0] = xCenter[0];
	params[1] = yCenter[0];
	params[2] = beta[0];
	params[3] = beta[1];
	params[4] = xa[1];
	params[5] = ya[1];

	double a = 0;
	double b = s[0];

	std::string integrationMethodGSL;

	std::string integrationMethodRoot;

	// Integralen
	GSLIntegrator myGSLIntegrator(panelFunctionGSL);
	myGSLIntegrator.setParams(params);
	ROOTIntegrator myROOTIntegrator(panelFunctionROOT, nParams);
	myROOTIntegrator.setParameters(params);


	double integrationResult;
	int nExecutions = 10000;
	std::clock_t start;

	std::cout << "GSL INTEGRATION METHODS: " << std::endl;
	std::cout << "\n";
	integrationMethodGSL = "CQUAD";
	start = std::clock();
	std::cout << "Method: " << integrationMethodGSL << std::endl;

	for(int i = 0; i < nExecutions; i++)
	{
		integrationResult = myGSLIntegrator.integrate(a, b, integrationMethodGSL).result;
	}

	std::cout << "Result: " << integrationResult << std::endl;
	std::cout << "Duration: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";


	integrationMethodGSL = "QAG";
	start = std::clock();
	std::cout << "Method: " << integrationMethodGSL << std::endl;

	for(int i = 0; i < nExecutions; i++)
	{
		integrationResult = myGSLIntegrator.integrate(a, b, integrationMethodGSL).result;
	}

	std::cout << "Result: " << integrationResult << std::endl;
	std::cout << "Duration: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";


	integrationMethodGSL = "QAGS";
	start = std::clock();
	std::cout << "Method: " << integrationMethodGSL << std::endl;

	for(int i = 0; i < nExecutions; i++)
	{
		integrationResult = myGSLIntegrator.integrate(a, b, integrationMethodGSL).result;
	}

	std::cout << "Result: " << integrationResult << std::endl;
	std::cout << "Duration: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";


	integrationMethodGSL = "GL";
	start = std::clock();
	std::cout << "Method: " << integrationMethodGSL << std::endl;

	for(int i = 0; i < nExecutions; i++)
	{
		integrationResult = myGSLIntegrator.integrate(a, b, integrationMethodGSL).result;
	}

	std::cout << "Result: " << integrationResult << std::endl;
	std::cout << "Duration: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	std::cout << "ROOT INTEGRATION METHODS: " << std::endl;
	std::cout << "\n";

	integrationMethodRoot = "GI";
	start = std::clock();
	std::cout << "Method: " << integrationMethodRoot << std::endl;

	for(int i = 0; i < nExecutions; i++)
	{
		integrationResult = myROOTIntegrator.integrate(a, b, integrationMethodRoot);
	}

	std::cout << "Result: " << integrationResult << std::endl;
	std::cout << "Duration: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";

	integrationMethodRoot = "GLI";
	start = std::clock();
	std::cout << "Method: " << integrationMethodRoot << std::endl;

	for(int i = 0; i < nExecutions; i++)
	{
		integrationResult = myROOTIntegrator.integrate(a, b, integrationMethodRoot);
	}

	std::cout << "Result: " << integrationResult << std::endl;
	std::cout << "Duration: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "\n";


	return 0;
}
