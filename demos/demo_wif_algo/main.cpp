#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	double radius = 2;
	unsigned int corners = 10;
	wif_core::vector_2d_c midpoint(0, 0);
	wif_core::airfoil_c myAirfoil(midpoint, radius, corners);
	std::shared_ptr<wif_core::uniform_flow_c> myFlow = std::make_shared<wif_core::uniform_flow_c>();
	bool Kuta = false;

	wif_algo::calculation_results_c calculate_flow2 = wif_algo::calculate_flow(myAirfoil, myFlow, Kuta);

	for(unsigned int i = 0; i < corners; i++)
	{
		std::cout << calculate_flow2.c_p[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << calculate_flow2.c_l << std::endl;


	return 0;
}
