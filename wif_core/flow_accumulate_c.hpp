#ifndef __FLOWS_ACCUMULATE_C_HPP_INCLUDED__
#define __FLOWS_ACCUMULATE_C_HPP_INCLUDED__

#include "flow_c.hpp"
#include "vector_2d_c.hpp"
#include <vector>
#include "line_2d_c.hpp"
#include <memory>
#include "airfoil_c.hpp"

using std::vector;
using std::shared_ptr;

namespace wif_core
{

class flow_accumulate_c : public flow_c
{
public:
	flow_accumulate_c();

	flow_accumulate_c(const vector<shared_ptr<flow_c>> & flow);

	flow_accumulate_c(shared_ptr<flow_c> flow);

	//flow_accumulate_c(const vector<double> & sigmas, const airfoil_c & foil);

	virtual ~flow_accumulate_c();

	/**
	 * adds a flow object to flows
	 */
	void add_flow(shared_ptr<flow_c> flow);

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

	/**
	 * adds a source sheet to flows on a line and with strength sigma
	 */
	void add_source_sheet(line_2d_c line, double sigma);

	/**
	 * add a vortex sheet to flows on a line and with strength lambda
	 */
	void add_vortex_sheet(line_2d_c line, double lambda);

	void airfoil_to_source_sheet(const vector<double> & sigmas, const airfoil_c & foil);

	void airfoil_to_vortex_sheet(double strenght, const airfoil_c & foil);

protected:

private:
	vector<shared_ptr<flow_c>> flows;
};




}
#endif // __FLOWS_HPP_INCLUDED__
