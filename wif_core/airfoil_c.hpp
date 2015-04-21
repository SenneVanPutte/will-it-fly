#ifndef __AIRFOIL_C_HPP_INCLUDED__
#define __AIRFOIL_C_HPP_INCLUDED__

#include <string>
#include <vector>
#include "line_2d_c.hpp"
#include <iterator>
#include <fstream>


namespace wif_core
{


class airfoil_c
{
public:
	/**
	 * makes a airfoil based on a .dat file in selig format.
	 * support for lednicer is upcoming
	 */
	airfoil_c(const std::string filename);

	/**
	 * makes an airfoil based on a std::vector of vector_2d_c.
	 */
	airfoil_c(const std::vector<vector_2d_c> iter);

	/**
	 * amount of points the airfoil_c contains
	 */
	unsigned int size() const;

	/**
	 * return the positions of the given point in the airfoil.
	 * Index can go from 0 to size()-1
	 */
	vector_2d_c & point(unsigned int index); //geen const, get poiunt geeft een reference terug dus kan dingen wijzigen.

	/**
	 * same as point(), but works with const airfoils, and gives a copy of the point ipv a reference
	 */
	vector_2d_c get_point(unsigned int index) const;
	//vector_2d_c get_point_after_dist(double distance) const;

	/**
	 * returns the given line. This will give the line that
	 * connects get_point(index) en get_point(index+1)
	 * Index can go from 0 to size()-2
	 * this does not give a reference, adapting this line will not change the airfoil.
	 */
	line_2d_c get_line(unsigned int index) const;

	/**
	 * calculates first intersection with a line
	 */
	vector_2d_c get_intersection_first(const line_2d_c) const;

	/**
	 * calculates last intersection with a line
	 */
	vector_2d_c get_intersection_last(const line_2d_c) const;

	/**
	 * makes new airfoil based on old airfoil using circle projection.
	 */
	airfoil_c get_circle_projection(uint32_t n, const vector_2d_c & projection_center) const;

private:

public:
	/**
	 * vector conatining all points of the airfoils, going in clockwize direction.
	 */
	std::vector<vector_2d_c> points;

private:





};






} // namespace wif_core

#endif // __AIRFOIL_C_HPP_INCLUDED__
