#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	double radius = 2;
	unsigned int corners = 100;
	wif_core::vector_2d_c midpoint(0, 0);
	wif_core::airfoil_c myAirfoil(midpoint, radius, corners);
	std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>(0,3);
	bool Kuta = false;


	wif_algo::calculation_results_c calculate_flow2 = wif_algo::calculate_flow(myAirfoil, myFlow, Kuta);
	std::cout << "c_p_i" << std::endl;
	for(unsigned int i = 0; i < corners; i++)
	{
		std::cout << calculate_flow2.c_p[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << "c_l"<< std::endl;
	std::cout << calculate_flow2.c_l << std::endl;
	std::cout << std::endl;

	///////

	std::cout << "y_c_i" << std::endl;
	
	std::vector<wif_core::line_2d_c> mylines = myAirfoil.get_lines();
	unsigned int num_lines = mylines.size();
	
	std::vector<wif_core::vector_2d_c> centers(num_lines);
	for(unsigned int i = 0; i < num_lines; i++)
	{
		wif_core::line_2d_c temp_line = mylines[i];
		centers[i] = temp_line.get_center_point();
	}
	for(unsigned int i =0; i<corners; i++)
	{
		std::cout<<centers[i].y<<std::endl; 
	}
	std::cout<<std::endl;


	return 0;
}
