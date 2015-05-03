#include "visualization_root.hpp"

namespace wif_viz
{


visualization_root_c::visualization_root_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	visualization_c(flow, min_range, max_range)
{
	//
}


visualization_root_c::~visualization_root_c()
{
	//
}


void visualization_root_c::draw(const std::string & filename)
{
	//
}


} // namespace wif_viz
