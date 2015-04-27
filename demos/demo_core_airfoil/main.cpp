#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	/*std::string filename = "/home/uauser/eindopdracht/will-it-fly/wif_core/airfoils/lednicer.dat";
	wif_core::airfoil_c airfoil(filename);
	std::cout << airfoil;
	std::cout << airfoil.get_circle_projection(9,wif_core::vector_2d_c(0.5,0),0.5);*/
	std::vector<wif_core::vector_2d_c> test;
	test.push_back(wif_core::vector_2d_c(1, 0.02));
	test.push_back(wif_core::vector_2d_c(0, 0.02));
	wif_core::airfoil_c airfoil(test, "flat");
	std::cout << airfoil;
	std::cout << airfoil.get_circle_projection(10, wif_core::vector_2d_c(0.5, 0), 0.5);

}
