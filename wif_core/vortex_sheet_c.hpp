#ifndef __VORTEX_SHEET_C_HPP_INCLUDED__
#define __VORTEX_SHEET_C_HPP_INCLUDED__

#include "flow_c.hpp"
#include "line_2d_c.hpp"

namespace wif_core
{

class vortex_sheet_c : public flow_c
{
public:
	/**
	 * default: line from (-1,0) to (1,0) and lambda = 1.0
	 */
	vortex_sheet_c();

	/**
	 * creates a vortex sheet on a given line with a given strength
	 */
	vortex_sheet_c(const line_2d_c & line, double lambda);

	virtual ~vortex_sheet_c();

	/**
	 * gives the streamfunction at a given point
	 */
	double get_psi(const vector_2d_c & position) const;

	/**
	 * gives the streampotential at a given point
	 */
	double get_phi(const vector_2d_c & position) const;

	/**
	 * gives the velocity at a given point
	 */
	vector_2d_c get_velocity(const vector_2d_c & position) const;

protected:
private:
	line_2d_c line;
	double lambda;
};

}

#endif
