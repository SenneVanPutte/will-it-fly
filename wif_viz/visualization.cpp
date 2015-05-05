#include "visualization.hpp"

namespace wif_viz
{


visualization_c::visualization_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	flow(flow),
	min_range(min_range),
	max_range(max_range),
	psi_bins(0.0, 0.0),
	phi_bins(0.0, 0.0),
	velocity_bins(0.0, 0.0)
{
	//
}


visualization_c::~visualization_c()
{
	//
}


void visualization_c::set_range(const vector_2d_c & new_min_range, const vector_2d_c & new_max_range)
{
	this->min_range = new_min_range;
	this->max_range = new_max_range;
}


void visualization_c::set_psi_bins(const vector_2d_c & bins)
{
	this->psi_bins = bins;
}


void visualization_c::set_phi_bins(const vector_2d_c & bins)
{
	this->phi_bins = bins;
}


void visualization_c::set_velocity_bins(const vector_2d_c & bins)
{
	this->velocity_bins = bins;
}


} // namespace wif_viz
