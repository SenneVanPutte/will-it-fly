#include "wif_viz.hpp"

#include <wif_core.hpp>

namespace wif_viz
{


uint32_t get_version()
{
    wif_core::get_version();
    return 1;
}


} //namespace wif_viz

