#ifndef __ADD_SHEET_C_HPP_INCLUDED__
#define __ADD_SHEET_C_HPP_INCLUDED__

#include "flow_c.hpp"
#include "vector_2d_c.hpp"
#include <memory>

namespace wif_core
{


enum E_CHOOSEFUNC
{
    /**
     * want to calculate phi
     */
    EC_PHI,

    /**
     * want to calculate psi
     */
    EC_PSI
};
/**
 * helper class for flow_accumulate_c
 */
class add_sheet_c
{
public:
	add_sheet_c(const vector_2d_c &, E_CHOOSEFUNC);

	~add_sheet_c();

	double operator()(double, std::shared_ptr<flow_c>) const;

	vector_2d_c operator()(vector_2d_c, std::shared_ptr<flow_c>) const;

	E_CHOOSEFUNC  what;

	vector_2d_c position;

};


}

#endif // ADD_SHEET_C_HPP
