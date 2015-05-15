#include "uniform_flow_c.hpp"

#include <math.h>


namespace wif_core
{


uniform_flow_c::uniform_flow_c() :
	U(vector_2d_c(1, 0))
{
	//
}


uniform_flow_c::uniform_flow_c(double angle, double u) :
	U(vector_2d_c(cos(angle) * u, sin(angle) * u))
{
	//
}


uniform_flow_c::~uniform_flow_c()
{
	//
}


double uniform_flow_c::get_phi(const vector_2d_c & pos) const
{
	return U.x * pos.x + U.y * pos.y;
}


double uniform_flow_c::get_psi(const vector_2d_c & pos) const
{
	return U.x * pos.y - U.y * pos.x;
}


vector_2d_c uniform_flow_c::get_velocity(const vector_2d_c & pos) const
{
	return U;
}


vector_2d_c uniform_flow_c::get_velocity() const
{
	return U;
}


double uniform_flow_c::get_angle() const
{
	return U.get_angle();
}


double uniform_flow_c::get_strength() const
{
	return U.get_length();
}


} // namespace wif_core
