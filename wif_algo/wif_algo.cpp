#include "wif_algo.hpp"

#include <wif_core/wif_core.hpp>

namespace wif_algo
{


uint32_t get_version()
{
	wif_core::get_version();
	return 1;
}


calculation_results_c calculate_flow(const wif_core::airfoil_c & input, std::shared_ptr<wif_core::uniform_flow_c> uniform_flow)
{
	calculation_results_c c;

	return c;
}


} // namespace wif_algo
