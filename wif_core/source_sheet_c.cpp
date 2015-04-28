#include "source_sheet_c.hpp"
#include <cmath>

using std::log;
using std::atan2;

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

	double temp1=a * a + 2 * a * b + b * b + d * d + c * c + 2 * c * d;
	double temp2=atan2(b * c - a * d, a * b + c * d)
                - atan2(b * c - a * d, a * b + b * b + d * d + c * d);
    double temp3=4 * M_PI * (b * b + d * d);

	return ((a * b - b * c) * (log(temp1) - log(a * a + c * c))
	        + 2 * (b * b + d * d) * (temp2))* sigma / (temp3);
}

double source_sheet_c::get_phi(const vector_2d_c & pos) const
{
	double a = line.begin.y - pos.y;
	double b = line.end.y - line.begin.y;
	double c = line.begin.x - pos.x;
	double d = line.end.x - line.begin.x;

	double temp1=a * b + b * b + d * d + c * d;
	double temp2=log(a * a + 2 * a * b + b * b + d * d + c * c + 2 * c * d);
	double temp3=sigma / (4 * M_PI * (b * b + d * d));

	double at1=atan2(b * c - a * d, temp1) ;
	double at2=atan2(b * c - a * d, a * b + c * d);



	return ((temp1) * temp2
	        + (2 * a * d - 2 * c * b) * at1- 2 * b * b - 2 * d * d
	        - (a * b + c * d) * log(a * a + c * c) - (2 * a * d - 2 * b * c) * at2)
	       * temp3;
}

vector_2d_c source_sheet_c::get_velocity(const vector_2d_c & pos) const
{
	//return vector_2d_c(line.end.x, line.begin.y) - pos;
	vector_2d_c diff = line.end - line.begin;
	double l = line.get_length();
	double ymin = (line.begin.x * diff.x - line.begin.y * diff.y) / l;
	double ymax = (line.end.x * diff.x + line.end.y * diff.y) / l;

	double x = (diff.y * pos.x - diff.x * pos.y + line.begin.y * line.end.x - line.end.y * line.begin.x) / l;
	double y = (diff.x * pos.x + diff.y * pos.y) / l;

	double vx = log((x * x + (y - ymin)) / (x * x + (y - ymax))) * sigma * x / (2 * M_PI);
	double vy = log((x * x + (y - ymin) * (y - ymin)) / (x * x + (y - ymax) * (y - ymax))) * sigma / (M_PI);
	return vector_2d_c(vx, vy);
}

}
