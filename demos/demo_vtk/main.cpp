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

	std::shared_ptr<wif_core::flow_accumulate_c> flow = std::make_shared<wif_core::flow_accumulate_c>();
	flow->add_flow(std::make_shared<wif_core::source_sink_c>(wif_core::vector_2d_c(0, 0), 100));

	wif_core::vector_2d_c min, max, bins;
	min.x = -10;
	min.y = -10;
	max.x = 10;
	max.y = 10;
	bins.x = 100;
	bins.y = 100;
	//int binsx = 20, binsy = 20;

	std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(flow, min, max);

	//vizy->set_velocityarrows(bins);
	vizy->set_psi_bins(bins);

	vizy->draw("test.png");

}
