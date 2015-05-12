#include <algorithm>

#include "ROOTIntegrator.h"
#include <Math/GaussIntegrator.h>
#include <Math/GaussLegendreIntegrator.h>
#include <Math/WrappedTF1.h>

ROOTIntegrator::ROOTIntegrator(double(*integrationFunctiony)(double *, double *), int nParams)
{
	integrationFunction = new TF1("f", integrationFunctiony, 0, 1, nParams);
}

void ROOTIntegrator::setParameters(double * params)
{
	integrationFunction->SetParameters(params);
}

double ROOTIntegrator::integrate(double a, double b, std::string method)
{
	std::string lowerMethod = method;
	std::transform(lowerMethod.begin(), lowerMethod.end(), lowerMethod.begin(), ::tolower);

	ROOT::Math::WrappedTF1 wrapFunc(*integrationFunction);

	if(lowerMethod == "gi")
	{
		ROOT::Math::GaussIntegrator GI;
		GI.SetRelTolerance(error);
		GI.SetFunction(wrapFunc);
		return GI.Integral(a, b);
	}
	else if(lowerMethod == "gli")
	{
		ROOT::Math::GaussLegendreIntegrator GLI;
		GLI.SetRelTolerance(error);
		GLI.SetNumberPoints(nPoints);
		GLI.SetFunction(wrapFunc);
		return GLI.Integral(a, b);
	}
	else
	{
		std::cerr << "Method not recognized" << std::endl;
		return -1;
	}

}
