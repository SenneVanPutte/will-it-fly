#ifndef __FLOWS_C_HPP_INCLUDED__
#define __FLOWS_C_HPP_INCLUDED__

#include "flow_sheet_c.hpp"
#include "vector_2d_c.hpp"
#include <vector>

namespace wif_core
{

class flow_c
{
public:
	flow_c();

	/**
	 * constructor for only a uniform flow
	 */
	flow_c(const vector_2d_c &);

	/**
	 * constructor with uniform flow and vector of pointers to flow_sheets
	 */
	//flow_c(const vector_2d_c&, const std::vector<flow_sheet_c*>&);

	virtual ~flow_c();

	flow_c(const flow_c & other);

	flow_c & operator=(const flow_c & other);

	/**
	 * gives the streamfunction at a given point
	 */
	//double psi(double, double) const;

	/**
	 * gives the streamfunction at a given point
	 */
	double psi(vector_2d_c) const;

	/**
	 * gives the streampotential at a given point
	 */
	//double phi(double, double) const;

	/**
	 * gives the streampotential at a given point
	 */
	double phi(vector_2d_c) const;

	/**
	 * gives the velocity
	 */
	//vector_2d_c v(double,double) const;

	/**
	 * gives the velocity
	 */
	vector_2d_c v(vector_2d_c) const;

	bool empty_sheets();

	/**
	 * temporary function for testing
	 */
	void add_source_sheet(line_2d_c, double);

protected:

private:

public:
	std::vector<flow_sheet_c *> sheets;

	/**
	 * the velocity at infinity/ uniform flow
	 */
	vector_2d_c U;
};



}
#endif // __FLOWS_HPP_INCLUDED__
