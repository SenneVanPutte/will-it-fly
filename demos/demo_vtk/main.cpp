#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	std::cout << wif_core::get_version() << std::endl;
	std::cout << wif_algo::get_version() << std::endl;
	std::cout << wif_viz::get_version()  << std::endl;
	
	std::shared_ptr<wif_core::flow_c> unifl = std::make_shared<wif_core::uniform_flow_c>();
	wif_core::vector_2d_c min, max, bins;
	min.x = -10;
	min.y = -10;
	max.x = 10;
	max.y = 10;
	bins.x = 20;
	bins.y = 20;
	//int binsx = 20, binsy = 20;
	
	std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(unifl, min, max);
	
	vizy->set_velocityarrows(bins);
	
	vizy->draw("test.png");
	
}
