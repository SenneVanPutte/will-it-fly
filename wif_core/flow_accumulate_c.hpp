#ifndef __FLOWS_ACCUMULATE_C_HPP_INCLUDED__
#define __FLOWS_ACCUMULATE_C_HPP_INCLUDED__


#include <memory>
#include <vector>

#include "airfoil_c.hpp"
#include "flow_c.hpp"
#include "line_2d_c.hpp"
#include "vector_2d_c.hpp"


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

	/**
	 * adds source sheets with lines on the airfoil and strenghts given in sigmas
	 */
	void add_source_sheets(const vector<double> & sigmas, const airfoil_c & foil);

	/**
	 * adds vortex sheets with lines on the airfoil and a given strenght.
	 */
	void add_vortex_sheets(double strength, const airfoil_c & foil);

protected:

private:
	vector<shared_ptr<flow_c>> flows;

};


} // namespace wif_core

#endif // __FLOWS_ACCUMULATE_HPP_INCLUDED__

