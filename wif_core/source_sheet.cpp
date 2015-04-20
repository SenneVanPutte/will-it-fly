#include "source_sheet.hpp"
#include <cmath>

namespace wif_core
{

source_sheet::source_sheet(const line_2d_c& line,double sigma):
	flow_sheet(line),
	sigma(sigma)
{
	//ctor
}

source_sheet::~source_sheet()
{
	//dtor
}

double source_sheet::psi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const
{
	vector_2d_c dif=pos1-pos2;
	double theta=atan2(dif.y,dif.x);
	return sigma*theta/(2*M_PI);
}
double source_sheet::phi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const
{
	vector_2d_c dif=pos1-pos2;
	return sigma/(2*M_PI)*log(dif.get_length());
}
vector_2d_c source_sheet::v_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const
{
	vector_2d_c dif=pos1-pos2;
	double vx=sigma/(2*M_PI*dif.get_length_sq())*dif.x;
	double vy=sigma/(2*M_PI*dif.get_length_sq())*dif.y;
}

}
