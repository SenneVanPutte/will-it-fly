#include "add_sheet_c.hpp"

namespace wif_core
{


add_sheet_c::add_sheet_c(const vector_2d_c & vec, E_CHOOSEFUNC choose):
	what(choose),
	position(vec)
{
	//ctor
}

add_sheet_c::~add_sheet_c()
{
	//dtor
}

double add_sheet_c::operator()(double init, std::shared_ptr<flow_c>  flow) const
{
	if(what == EC_PHI)
	{
		return init + flow.get()->get_phi(position);
	}
	else
	{
		return init + flow.get()->get_psi(position);
	}
}

vector_2d_c add_sheet_c::operator()(vector_2d_c init, std::shared_ptr<flow_c> flow) const
{
	return init + flow.get()->get_velocity(position);
}

}
