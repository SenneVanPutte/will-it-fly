#include "source_sink_c.hpp"


namespace wif_core
{


source_sink_c::source_sink_c() :
	location(vector_2d_c(0, 0)),
	sigma(1)
{
	//
}


source_sink_c::source_sink_c(const vector_2d_c & location, double sigma) :
	location(location),
	sigma(sigma)
{
	//
}


source_sink_c::~source_sink_c()
{
	//
}


double source_sink_c::get_psi(const vector_2d_c & pos) const
{
	vector_2d_c diff = pos - location;
	return atan(diff.y / diff.x) * sigma / (2 * M_PI);
}


double source_sink_c::get_phi(const vector_2d_c & pos) const
{
	vector_2d_c diff = pos - location;
	return log(diff.get_length_sq()) * sigma / (4 * M_PI);
}




vector_2d_c source_sink_c::get_velocity(const vector_2d_c & pos) const
{
	vector_2d_c diff = pos - location;
	double vx = diff.x / (diff.get_length_sq()) * sigma / (2 * M_PI);
	double vy = diff.y / (diff.get_length_sq()) * sigma / (2 * M_PI);
	return vector_2d_c(vx, vy);
}


} // namespace wif_core
