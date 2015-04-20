#include "flow_sheet.hpp"

namespace wif_core
{

flow_sheet::flow_sheet(const line_2d_c & line) :
	line(line)
{
	//ctor
}

flow_sheet::~flow_sheet()
{
	//dtor
}

flow_sheet::flow_sheet(const flow_sheet& other) :
	line(other.line)
{
	//copy ctor
}

double flow_sheet::psi(double x,double y) const
{
	return this->psi(vector_2d_c(x,y));
}

double flow_sheet::psi(const vector_2d_c& vec) const
{
	// TODO: implement integral

	return this->psi_for_integration(0,vec);
}

double flow_sheet::phi(double x,double y) const
{
	return this->phi(vector_2d_c(x,y));
}

double flow_sheet::phi(const vector_2d_c& vec) const
{
	// TODO: implement integral

	return this->phi_for_integration(0,vec);
}

vector_2d_c flow_sheet::v(double x,double y) const
{
	return this->v(vector_2d_c(x,y));
}

vector_2d_c flow_sheet::v(const vector_2d_c& vec) const
{
	// TODO: implement integral

	return this->v_for_integration(0,vec);
}

double flow_sheet::psi_for_integration(double t,const vector_2d_c& pos) const
{
	return this->psi_one_point(this->line_equation(t),pos);
}

double flow_sheet::phi_for_integration(double t,const vector_2d_c& pos) const
{
	return this->phi_one_point(this->line_equation(t),pos);
}

vector_2d_c flow_sheet::v_for_integration(double t,const vector_2d_c& pos) const
{
	return this->v_one_point(this->line_equation(t),pos);
}

vector_2d_c flow_sheet::line_equation(double t) const
{
	vector_2d_c temp=line.end-line.begin;
	temp*=t;
	temp+=line.begin;
	return temp;
}


}
