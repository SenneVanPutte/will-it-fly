#include <iostream>
#include <cmath>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	double radius = 2;
	unsigned int num_lines = 100;
	wif_core::vector_2d_c midpoint(0, 0);
	wif_core::airfoil_c myAirfoil(midpoint, radius, num_lines);
	std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>(0, 1);
	bool Kutta = 0;

	wif_algo::calculation_results_c calculate_flow2 = wif_algo::calculate_flow(myAirfoil, myFlow, Kutta);
	std::vector<wif_core::line_2d_c> mylines = myAirfoil.get_lines();
	std::vector<wif_core::vector_2d_c> centers(num_lines);
	std::cout << "y" << "   " << "cp calc" << "   " << "cp theor pol" << "   " << "cp theor cart" << std::endl;

	for(unsigned int i = 0; i < num_lines; i++)
	{
		wif_core::line_2d_c temp_line = mylines[i];
		centers[i] = temp_line.get_center_point();
		std::cout << centers[i].y << "   " << calculate_flow2.c_p[i] << "   " << 1 - 4 * pow(sin(temp_line.get_angle()), 2) << "   " << 1 - 4 * pow((centers[i].y / radius), 2)  << std::endl;
	}



	return 0;
}
