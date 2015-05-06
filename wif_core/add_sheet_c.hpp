#ifndef __ADD_SHEET_C_HPP_INCLUDED__
#define __ADD_SHEET_C_HPP_INCLUDED__


#include "flow_c.hpp"
#include "vector_2d_c.hpp"
#include <memory>


namespace wif_core
{


/**
 * helper class for flow_accumulate_c
 */
class add_sheet_phi_c
{
public:
	add_sheet_phi_c(const vector_2d_c &);

	~add_sheet_phi_c();

	double operator()(double, std::shared_ptr<flow_c>) const;

public:
	vector_2d_c position;

};


/**
 * helper class for flow_accumulate_c
 */
class add_sheet_psi_c
{
public:
	add_sheet_psi_c(const vector_2d_c &);

	~add_sheet_psi_c();

	double operator()(double, std::shared_ptr<flow_c>) const;

public:
	vector_2d_c position;

};


/**
 * helper class for flow_accumulate_c
 */
class add_sheet_v_c
{
public:
	add_sheet_v_c(const vector_2d_c &);

	~add_sheet_v_c();

	vector_2d_c operator()(vector_2d_c, std::shared_ptr<flow_c>) const;

public:
	vector_2d_c position;

};


} // namespace wif_core


#endif // __ADD_SHEET_C_HPP_INCLUDED__
