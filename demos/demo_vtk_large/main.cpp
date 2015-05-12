#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>


void print_all_fields(const std::string & name, std::shared_ptr<wif_core::flow_c>  flow,
                      const wif_core::vector_2d_c                 &                min,
                      const wif_core::vector_2d_c                 &                max,
                      const wif_core::vector_2d_c                 &                binning)
{
	std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(flow, min, max);

	vizy->set_psi_bins(binning);
	vizy->set_phi_bins(binning);
	vizy->set_velocity_bins(binning);

	vizy->draw(name);
}


void visualize_all(bool                               screen,
                   const std::string         &        name,
                   std::shared_ptr<wif_core::flow_c>  flow,
                   const wif_core::vector_2d_c    &   min,
                   const wif_core::vector_2d_c    &   max,
                   const wif_core::vector_2d_c    &   binning)
{
	if(screen)
	{
		{
			std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(flow, min, max);

			vizy->set_psi_bins(binning);

			vizy->draw("");
		}

		{
			std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(flow, min, max);

			vizy->set_phi_bins(binning);

			vizy->draw("");
		}

		{
			std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(flow, min, max);

			vizy->set_velocity_bins(binning);

			vizy->draw("");
		}
	}
	else
	{
		print_all_fields(name, flow, min, max, binning);
	}
}


std::string get_name(bool screen, const std::string & filename)
{
	return screen ? "" : filename;
}


void test_uniflow(bool screen)
{
	std::shared_ptr<wif_core::flow_c> flow = std::make_shared<wif_core::uniform_flow_c>(0.0, 1.0);

	visualize_all(screen, "test-uniflow", flow, { -2, -2}, {2, 2}, {31, 31});
}


void test_circle(bool screen)
{
	wif_core::airfoil_c airfoil({0, 0}, 1, 30);

	std::shared_ptr<wif_core::flow_accumulate_c> flow = std::make_shared<wif_core::flow_accumulate_c>();
	flow->add_source_sheets(std::vector<double>(airfoil.get_lines().size(), 1), airfoil);

	visualize_all(screen, "test-circle", flow, { -2, -2}, {2, 2}, {31, 31});
}


void test_circle_flow(bool screen)
{
	wif_core::airfoil_c airfoil({0, 0}, 1, 30);

	std::shared_ptr<wif_core::flow_c> uniflow = std::make_shared<wif_core::uniform_flow_c>(0.0, 1.0);
	std::shared_ptr<wif_core::flow_accumulate_c> flow = std::make_shared<wif_core::flow_accumulate_c>(uniflow);
	flow->add_source_sheets(std::vector<double>(airfoil.get_lines().size(), 1), airfoil);

	visualize_all(screen, "test-circle-flow", flow, { -2, -2}, {2, 2}, {31, 31});
}


void tests()
{
	bool screen = true;

	test_uniflow(screen);
	test_circle(screen);
	test_circle_flow(screen);
}


int main()
{
	tests();
	return 0;
}
