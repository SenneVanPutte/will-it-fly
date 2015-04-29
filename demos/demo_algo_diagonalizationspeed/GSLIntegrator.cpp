#include <algorithm>
#include <iostream>

#include "GSLIntegrator.h"


GSLIntegrator::GSLIntegrator(double (*integrateFunction)(double, void*)){
	F.function = integrateFunction;
}

void GSLIntegrator::setError(double errorArg){
	error = errorArg;
}

double GSLIntegrator::getError(){
	return error;
}

void GSLIntegrator::setIntervals(size_t nIntervalsArg){
	nIntervals = nIntervalsArg;
}

size_t GSLIntegrator::getIntervals(){
	return nIntervals;
}

solution GSLIntegrator::integrate(double a, double b, std::string method){
	solution mySolution;
	std::string lowerMethod = method;
	std::transform(lowerMethod.begin(), lowerMethod.end(), lowerMethod.begin(), ::tolower);


	if (lowerMethod == "qng"){
		gsl_integration_qng(&F, a, b, 0, error, &mySolution.result, &mySolution.error, &mySolution.nEvals);
	}
	else if (lowerMethod == "qag"){
		int key = 6; //CHECK DOCUMENTATION, QAG HAS DIFFERENT ALGORITHMS
		gsl_integration_workspace *w = gsl_integration_workspace_alloc(nIntervals);
		gsl_integration_qag(&F, a, b, 0, error, w->limit, key, w, &mySolution.result, &mySolution.error);
		mySolution.nEvals = w->size;
		gsl_integration_workspace_free(w);
	}
	else if (lowerMethod == "qags"){
		gsl_integration_workspace *w = gsl_integration_workspace_alloc(nIntervals);
		gsl_integration_qags(&F, a, b, 0, error, w->limit, w, &mySolution.result, &mySolution.error);
		mySolution.nEvals = w->size;
		gsl_integration_workspace_free(w);
	}
	else if (lowerMethod == "cquad"){
		gsl_integration_cquad_workspace *w = gsl_integration_cquad_workspace_alloc(nIntervals);
		gsl_integration_cquad(&F, a, b, 0, error, w, &mySolution.result, &mySolution.error, &mySolution.nEvals);
		gsl_integration_cquad_workspace_free(w);
	}
	else if (lowerMethod == "gl"){
		gsl_integration_glfixed_table *w = gsl_integration_glfixed_table_alloc(nIntervals);
		mySolution.result = gsl_integration_glfixed(&F, a, b, w);
		gsl_integration_glfixed_table_free(w);
	}
	else{
		std::cerr << "Method not recognized" << std::endl;
	}

	return mySolution;
}


void GSLIntegrator::setParams(void* params){
	F.params = params;
}
