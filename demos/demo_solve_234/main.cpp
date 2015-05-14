#include <iostream>

#include <wif_core/wif_core.hpp>
//#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{


	//maakt flow object met varienrende sterkte
	for(double strenght = 1; strenght < 5; strenght += 1.0)
	{
		wif_core::flow_accumulate_c flow;
		flow.add_flow(std::make_shared<wif_core::uniform_flow_c>(0, strenght));

		for(double y = -1.0; y <= 1; y += 0.2)
		{
			flow.add_flow(std::make_shared<wif_core::source_sink_c>(wif_core::vector_2d_c(0, y), 1));
		}

		//drawf
		std::shared_ptr<wif_viz::visualization_c> viz = wif_viz::create_visualization_vtk(std::make_shared<wif_core::flow_accumulate_c>(flow), { -3, -3}, {3, 3});
		viz->set_phi_bins({300, 300});
		viz->set_psi_bins({300, 300});
		viz->set_velocity_bins({300, 300});
		viz->set_output_to_file(true);
		viz->draw("sources_in_uniform_flow");
	}

}
