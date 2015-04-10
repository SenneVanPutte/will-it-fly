#include "wif_algo.hpp"
#include "wif_core.hpp"

uint32_t wif_algo::get_version()
{


    wif_core::get_version();
    return 1;
}
