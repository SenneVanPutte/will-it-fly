#include "source_sheet_c.hpp"
#include <cmath>
#include <math.h>

namespace wif_core
{

source_sheet_c::source_sheet_c() :
	line(line_2d_c(-1, 0, 1, 0)),
	sigma(1)
{

}

source_sheet_c::source_sheet_c(const line_2d_c & line, double sigma):
	line(line),
	sigma(sigma)
{
	//ctor
}

source_sheet_c::~source_sheet_c()
{
	//dtor
}

double source_sheet_c::get_psi(const vector_2d_c & pos) const
{
	double a = line.begin.y - pos.y;
	double b = line.end.y - line.begin.y;
	double c = line.begin.x - pos.x;
	double d = line.end.x - line.begin.x;

	return ((a * b - b * c) * (log(a * a + 2 * a * b + b * b + d * d + c * c + 2 * c * d) - log(a * a + c * c))
	        + 2 * (b * b + d * d) * (atan2(b * c - a * d, a * b + c * d) - atan2(b * c - a * d, a * b + b * b + d * d + c * d)))
	       * sigma / (4 * M_PI * (b * b + d * d));
}

double source_sheet_c::get_phi(const vector_2d_c & pos) const
{
	//return line.end.y - pos.y;
	return 1;
}

vector_2d_c source_sheet_c::get_velocity(const vector_2d_c & pos) const
{
	return vector_2d_c(line.end.x, line.begin.y) - pos;
}


}
