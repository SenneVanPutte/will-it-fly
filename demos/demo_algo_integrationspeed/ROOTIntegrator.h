#ifndef ROOTINTEGRATOR_H
#define ROOTINTEGRATOR_H

#include <TF1.h>


class ROOTIntegrator{

public:
	ROOTIntegrator(double(*)(double*, double*), int);
	void setParameters(double*);
	void setError(double);
	double integrate(double, double, std::string);
	void setNPoints(int);
private:
	TF1* integrationFunction;
	double error = 1e-7;
	int nPoints = 1000;


};



#endif
