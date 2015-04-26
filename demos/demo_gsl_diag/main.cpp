#include <stdio.h>
#include <math.h>
#include <ctime>
#include <gsl/gsl_linalg.h>

using namespace std;

/*double func(double coord, vector<double> p)
{
	double s = coord;
	double x_c=(p[1])*cos(p[2]);
	double y_c=(p[1])*sin(p[2]));
	double x_a=(p[0]))*cos(p[2])-3.1415/8);
	double y_a=(p[0]))*sin(p[2])-3.1415/8);

	double P1=(x_c-(x_a-s*sin(p[2])))*cos(p[2])+(y_c-(y_a-s*cos(p[2])))*sin(p[2]);
	double P2=pow(x_c-(x_a-s*sin(p[2]),2)+pow(y_c-(y_a-s*cos(p[2])),2);
	return P1/P2;
}*/

int main()
{

	//y=x
	//y=-2x+6
	//intersection: (y,x)=(2,2)
	double a_data[] = { 1, -1, 1, 2};

	double b_data[] = { 0, 6};

	gsl_matrix_view m
	= gsl_matrix_view_array (a_data, 2, 2);

	gsl_vector_view b
	= gsl_vector_view_array (b_data, 2);

	gsl_vector *x = gsl_vector_alloc (2);

	int s;

	gsl_permutation * p = gsl_permutation_alloc (2);

	gsl_linalg_LU_decomp (&m.matrix, p, &s);

	gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);

	printf ("x = \n");
	gsl_vector_fprintf (stdout, x, "%g");

	gsl_permutation_free (p);
	gsl_vector_free (x);

	/*double n=8;
	double m=8;

	double U_inf=1;
	double R=1; //radius
	double r=R*(1+sqrt(2))/sqrt(4+2*sqrt(2)); //inradius

	double s_0=0;
	double s_1=R*2/sqrt(4+2*sqrt(2));

	vector<double> P;
	p.push_back(s_0);
	p.push_back(s_1);
	p.push_back(3.);//hoek beta

	double a_data[n*m];
	double b_data[n];

	gsl_matrix_view m
	= gsl_matrix_view_array (a_data, n, m);

	gsl_vector *x = gsl_vector_alloc (n);


	for (int i= 0; i < n; i++)
	{
		b[i]= -U_inf*cos(3.1415/4*i);

		gsl_matrix_set (gsl_matrix * m, size_t i, size_t j, func(,P);

		for (int j= 0; j < m; j++)
		{
			if (i==j)
			{
				A(i,j)=0.5;
			}
			else
			{
				gsl_matrix_set (m,i,j,0.5/TMath::Pi()*GI.Integral(s_0,s_1));
			}
		}
	}

	gsl_vector_view b
	= gsl_vector_view_array (b_data, n);



	*/
	return 0;
}
