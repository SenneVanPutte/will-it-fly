#include "flow_sheet_c.hpp"

namespace wif_core
{

flow_sheet_c::flow_sheet_c():
	line(line_2d_c(0, 0, 0, 0))
{
}

flow_sheet_c::flow_sheet_c(const line_2d_c & line) :
	line(line)
{
	//ctor
}

flow_sheet_c::~flow_sheet_c()
{
	//dtor
}

flow_sheet_c::flow_sheet_c(const flow_sheet_c & other) :
	line(other.line)
{
	//copy ctor
}

double flow_sheet_c::psi(double x, double y) const
{
	return this->psi(vector_2d_c(x, y));
}

double flow_sheet_c::psi(const vector_2d_c & vec) const
{
	// TODO: implement integral

	return this->psi_for_integration(0, vec);
}

double flow_sheet_c::phi(double x, double y) const
{
	return this->phi(vector_2d_c(x, y));
}

double flow_sheet_c::phi(const vector_2d_c & vec) const
{
	// TODO: implement integral

	return this->phi_for_integration(0, vec);
}

vector_2d_c flow_sheet_c::v(double x, double y) const
{
	return this->v(vector_2d_c(x, y));
}

vector_2d_c flow_sheet_c::v(const vector_2d_c & vec) const
{
	// TODO: implement integral

	return this->v_for_integration(0, vec);
}

double flow_sheet_c::psi_for_integration(double t, const vector_2d_c & pos) const
{
	return this->psi_one_point(this->line_equation(t), pos);
}

double flow_sheet_c::phi_for_integration(double t, const vector_2d_c & pos) const
{
	return this->phi_one_point(this->line_equation(t), pos);
}

vector_2d_c flow_sheet_c::v_for_integration(double t, const vector_2d_c & pos) const
{
	return this->v_one_point(this->line_equation(t), pos);
}

vector_2d_c flow_sheet_c::line_equation(double t) const
{
	vector_2d_c temp = line.end - line.begin;
	temp *= t;
	temp += line.begin;
	return temp;
}


}
