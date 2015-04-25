#ifndef __SOURCE_SINK_C_HPP_INCLUDED__
#define __SOURCE_SINK_C_HPP_INCLUDED__

#include "flow_c.hpp"
#include "vector_2d_c.hpp"

namespace wif_core
{


class source_sink_c : public flow_c
{
public:
	/**
	 * Default: source at (0,0) with sigma = 1
	 */
	source_sink_c();

	source_sink_c(const vector_2d_c &, double);

	virtual ~source_sink_c();

	/**
	 * gives the streamfunction at a given possition
	 */
	double get_psi(const vector_2d_c &) const;

	/**
	 * gives the streampotential at a given possition
	 */
	double get_phi(const vector_2d_c &) const;

	/**
	 * gives the velocity at a given possition
	 */
	vector_2d_c get_velocity(const vector_2d_c &) const;

protected:
private:
	vector_2d_c location;
	double sigma;
};


}
#endif // __SOURCE_SINK_C_HPP_INCLUDED__
