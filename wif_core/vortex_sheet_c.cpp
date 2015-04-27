#include "vortex_sheet_c.hpp"
#include <cmath>

namespace wif_core
{

vortex_sheet_c::vortex_sheet_c() :
	line(line_2d_c(-1, 0, 1, 0)),
	lambda(1)
{

}

vortex_sheet_c::vortex_sheet_c(const line_2d_c & line, double lambda):
	line(line),
	lambda(lambda)
{
	//ctor
}

vortex_sheet_c::~vortex_sheet_c()
{
	//dtor
}

double vortex_sheet_c::get_psi(const vector_2d_c & pos) const
{
	return line.begin.x - pos.x;
}

double vortex_sheet_c::get_phi(const vector_2d_c & pos) const
{
	return line.end.y - pos.y;
}

vector_2d_c vortex_sheet_c::get_velocity(const vector_2d_c & pos) const
{
	return vector_2d_c(line.end.x, line.begin.y) - pos;
}


}
