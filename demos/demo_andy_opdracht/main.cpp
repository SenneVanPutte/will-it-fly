#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	double pi = 3.1415;

	{
		//Opdracht 12

		double radius = 1;
		unsigned int num_lines = 100;
		wif_core::vector_2d_c midpoint(0, 0);
		wif_core::airfoil_c myAirfoil("wif_core/airfoils/n0012-il.dat");
		myAirfoil = myAirfoil.get_circle_projection(num_lines, midpoint, radius, 0.0001);
		myAirfoil = myAirfoil.closed_merge();
		double angle_in_degrees = 0;
		std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>((angle_in_degrees / 180) * pi, 1);
		bool Kutta = 0;

		wif_algo::calculation_results_c myResults = wif_algo::calculate_flow(myAirfoil, myFlow, Kutta);

		std::vector<wif_core::line_2d_c> mylines = myAirfoil.get_lines();
		std::vector<wif_core::vector_2d_c> centers(num_lines);
		std::vector<double> angles(num_lines);
		std::vector<double> c_p_boven;
		std::vector<double> x_as_boven;
		std::vector<double> c_p_onder;
		std::vector<double> x_as_onder;


		for(unsigned int i = 0; i < num_lines; i++)
		{
			wif_core::line_2d_c temp_line = mylines[i];
			centers[i] = temp_line.get_center_point();

			if(temp_line.begin.x > temp_line.end.x && temp_line.begin.y > temp_line.end.y)
			{
				angles[i] = temp_line.get_angle() - pi / 2;
			}
			else if(temp_line.begin.x > temp_line.end.x && temp_line.begin.y < temp_line.end.y)
			{
				angles[i] = temp_line.get_angle() - pi / 2;
			}
			else if(temp_line.begin.x < temp_line.end.x && temp_line.begin.y > temp_line.end.y)
			{
				angles[i] = temp_line.get_angle() - pi / 2;
			}
			else if(temp_line.begin.x < temp_line.end.x && temp_line.begin.y < temp_line.end.y)
			{
				angles[i] = temp_line.get_angle() + (3 * pi) / 2;
			}
			else if(temp_line.begin.x == temp_line.end.x)
			{
				angles[i] = 0;
			}
			else if(temp_line.begin.y == temp_line.end.y)
			{
				angles[i] = pi / 2;
			}
			else
			{
				std::cout << i << "  Not in any of these categories" << std::endl;
			}

			if(centers[i].y > 0)
			{
				c_p_boven.push_back(myResults.c_p[i]);
				x_as_boven.push_back(centers[i].x);
			}
			else if(centers[i].y < 0)
			{
				c_p_onder.push_back(myResults.c_p[i]);
				x_as_onder.push_back(centers[i].x);
			}
		}

		int num_elements_boven = c_p_boven.size();
		int num_elements_onder = c_p_onder.size();

		std::vector<vector<double>> c_p_data(3, std::vector<double>(c_p_onder.size()));
		std::vector<std::string> Legend(3);
		Legend[0] = "Bovenkant";
		Legend[1] = "Onderkant";
		Legend[2] = "Verschil";

		c_p_boven.pop_back();
		c_p_boven.erase(c_p_boven.begin());

		std::reverse(c_p_onder.begin(), c_p_onder.end());
		c_p_onder.pop_back();
		c_p_data[0] = c_p_boven;
		c_p_data[1] = c_p_onder;
		std::vector<double> c_p_differences;

		for(unsigned int i = 0; i < c_p_boven.size(); i++)
		{
			c_p_differences.push_back(c_p_boven[i] - c_p_onder[i]);
		}

		c_p_data[2] = c_p_differences;
		std::shared_ptr<wif_viz::visualization_c> myRoot = wif_viz::create_visualization_root(myFlow, midpoint, midpoint);
		myRoot->plotVectors(c_p_data, x_as_onder, Legend, "cpbeno.png", "x", "cp", "Aantal panelen = 49, Alpha = 0");
	}

	{
		// OPDRACHT 13
		double radius = 1;

		wif_core::vector_2d_c midpoint(0, 0);
		wif_core::airfoil_c myAirfoil("wif_core/airfoils/n0012-il.dat");
		double angle_in_degrees = 0;
		std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>((angle_in_degrees / 180) * pi, 1);
		bool Kutta = 0;

		int max_lines = 100;
		int step_size = 10;

		std::vector<double> x_as;
		std::vector<vector<double>> plotData(1);

		for(int i = 10; i <= max_lines; i += step_size)
		{
			unsigned int num_lines = i;
			myAirfoil = myAirfoil.get_circle_projection(num_lines, midpoint, radius, 0.0001);
			myAirfoil = myAirfoil.closed_merge();
			wif_algo::calculation_results_c myResults = wif_algo::calculate_flow(myAirfoil, myFlow, Kutta);

			x_as.push_back(i);
			plotData[0].push_back(myResults.closed_body_check * 1000);
			std::cout << "Aantal lijnen: " << i << "    Closed Body CheckSum: " << myResults.closed_body_check << std::endl;
		}

		std::vector<std::string> Legend(1);
		Legend[0] = "Som sigma*l";




		std::shared_ptr<wif_viz::visualization_c> myRoot = wif_viz::create_visualization_root(myFlow, midpoint, midpoint);
		myRoot->plotVectors(plotData, x_as, Legend, "closedbodycheck.png", "N", "Sommen sigma*l * 10^3", "Gesloten lichaam check");
	}



	return 0;
}
