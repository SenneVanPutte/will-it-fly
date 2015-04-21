#include "source_sheet_c.hpp"
#include <cmath>

namespace wif_core
{

source_sheet_c::source_sheet_c(const line_2d_c& line,double sigma):
	flow_sheet_c(line),
	sigma(sigma)
{
	//ctor
}

source_sheet_c::~source_sheet_c()
{
	//dtor
}

double source_sheet_c::psi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const
{
	vector_2d_c dif=pos1-pos2;
	double theta=dif.get_angle();
	return sigma*theta/(2*M_PI);
}
double source_sheet_c::phi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const
{
	vector_2d_c dif=pos1-pos2;
	return sigma/(2*M_PI)*log(dif.get_length());
}
vector_2d_c source_sheet_c::v_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const
{
	vector_2d_c dif=pos1-pos2;
	double vx=sigma/(2*M_PI*dif.get_length_sq())*dif.x;
	double vy=sigma/(2*M_PI*dif.get_length_sq())*dif.y;

	return vector_2d_c(vx,vy);
}

}
