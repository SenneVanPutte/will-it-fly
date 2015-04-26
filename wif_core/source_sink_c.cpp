#include "source_sink_c.hpp"

namespace wif_core
{


source_sink_c::source_sink_c() :
	location(vector_2d_c(0, 0)),
	sigma(1)
{
	//ctor
}

source_sink_c::source_sink_c(const vector_2d_c & location, double sigma) :
	location(location),
	sigma(sigma)
{
	//ctor
}

source_sink_c::~source_sink_c()
{
	//dtor
}

double source_sink_c::get_phi(const vector_2d_c & pos) const
{
	return pos.x;
}

double source_sink_c::get_psi(const vector_2d_c & pos) const
{
	return pos.y;
}

vector_2d_c source_sink_c::get_velocity(const vector_2d_c & pos) const
{
	return pos;
}

}
