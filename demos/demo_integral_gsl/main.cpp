#include <stdio.h>
#include <math.h>
#include <ctime>
#include <gsl/gsl_integration.h>

using namespace std;

double f(double x, void * params)
{
	double alpha = *(double *) params;
	double f = log(alpha * x) / sqrt(x);
	return f;
}

struct my_ff_params
{
	double a;
	double b;
	double c;
};

double ff(double x, void * p)
{
	struct my_ff_params * params = (struct my_ff_params *)p;
	double alpha = (params->a);
	double beta = (params->b);
	double gamma = (params->c);
	double ff = alpha * pow(x, 2) + beta * x + gamma;
	return ff;
}

struct my_velocity_params
{
	double d;
	double e;
	double f;
};

double velocity (double XI,void * p)
{
	struct my_velocity_params * params = (struct my_velocity_params *)p;
	double sigma = (params->d);
	double x = (params->e);
	double y = (params->f);
	double velocity = sigma/2/3.14*x/(pow(x,2)+pow(y-XI,2));
	return velocity;
}

int main()
{

	clock_t start;
	double duration;

	gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);  //Maakt plaats vrij voor intervallen

	double result, error;
	double alpha = 1.0;

	gsl_function F;
	F.function = &f;
	F.params = &alpha;

	start = clock();
	gsl_integration_qags(&F, 0, 1, 0, 1e-7, 1000, w, &result, &error);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	printf("result          = % .10f\n", result);
	printf("estimated error = % .10f\n", error);
	printf("intervals =  %d\n", w->size);
	printf("duration = %d\n", duration);

	gsl_integration_workspace_free(w);

	gsl_integration_workspace * ww = gsl_integration_workspace_alloc(1000);

	struct my_ff_params alpha2 = {1., 2., 3.};
	gsl_function FF;
	FF.function = &ff;
	FF.params = &alpha2;

	start = clock();
	gsl_integration_qags(&FF, 0, 1, 0, 1e-7, 1000, w, &result, &error);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	printf("result          = % .10f\n", result);
	printf("estimated error = % .10f\n", error);
	printf("intervals =  %d\n", ww->size);
	printf("duration = %d\n", duration);

	gsl_integration_workspace_free(ww);

	gsl_integration_workspace * w3 = gsl_integration_workspace_alloc (1000);

	struct my_velocity_params alpha3 = {1.,1.,1.};
	gsl_function VELOCITY;
	VELOCITY.function = &velocity;
	VELOCITY.params = &alpha3;

	start=clock();
	for(int i=0;i<1000;i++)
	{
		gsl_integration_qags (&VELOCITY, 0, 1, 0, 1e-7, 1000,w3, &result, &error);
	}
	duration = (clock()-start) / (double) CLOCKS_PER_SEC;

	printf ("result          = % .10f\n", result);
	printf ("estimated error = % .10f\n", error);
	printf ("intervals =  %d\n", w3->size);
	printf ("duration = %.18f\n", duration);

	gsl_integration_workspace_free (w3);


	return 0;
}
