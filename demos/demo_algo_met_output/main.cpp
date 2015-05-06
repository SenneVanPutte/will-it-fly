#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

int main()
{
	std::shared_ptr<wif_core::flow_c> unifl = std::make_shared<wif_core::uniform_flow_c>();
	std::shared_ptr<wif_core::flow_accumulate_c> flow = std::make_shared<wif_core::flow_accumulate_c>();//unifl);

#if 1
	wif_core::airfoil_c airfoil({0, 0}, 1, 300);
#else
	wif_core::airfoil_c airfoil("../../wif_core/airfoils/selig.dat");
#endif //

	std::shared_ptr<wif_core::flow_c> ff = std::make_shared<wif_core::flow_accumulate_c>(std::vector<double>(airfoil.get_lines().size(), 1), airfoil);

	wif_core::vector_2d_c min, max, bins;
	min.x = -2;
	min.y = -2;
	max.x = 2;
	max.y = 2;
	bins.x = 10;
	bins.y = 10;

	std::shared_ptr<wif_viz::visualization_c> vizy = wif_viz::create_visualization_vtk(ff, min, max);

	vizy->set_phi_bins(bins);
	vizy->draw("test.png");

	return 0;
}
