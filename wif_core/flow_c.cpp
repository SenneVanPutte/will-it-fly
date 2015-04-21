#include "flow_c.hpp"

#include <numeric>
#include "source_sheet_c.hpp"
#include "add_sheet_c.hpp"

namespace wif_core
{

flow_c::flow_c():
    U(vector_2d_c(0,0))
{

}

flow_c::~flow_c()
{
   this->empty_sheets();
}

flow_c::flow_c(const flow_c& other)
{
    //copy ctor
}

flow_c::flow_c(const vector_2d_c& u):
U(u)
{
}

flow_c& flow_c::operator=(const flow_c& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

bool flow_c::empty_sheets()
{
     for (std::vector<flow_sheet_c*>::iterator it = sheets.begin() ; it != sheets.end(); ++it)
   {
     delete (*it);
   }
   sheets.clear();
   return true;
}

double flow_c::psi(vector_2d_c pos) const
{
    add_sheet_c add = add_sheet_c(pos,EC_PSI);
    double init=U.x*pos.y+U.y*pos.x;
    return std::accumulate(sheets.begin(),sheets.end(),init,add);
}

double flow_c::phi(vector_2d_c pos) const
{
    add_sheet_c add = add_sheet_c(pos,EC_PHI);
    double init=U.x*pos.x+U.y*pos.y;
    return std::accumulate(sheets.begin(),sheets.end(),init,add);
}

vector_2d_c flow_c::v(vector_2d_c pos) const
{
    add_sheet_c add = add_sheet_c(pos,EC_PSI);
    return std::accumulate(sheets.begin(),sheets.end(),U,add);
}


void flow_c::add_source_sheet(line_2d_c line, double sigma)
{
	source_sheet_c* point = new source_sheet_c(line,sigma);
	sheets.push_back(point);
}

}
