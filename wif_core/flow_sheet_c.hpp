#ifndef __FLOW_SHEET_C_HPP_INCLUDED__
#define __FLOW_SHEET_C_HPP_INCLUDED__

#include "line_2d_c.hpp"
#include "vector_2d_c.hpp"



namespace wif_core
{

class flow_sheet_c
{
public:
	flow_sheet_c();

	flow_sheet_c(const line_2d_c &);

	virtual ~flow_sheet_c();

	flow_sheet_c(const flow_sheet_c & other);

	flow_sheet_c & operator=(const flow_sheet_c & other);

	/**
	 * gives the streamfunction at a given point
	 */
	double psi(const vector_2d_c &) const;

	/**
	 * gives the streamfunction at a given point
	 */
	double psi(double, double) const;

	/**
	 * the effect of an source,vortex,... on pos1 on psi in pos2
	 * should be implemented in derived classes
	 */
	virtual double psi_one_point(const vector_2d_c & pos1, const vector_2d_c & pos2) const = 0;

	/**
	 * gives the streampotential at a given point
	 */
	double phi(const vector_2d_c &) const;

	/**
	 * gives the streampotential at a given point
	 */
	double phi(double, double) const;

	/**
	 * the effect of an source,vortex,... on pos1 on phi in pos2
	 * should be implemented in derived classes
	 */
	virtual double phi_one_point(const vector_2d_c & pos1, const vector_2d_c & pos2) const = 0;

	/**
	 * gives the velocity at a given point
	 */
	vector_2d_c v(const vector_2d_c &) const;

	/**
	 * gives the velocity at a given point
	 */
	vector_2d_c v(double, double) const;

	/**
	 * the effect of an source,vortex,... on pos1 on v in pos2
	 * should be implemented in derived classes
	 */
	virtual vector_2d_c v_one_point(const vector_2d_c & pos1, const vector_2d_c & pos2) const = 0;

	/**
	 * gives a point on line corresponding to the
	 * parameter t
	 */
	vector_2d_c line_equation(double t) const;

	line_2d_c line;

protected:
	double psi_for_integration(double, const vector_2d_c &) const;

	double phi_for_integration(double, const vector_2d_c &) const;

	vector_2d_c v_for_integration(double, const vector_2d_c &) const;

private:

};

}

#endif // __FLOW_SHEET_HPP_INCLUDED__
