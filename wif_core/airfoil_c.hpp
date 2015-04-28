#ifndef __AIRFOIL_C_HPP_INCLUDED__
#define __AIRFOIL_C_HPP_INCLUDED__

#include <string>
#include <vector>
#include "line_2d_c.hpp"



namespace wif_core
{


class airfoil_c
{
public:
	/**
	 * Empty constructor. Gives an airfoil without points nor lines.
	 */
	airfoil_c();

	/**
	 * Read the file's data
	 */
	airfoil_c(const std::string & filename);

	/**
	 * Create airfoil with given name and vector
	 */
	airfoil_c(std::vector<vector_2d_c> & points, const std::string & name);

	/**
	 * New airfoil named old name + " circle projected with $n subdivisions centered on $projection_center with radius $radius".
	 */
	airfoil_c get_circle_projection(uint32_t n, const vector_2d_c & projection_center, double radius, double epsilon = 0.0001) const;

	/**
	 * Check if the last points is the same as the first, within a certain error
	 */
	bool is_closed(double epsilon = 0.0001) const;

	/**
	 * Check if the airfoil contains at least 1 point.
	 */
	bool is_valid() const;

	/**
	 * Makes pairss ([i], [i+1]) lines, with i = 0 to points.size()-1.
	 */
	std::vector<line_2d_c> get_lines() const;

	/**
	 * Same as get_lines() but in the reversed order
	 */
	std::vector<line_2d_c> get_lines_reversed() const;


	/**
	 * Gives the name
	 */
	std::string get_name() const;

	void set_name(const std::string & new_name);

private:
	/**
	 * returns first intersection with line
	 */
	vector_2d_c get_intersection_last(const line_2d_c & line) const;

	/**
	 * returns last intersection with line
	 */
	vector_2d_c get_intersection_first(const line_2d_c & line) const;

private:
	std::vector<vector_2d_c> points;
	std::string name;

	friend std::ostream & operator << (std::ostream & output, const airfoil_c & airfoil);

};


std::ostream & operator << (std::ostream & output, const airfoil_c & airfoil);

} // namespace wif_core

#endif // __AIRFOIL_C_HPP_INCLUDED__
