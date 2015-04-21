#include "wif_algo.hpp"

#include <wif_core.hpp>

namespace wif_algo
{


uint32_t get_version()
{
	wif_core::get_version();
	return 1;
}


} // namespace wif_algo
