#ifndef GSLINTEGRATOR_H
#define GSLINTEGRATOR_H

#include <gsl/gsl_integration.h>


/*
INTEGRATION METHODS:

• QNG non-adaptive Gauss-Kronrod integration:			gives convergence error
• QAG adaptive integration:								works
• QAGS adaptive integration with singularities:			works
• QAGP adaptive integration with known singular points:	not implemented, no singularities in functions
• QAGI adaptive integration on infinite intervals:		not implemented, no infinite intervals
• QAWC adaptive integration for Cauchy principal values:not implemented, no singularities in functions
• QAWS adaptive integration for singular functions:		not implemented, no singularties at end of intervals
• QAWO adaptive integration for oscillatory functions:	not implemented, no oscillatory factors in functions
• QAWF adaptive integration for Fourier integrals:		not implemented, no semi infinite intervals
• CQUAD doubly-adaptive integration:	  				works
• Fixed order Gauss-Legendre integration:    			works

*/



typedef struct{
	double result;
	double error;
	size_t nEvals;
}solution;

class GSLIntegrator{
public:
	GSLIntegrator(double(*)(double, void*));
	void setError(double);
	void setIntervals(size_t);
	double getError();
	size_t getIntervals();
	solution integrate(double, double, std::string);
	void setParams(void*);

private:
	gsl_function F;
	double error = 1e-7;
	size_t nIntervals = 1000;



};

#endif
