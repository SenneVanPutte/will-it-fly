#include "wif_viz.hpp"

#include "visualization_vtk.hpp"
#include "visualization_root.hpp"

namespace wif_viz
{


uint32_t get_version()
{
	wif_core::get_version();
	return 1;
}


std::shared_ptr<visualization_c> create_visualization_vtk(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range)
{
	return std::make_shared<visualization_vtk_c>(flow, min_range, max_range);
}


std::shared_ptr<visualization_c> create_visualization_root(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range)
{
	return std::make_shared<visualization_root_c>(flow, min_range, max_range);
}


} // namespace wif_viz

