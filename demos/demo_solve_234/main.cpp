#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

void make_plot(const wif_core::flow_accumulate_c & flow)
{
	std::shared_ptr<wif_viz::visualization_c> viz = wif_viz::create_visualization_vtk(std::make_shared<wif_core::flow_accumulate_c>(flow), { -3, -3}, {3, 3});
	viz->set_phi_bins({300, 300});
	viz->set_psi_bins({300, 300});
	viz->set_velocity_bins({300, 300});
	viz->set_output_to_file(true);
	viz->draw("sources_in_uniform_flow");
}

void make_plot(const wif_core::flow_accumulate_c & flow,wif_core::airfoil_c * airfoil)
{
	std::shared_ptr<wif_viz::visualization_c> viz = wif_viz::create_visualization_vtk(std::make_shared<wif_core::flow_accumulate_c>(flow), { -3, -3}, {3, 3});
	viz->set_phi_bins({300, 300});
	viz->set_psi_bins({300, 300});
	viz->set_velocity_bins({300, 300});
	viz->set_output_to_file(true);
	viz->set_airfoil(airfoil);
	viz->draw("sources_in_uniform_flow");
}

int main()
{


	//maakt flow object met varienrende sterkte
	//opdracht 2 geeft een vaste sterkte, maar als er 1 van de situaties wordt uitgekozen is dit een situatie met vaste starkte.
	for (double strenght=1;strenght < 5;strenght+=1.0)
	{
		wif_core::flow_accumulate_c flow;
		flow.add_flow(std::make_shared<wif_core::uniform_flow_c>(0, strenght));

		for(double y = -1.0; y <= 1; y += 0.2)
		{
			flow.add_flow(std::make_shared<wif_core::source_sink_c>(wif_core::vector_2d_c(0, y), 1));
		}

		//drawf
		make_plot(flow);

	}

	{//flow met source sheet
		wif_core::flow_accumulate_c flow;
		flow.add_flow(std::make_shared<wif_core::uniform_flow_c>(0, 3));
		flow.add_source_sheet(wif_core::line_2d_c(0.0,-1.0,0.0,1.0),1);
		make_plot(flow);
	}

	{//flow met source sheet, waabij sterkte 2U is.
		wif_core::flow_accumulate_c flow;
		flow.add_flow(std::make_shared<wif_core::uniform_flow_c>(0, 1));
		flow.add_source_sheet(wif_core::line_2d_c(0.0,-1.0,0.0,1.0),2);
		make_plot(flow);
	}

	{//parametriseer cirkel
		wif_core::airfoil_c airfoil(wif_core::vector_2d_c(0.0,0.0),1,40);
		std::shared_ptr<wif_core::uniform_flow_c> uniflow =
				std::make_shared<wif_core::uniform_flow_c>(0, 1);
		//geen idee hoe ge deze tekend, maar dat moet hier gebeuren
		wif_algo::calculation_results_c calc_res = wif_algo::calculate_flow(airfoil,uniflow,false,1);
		make_plot(calc_res.flow);
	}

    {//laad airfoil


    }



}
