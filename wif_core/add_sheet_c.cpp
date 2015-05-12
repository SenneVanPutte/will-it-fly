#include "add_sheet_c.hpp"

#include <iostream>


namespace wif_core
{


add_sheet_phi_c::add_sheet_phi_c(const vector_2d_c & vec):
	position(vec)
{
	//
}


add_sheet_phi_c::~add_sheet_phi_c()
{
	//
}

double add_sheet_phi_c::operator()(double init, const std::shared_ptr<flow_c> & flow) const
{
	return init + flow.get()->get_phi(position);
}


add_sheet_psi_c::add_sheet_psi_c(const vector_2d_c & vec):
	position(vec)
{
	//
}


add_sheet_psi_c::~add_sheet_psi_c()
{
	//
}


double add_sheet_psi_c::operator()(double init, const std::shared_ptr<flow_c> & flow) const
{
	return init + flow.get()->get_psi(position);
}


add_sheet_v_c::add_sheet_v_c(const vector_2d_c & vec):
	position(vec)
{
	//ctor
}


add_sheet_v_c::~add_sheet_v_c()
{
	//dtor
}


vector_2d_c add_sheet_v_c::operator()(vector_2d_c init, const std::shared_ptr<flow_c> & flow) const
{
	return init + flow.get()->get_velocity(position);
}


} // namespace wif_core
