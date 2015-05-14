#include <iostream>
#include <cmath>
#include <fstream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	double pi = 3.1415;
	//opdracht 8
	double radius = 2;
	unsigned int num_lines = 100;

	wif_core::vector_2d_c midpoint(0, 0);
	wif_core::airfoil_c myAirfoil(midpoint, radius, num_lines);
	std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>(0, 1);
	std::vector<wif_core::line_2d_c> mylines = myAirfoil.get_lines();
	std::vector<wif_core::vector_2d_c> centers(num_lines);
	std::vector<double> angles(num_lines);
	bool Kutta = 0;
	int imax = 20;
	int stepsize = 5;
	int j = 0;
	std::vector<vector<double>> data_to_plot_gamma(imax / stepsize, std::vector<double>(num_lines));
	std::cout << imax / stepsize << std::endl;
	std::vector<std::string> Legend(imax / stepsize);
	std::vector<double> X_as(num_lines);

	for(unsigned int i = 0; i < num_lines; i++)
	{
		wif_core::line_2d_c temp_line = mylines[i];
		centers[i] = temp_line.get_center_point();
		X_as[i] = i;

		if(centers[i].y > 0)
		{
			angles[i] = atan2(centers[i].y, centers[i].x);
		}
		else
		{
			angles[i] = atan2(centers[i].y, centers[i].x) + 2 * pi;
		}

	}




	for(int i = 0 ; i < imax ; i = i + stepsize)
	{
		double gamma = i * 1.;

		std::string filename = std::to_string(i) + ".txt";
		wif_algo::calculation_results_c calculate_flow2 = wif_algo::calculate_flow(myAirfoil, myFlow, Kutta, gamma);





		data_to_plot_gamma[j] = calculate_flow2.c_p;

		Legend[j] = std::to_string(gamma);

		j++;

	}

	std::shared_ptr<wif_viz::visualization_c> myRoot = wif_viz::create_visualization_root(myFlow, midpoint, midpoint);
	myRoot->plotVectors(data_to_plot_gamma, X_as, Legend, "test.pdf", "paneel", "cp", "cp(gamma)");


	//Opdracht 14
	/*wif_core::airfoil_c myAirfoil("wif_core/airfoils/n0012-il.dat");
	wif_core::airfoil_c myClosedAirfoil = myAirfoil.closed_intersect();
	double gamma = 0;

	bool Kutta = 0;

	int j = 0;
	int max_angle=pi/2;
	int step_angle=pi/8;

	for(double i = 0 ; i <= max_angle; i = i + step_angle)
	{
		double angle_of_attack = i;
		std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>(angle_of_attack, 1);

		std::string filename = std::to_string(j) + ".txt";
		wif_algo::calculation_results_c calculate_flow2 = wif_algo::calculate_flow(myClosedAirfoil, myFlow, Kutta);


		std::vector<wif_core::line_2d_c> mylines = myClosedAirfoil.get_lines();
		int num_lines = mylines.size();
		std::vector<wif_core::vector_2d_c> centers(num_lines);
		std::vector<double> angles(num_lines);
		std::vector<double> upperfoil_x(num_lines);
		std::vector<double> underfoil_x(num_lines);
		std::vector<double> centers_x(num_lines);
		std::vector<vector<double>> data_to_plot_under_upper(2, std::vector<double>(num_lines));
		std::vector<vector<double>> data_to_plot_under(max_angle/step_angle, std::vector<double>(num_lines));
		std::vector<vector<double>> data_to_plot_upper(max_angle/step_angle, std::vector<double>(num_lines));
		std::vector<std::string> Legend(2);
		std::vector<std::string> Legend2(max_angle/step_angle);

		for(unsigned int i = 0; i < num_lines; i++)
		{
			wif_core::line_2d_c temp_line = mylines[i];
			centers[i] = temp_line.get_center_point();

			if(centers[i].y > 0)
			{
				angles[i] = atan2(centers[i].y, centers[i].x);
				upperfoil_x[i]=calculate_flow2.c_p[i];
			}
			else
			{
				angles[i] = atan2(centers[i].y, centers[i].x) + 2 * pi;
				underfoil_x[i]=calculate_flow2.c_p[i];
			}

		}
		data_to_plot_under_upper[0]=underfoil_x;
		data_to_plot_under_upper[1]=upperfoil_x;
		Legend[0]="Under foil with angle of attack " + std::to_string(angle_of_attack);
		Legend[1]="Upper foil with angle of attack " + std::to_string(angle_of_attack);
		data_to_plot_under[j]=underfoil_x;
		data_to_plot_upper[j]=upperfoil_x;
		Legend2[j]=std::to_string(angle_of_attack);
		j++;

	}*/

	//Opdracht 15
	/*wif_core::airfoil_c myAirfoil("wif_core/airfoils/n0012-il.dat");
	wif_core::airfoil_c myClosedAirfoil = myAirfoil.closed_intersect();
	double gamma = 0;

	bool Kutta = 1;

	int j = 0;
	int max_angle=pi/2;
	int step_angle=pi/8;

	for(double i = 0 ; i <= max_angle; i = i + step_angle)
	{
		double angle_of_attack = i;
		std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>(angle_of_attack, 1);

		std::string filename = std::to_string(j) + ".txt";
		wif_algo::calculation_results_c calculate_flow2 = wif_algo::calculate_flow(myClosedAirfoil, myFlow, Kutta);


		std::vector<wif_core::line_2d_c> mylines = myClosedAirfoil.get_lines();
		int num_lines = mylines.size();
		std::vector<wif_core::vector_2d_c> centers(num_lines);
		std::vector<double> angles(num_lines);
		std::vector<double> upperfoil_x(num_lines);
		std::vector<double> underfoil_x(num_lines);
		std::vector<double> centers_x(num_lines);
		std::vector<vector<double>> data_to_plot_under_upper(2, std::vector<double>(num_lines));
		std::vector<vector<double>> data_to_plot_under(max_angle/step_angle, std::vector<double>(num_lines));
		std::vector<vector<double>> data_to_plot_upper(max_angle/step_angle, std::vector<double>(num_lines));
		std::vector<std::string> Legend(2);
		std::vector<std::string> Legend2(max_angle/step_angle);

		for(unsigned int i = 0; i < num_lines; i++)
		{
			wif_core::line_2d_c temp_line = mylines[i];
			centers[i] = temp_line.get_center_point();

			if(centers[i].y > 0)
			{
				angles[i] = atan2(centers[i].y, centers[i].x);
				upperfoil_x[i]=calculate_flow2.c_p[i];
			}
			else
			{
				angles[i] = atan2(centers[i].y, centers[i].x) + 2 * pi;
				underfoil_x[i]=calculate_flow2.c_p[i];
			}

		}
		data_to_plot_under_upper[0]=underfoil_x;
		data_to_plot_under_upper[1]=upperfoil_x;
		Legend[0]="Under foil with angle of attack " + std::to_string(angle_of_attack);
		Legend[1]="Upper foil with angle of attack " + std::to_string(angle_of_attack);
		data_to_plot_under[j]=underfoil_x;
		data_to_plot_upper[j]=upperfoil_x;
		Legend2[j]=std::to_string(angle_of_attack);
		j++;

	}*/

	//Opdracht 16



	return 0;
}
