#include "wif_algo.hpp"

#include <wif_core/wif_core.hpp>

namespace wif_algo
{


uint32_t get_version()
{
	wif_core::get_version();
	return 1;
}

struct integration_function_parameters
{
	double beta;
	double betaj;
	double xc;
	double yc;
	double xa;
	double ya;
};

double source_sheet_function(double s, void * parameters)
{
	struct integration_function_parameters * params = (struct integration_function_parameters *)parameters;
	double beta = (params->beta);
	double betaj = (params->betaj);
	double xc = (params->xc);
	double yc = (params->yc);
	double xa = (params->xa);
	double ya = (params->ya);
	double source_sheet_function = ((xc - (xa - s * sin(betaj))) * cos(beta) + (yc - (ya + s * cos(betaj))) * sin(beta)) / (pow((xc - (xa - s * sin(betaj))), 2.) + pow((yc - (ya + s * cos(betaj))), 2.));
	return source_sheet_function;
}

double vortex_sheet_function_1(double s, void * parameters)
{
	struct integration_function_parameters * params = (struct integration_function_parameters *)parameters;
	double beta = (params->beta);
	double betaj = (params->betaj);
	double xc = (params->xc);
	double yc = (params->yc);
	double xa = (params->xa);
	double ya = (params->ya);

	double a = sin(beta) * (xc - (xa - s * sin(betaj))) - cos(beta) * (yc - (ya + s * cos(betaj)));
	double b = pow(xc - (xa - s * sin(betaj)), 2) + pow(yc - (ya + s * cos(betaj)), 2);

	return a / b;
}

double vortex_sheet_function_2(double s, void * parameters)
{
	struct integration_function_parameters * params = (struct integration_function_parameters *)parameters;
	double beta = (params->beta);
	double betaj = (params->betaj);
	double xc = (params->xc);
	double yc = (params->yc);
	double xa = (params->xa);
	double ya = (params->ya);

	double a = cos(beta) * (xc - (xa - s * sin(betaj))) - sin(beta) * (yc - (ya + s * cos(betaj)));
	double b = pow(xc - (xa - s * sin(betaj)), 2) + pow(yc - (ya + s * cos(betaj)), 2);

	return a / b;
}

double v_t_function(double s, void * parameters)
{
	struct integration_function_parameters * params = (struct integration_function_parameters *)parameters;
	double beta = (params->beta);
	double betaj = (params->betaj);
	double xc = (params->xc);
	double yc = (params->yc);
	double xa = (params->xa);
	double ya = (params->ya);
	double v_t_function = ((xc - (xa - s * sin(betaj))) * -sin(beta) + (yc - (ya + s * cos(betaj))) * cos(beta)) / (pow((xc - (xa - s * sin(betaj))), 2.) + pow((yc - (ya + s * cos(betaj))), 2.));
	return v_t_function;
}

calculation_results_c calculate_flow(const wif_core::airfoil_c & myAirfoil, std::shared_ptr<wif_core::uniform_flow_c> myFlow, bool Kuta)
{
	calculation_results_c c;

	double pi = 3.1415;


	std::vector<wif_core::line_2d_c> mylines = myAirfoil.get_lines();

	unsigned int corners = mylines.size();


	std::vector<double> lengths;

	for(unsigned int i = 0; i < corners; i++)
	{
		wif_core::line_2d_c lineNow = mylines[i];
		lengths.push_back(lineNow.get_length());
	}

	std::vector<wif_core::vector_2d_c> centers;

	for(unsigned int i = 0; i < corners; i++)
	{
		wif_core::line_2d_c lineNow = mylines[i];
		centers.push_back(lineNow.get_center_point());
	}

	std::vector<wif_core::vector_2d_c> points_airfoil;
	points_airfoil = myAirfoil.get_points();

	std::vector<double> angles;

	for(unsigned int i = 0; i < corners; i++)
	{
		wif_core::line_2d_c lineNow = mylines[i];
		angles.push_back(lineNow.get_angle());
	}

	double U_inf = myFlow->get_strength();
	double angle_attack = myFlow->get_angle();
	double result, error;
	double s_0 = 0.;
	vector<double> c_p;
	double c_l;
	std::shared_ptr<wif_core::flow_accumulate_c> flow;
	size_t nevals;
	double v_t_i;

	//Check if one uses Kuta condition or not
	if(Kuta == false)
	{

		unsigned int n = corners;
		unsigned int m = corners;

		double a_data [n * m];
		double b_data [n];


		gsl_matrix_view a = gsl_matrix_view_array(a_data, n, m);

		gsl_function FUNC;
		FUNC.function = &source_sheet_function;

		//Setting matrix A and vector B to solve the system
		for(unsigned int i = 0; i < n; i++)
		{
			b_data[i] = -U_inf * cos(angles[i]) * cos(angle_attack) - U_inf * sin(angle_attack) * sin(angles[i]);

			for(unsigned int j = 0; j < m; j++)
			{
				if(i == j)
				{
					gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, 0.5);

				}
				else
				{
					struct integration_function_parameters parameters = {angles[i], angles[j], centers[i].x, centers[i].y, points_airfoil[j].x, points_airfoil[j].y};

					FUNC.params = &parameters;


					gsl_integration_cquad_workspace * w1 = gsl_integration_cquad_workspace_alloc(1000);
					gsl_integration_cquad(&FUNC, s_0, lengths[j], 0., 1e-7, w1, &result, &error, &nevals);
					gsl_integration_cquad_workspace_free(w1);

					gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, result / (2.*pi));

				}
			}
		}

		//Solve the system
		gsl_vector_view b
		    = gsl_vector_view_array(b_data, n);

		gsl_vector * x = gsl_vector_alloc(n);

		int q;

		gsl_permutation * p = gsl_permutation_alloc(n);

		gsl_linalg_LU_decomp(&a.matrix, p, &q);

		gsl_linalg_LU_solve(&a.matrix, p, &b.vector, x);

		std::vector<double> Sigma;

		for(unsigned int i = 0; i < n; i++)
		{
			Sigma.push_back(gsl_vector_get(x, i));
		}


		gsl_permutation_free(p);
		gsl_vector_free(x);

		//Calculating c_p
		gsl_function V_FUNC;
		V_FUNC.function = &v_t_function;

		for(unsigned int i = 0; i < corners; i++)
		{
			v_t_i = 0;

			for(unsigned int j = 0; j < corners; j++)
			{
				struct integration_function_parameters parameters = {angles[i], angles[j], centers[i].x, centers[i].y, points_airfoil[j].x, points_airfoil[j].y};

				V_FUNC.params = &parameters;

				gsl_integration_cquad_workspace * w2 = gsl_integration_cquad_workspace_alloc(1000);
				gsl_integration_cquad(&V_FUNC, s_0, lengths[j], 0., 1e-7, w2, &result, &error, &nevals);
				gsl_integration_cquad_workspace_free(w2);
				v_t_i = v_t_i + Sigma[j] / (2 * pi) * result;

			}

			c_p.push_back(-U_inf * sin(angles[i]) + v_t_i);
		}

		//calculating c_l
		c_l = 0;

		//Building return
		flow->add_flow(myFlow);
		flow->add_source_sheets(Sigma, myAirfoil);
		c.airfoil = myAirfoil;
		c.flow = flow;
		c.c_p = c_p;
		c.c_l = c_l;
	}
	else
	{
		unsigned int n = corners + 1;
		unsigned int m = corners + 1;
		double a_data [n * m];
		double b_data [n];
		double gamma = 1;
		int k = 0; //first panel
		int l = n - 1; //last panel

		gsl_matrix_view a
		    = gsl_matrix_view_array(a_data, n, m);

		gsl_function FUNC;
		FUNC.function = &source_sheet_function;

		//Fistr set matrix a and vector b
		for(unsigned int i = 0; i < n - 1; i++)
		{
			b_data[i] = -U_inf * cos(angles[i]) * cos(angle_attack) - U_inf * sin(angle_attack) * sin(angles[i]);

			for(unsigned int j = 0; j < m - 1; j++)
			{
				if(i == j)
				{
					gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, 0.5);

				}
				else
				{
					struct integration_function_parameters parameters = {angles[i], angles[j], centers[i].x, centers[i].y, points_airfoil[j].x, points_airfoil[j].y};

					FUNC.params = &parameters;


					gsl_integration_cquad_workspace * w3 = gsl_integration_cquad_workspace_alloc(1000);
					gsl_integration_cquad(&FUNC, s_0, lengths[j], 0., 1e-7, w3, &result, &error, &nevals);
					gsl_integration_cquad_workspace_free(w3);

					gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, result / (2.*pi));

				}
			}
		}

		gsl_function VORTEX1;
		VORTEX1.function = &vortex_sheet_function_1;

		//Set last row of matrix A
		for(unsigned int i = 0; i < n; i++)
		{
			unsigned int j = n - 1;

			struct integration_function_parameters parameters = {angles[i], angles[j], centers[i].x, centers[i].y, points_airfoil[j].x, points_airfoil[j].y};

			VORTEX1.params = &parameters;

			gsl_integration_cquad_workspace * w4 = gsl_integration_cquad_workspace_alloc(1000);
			gsl_integration_cquad(&VORTEX1, s_0, lengths[j], 0., 1e-7, w4, &result, &error, &nevals);
			gsl_integration_cquad_workspace_free(w4);

			gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, -0.5 * gamma / pi * result);
		}

		//Set last collumn of matrix A and set vector B
		for(unsigned int j = 0; j < n; j++)
		{
			unsigned int i = n - 1;

			b_data[i] = -U_inf * cos(angle_attack - angles[k]) - U_inf * cos(angle_attack - angles[l]);

			struct integration_function_parameters parameters = {angles[k], angles[j], centers[k].x, centers[k].y, points_airfoil[j].x, points_airfoil[j].y};

			VORTEX1.params = &parameters;

			gsl_integration_cquad_workspace * w5 = gsl_integration_cquad_workspace_alloc(1000);
			gsl_integration_cquad(&VORTEX1, s_0, lengths[j], 0., 1e-7, w5, &result, &error, &nevals);
			gsl_integration_cquad_workspace_free(w5);

			double result_temp = -0.5 / (pi) * result;

			parameters = {angles[l], angles[j], centers[l].x, centers[l].y, points_airfoil[j].x, points_airfoil[j].y};

			VORTEX1.params = &parameters;

			size_t nevals;
			gsl_integration_cquad_workspace * w6 = gsl_integration_cquad_workspace_alloc(1000);
			gsl_integration_cquad(&VORTEX1, s_0, lengths[j], 0., 1e-7, w6, &result, &error, &nevals);
			gsl_integration_cquad_workspace_free(w6);

			result_temp = result_temp - 0.5 / (pi) * result;

			gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, result_temp);

		}

		//Set last ellement of A

		int i = n - 1;
		int j = n - 1;


		gsl_function VORTEX2;
		VORTEX2.function = &vortex_sheet_function_2;

		struct integration_function_parameters parameters = {angles[k], angles[j], centers[k].x, centers[k].y, points_airfoil[j].x, points_airfoil[j].y};

		VORTEX2.params = &parameters;

		gsl_integration_cquad_workspace * w7 = gsl_integration_cquad_workspace_alloc(1000);
		gsl_integration_cquad(&VORTEX2, s_0, lengths[j], 0., 1e-7, w7, &result, &error, &nevals);
		gsl_integration_cquad_workspace_free(w7);

		double result_temp = -0.5 / (pi) * result;

		parameters = {angles[l], angles[j], centers[l].x, centers[l].y, points_airfoil[j].x, points_airfoil[j].y};

		VORTEX2.params = &parameters;

		size_t nevals;
		gsl_integration_cquad_workspace * w8 = gsl_integration_cquad_workspace_alloc(1000);
		gsl_integration_cquad(&VORTEX2, s_0, lengths[j], 0., 1e-7, w8, &result, &error, &nevals);
		gsl_integration_cquad_workspace_free(w8);

		result_temp = result_temp - 0.5 / (pi) * result;

		gsl_matrix_set(&a.matrix, (size_t) i, (size_t) j, result_temp);

		//Solve the system
		gsl_vector_view b
		    = gsl_vector_view_array(b_data, n);

		gsl_vector * x = gsl_vector_alloc(n);

		int q;

		gsl_permutation * p = gsl_permutation_alloc(n);

		gsl_linalg_LU_decomp(&a.matrix, p, &q);

		gsl_linalg_LU_solve(&a.matrix, p, &b.vector, x);

		std::vector<double> Sigma;

		for(unsigned int i = 0; i < n - 1; i++)
		{
			Sigma.push_back(gsl_vector_get(x, i));
		}

		double Gamma;
		Gamma = gsl_vector_get(x, n - 1);

		gsl_permutation_free(p);
		gsl_vector_free(x);

		//Calculate c_p
		gsl_function V_FUNC;
		V_FUNC.function = &v_t_function;

		double v_t_i;

		for(unsigned int i = 0; i < corners; j++)
		{
			v_t_i = 0;

			for(unsigned int j = 0; j < corners; j++)
			{
				struct integration_function_parameters parameters = {angles[i], angles[j], centers[i].x, centers[i].y, points_airfoil[j].x, points_airfoil[j].y};

				V_FUNC.params = &parameters;

				size_t nevals;
				gsl_integration_cquad_workspace * w1 = gsl_integration_cquad_workspace_alloc(1000);
				gsl_integration_cquad(&V_FUNC, s_0, lengths[j], 0., 1e-7, w1, &result, &error, &nevals);
				gsl_integration_cquad_workspace_free(w1);
				v_t_i = v_t_i + Sigma[j] / (2 * pi) * result;

			}

			c_p.push_back(-U_inf * sin(angles[i]) + v_t_i);
		}

		//Calculate c_l
		double ll = std::accumulate(lengths.begin(), lengths.end(), 0);
		double x_max = points_airfoil[0].x;
		double x_min = points_airfoil[0].x;

		for(unsigned int j = 1; j < points_airfoil.size(); j++)
		{
			if(points_airfoil[j].x > x_max)
			{
				x_max = points_airfoil[j].x;
			}
			else if(points_airfoil[j].x < x_min)
			{
				x_min = points_airfoil[j].x;
			}
		}

		c_l = ll * Gamma * 0.5 / U_inf / (x_max - x_min);

		//Building return
		flow->add_flow(myFlow);
		flow->add_source_sheets(Sigma, myAirfoil);
		c.airfoil = myAirfoil;
		c.flow = flow;
		c.c_p = c_p;
		c.c_l = c_l;
	}

	return c;
}

} // namespace wif_algo
