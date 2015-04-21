#include "add_sheet_c.hpp"

namespace wif_core
{


add_sheet_c::add_sheet_c(const vector_2d_c& vec, E_CHOOSEFUNC choose):
what(choose),
position(vec)
{
	//ctor
}

add_sheet_c::~add_sheet_c()
{
	//dtor
}

double add_sheet_c::operator()(double init, flow_sheet_c* sheet) const
{
    if (what==EC_PHI)
    {
        return init+sheet->phi(position);
    }
    else
    {
        return init+sheet->psi(position);
    }
}

vector_2d_c add_sheet_c::operator()(vector_2d_c init, flow_sheet_c* sheet) const
{
    return init+sheet->v(position);
}

}
