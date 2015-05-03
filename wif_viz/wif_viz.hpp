#ifndef __WIF_VIZ_HPP_INCLUDED__
#define __WIF_VIZ_HPP_INCLUDED__

#include <cstdint>

#include "visualization.hpp"

namespace wif_viz
{


uint32_t get_version();


std::shared_ptr<visualization_c> create_visualization_vtk(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range);


std::shared_ptr<visualization_c> create_visualization_root(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range);


} // namespace wif_viz

#endif // __WIF_VIZ_HPP_INCLUDED__
