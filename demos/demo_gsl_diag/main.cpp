#include <stdio.h>
#include <cmath>
#include <ctime>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_integration.h>
#include <iostream>

using namespace std;

struct my_func_params
{
	double beta;
	double betaj;
	double xc;
	double yc;
	double xa;
	double ya;
};

double func(double s, void * p)
{
	struct my_func_params * params = (struct my_func_params *)p;
	double beta = (params->beta);
	double betaj = (params->betaj);
	double xc = (params->xc);
	double yc = (params->yc);
	double xa = (params->xa);
	double ya = (params->ya);
	double func = ((xc - (xa - s * sin(betaj))) * cos(beta) + (yc - (ya + s * cos(betaj))) * sin(beta))/(pow((xc - (xa - s * sin(betaj))), 2.) + pow((yc - (ya + s * cos(betaj))), 2.));
	/*double noemer = (pow((xc - (xa - s * sin(betaj))), 2.) + pow((yc - (ya + s * cos(betaj))), 2.));
	double func = teller / noemer;*/
	return func;
}

int main()
{
	double pi = 3.1415;

	//simple function
	//y=x
	//y=-2x+6
	//intersection: (y,x)=(2,2)
	/*double a_data_size
	double a_data[] = { 1, -1, 1, 2};

	double b_data[] = { 0, 6};

	gsl_matrix_view m
	    = gsl_matrix_view_array(a_data, 2, 2);

	gsl_vector_view b
	    = gsl_vector_view_array(b_data, 2);

	gsl_vector * x = gsl_vector_alloc(2);

	int s;

	gsl_permutation * p = gsl_permutation_alloc(2);

	gsl_linalg_LU_decomp(&m.matrix, p, &s);

	gsl_linalg_LU_solve(&m.matrix, p, &b.vector, x);

	printf("x = \n");
	gsl_vector_fprintf(stdout, x, "%g");

	gsl_permutation_free(p);
	gsl_vector_free(x);*/

	int n = 8;
	int m = 8;

	double U_inf = 1.;

	double a_data [n * m];
	double b_data [n];
	double beta_data [] = {0., pi / 4., pi / 2., 3. * pi / 4., pi, 5. * pi / 4., 3. * pi / 2., 7. * pi / 4.};
	double xa_data [] = {4., 4., 2., -2., -4., -4., -2., 2.};
	double ya_data [] = { -2., 2., 4., 4., 2., -2., -4., -4.};
	double xc_data [] = {4., 3., 0., -3., -4., -3., 0., 3.};
	double yc_data [] = {0., 3., 4., 3., 0., -3., -4., -3.};
	double s_0 = 0.;
	double s_1 [] = {4., 2. * pow(2., 0.5), 4., 2. * pow(2., 0.5), 4., 2. * pow(2., 0.5), 4., 2. * pow(2., 0.5)};

	gsl_matrix_view a
	    = gsl_matrix_view_array(a_data, n, m);

	gsl_function FUNC;
	FUNC.function = &func;

	double result, error;

	for(int i = 0; i < n; i++)
	{
		b_data[i] = -U_inf * cos(beta_data[i]);

		for(int j = 0; j < m; j++)
		{
			if(i == j)
			{
				gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, 0.5);

			}
			else
			{
				/*gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);

				struct my_func_params parameters = {beta_data[i],xc_data[i],yc_data[i],xa_data[i],ya_data[i]};

				FUNC.function = &func;
				FUNC.params = &parameters;

				gsl_integration_qags(&FUNC, s_0, s_1[i], 0, 1e-7, 1000, w, &result, &error);

				gsl_integration_workspace_free(w);

				gsl_matrix_set (&a.matrix,i,j,0.5/(2*pi)*result);*/



				struct my_func_params parameters = {beta_data[i], beta_data[j], xc_data[i], yc_data[i], xa_data[j], ya_data[j]};

				FUNC.params = &parameters;

				size_t nevals;
				gsl_integration_cquad_workspace * w1 = gsl_integration_cquad_workspace_alloc(1000);
				gsl_integration_cquad(&FUNC, s_0, s_1[j], 0., 1e-7, w1, &result, &error, &nevals);
				gsl_integration_cquad_workspace_free(w1);

				gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j,result/(2.*pi));






			}
		}
	}

	gsl_vector_view b
	   = gsl_vector_view_array(b_data, n);

	//printf("a = \n");
	//gsl_matrix_fprintf(stdout, &a.matrix, "%g");

	gsl_vector * x = gsl_vector_alloc(n);

	int q;

	gsl_permutation * p = gsl_permutation_alloc(n);

	gsl_linalg_LU_decomp(&a.matrix, p, &q);

	gsl_linalg_LU_solve(&a.matrix, p, &b.vector, x);



	printf("x = \n");
	gsl_vector_fprintf(stdout, x, "%g");



	gsl_permutation_free(p);
	gsl_vector_free(x);


	return 0;
}
