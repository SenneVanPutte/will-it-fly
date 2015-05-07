#ifndef __UNIFORM_FLOW_C_HPP_INCLUDED__
#define __UNIFORM_FLOW_C_HPP_INCLUDED__

#include "flow_c.hpp"
#include "vector_2d_c.hpp"


namespace wif_core
{


class uniform_flow_c : public flow_c
{
public:
	/**
	 * default:: angle=0 and u_infinity = 1
	 */
	uniform_flow_c();

	uniform_flow_c(double angle, double u);

	virtual ~uniform_flow_c();

	/**
	 * gives the streamfunction at a given position
	 */
	double get_psi(const vector_2d_c & position) const;

	/**
	 * gives the streampotential at a given position
	 */
	double get_phi(const vector_2d_c & position) const;

	/**
	 * gives the velocity at a given position
	 */
	vector_2d_c get_velocity(const vector_2d_c & position) const;

	/**
	 * gives the velocity of the uniform flow
	 */
	vector_2d_c get_velocity() const;

	double get_strength() const;

	double get_angle() const;

protected:

private:
	vector_2d_c U;

};


} // namespace wif_core


#endif // __UNIFORM_FLOW_C_HPP_INCLUDED__
