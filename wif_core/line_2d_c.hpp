#ifndef __LINE_2D_C_HPP_INCLUDED__
#define __LINE_2D_C_HPP_INCLUDED__

#include "vector_2d_c.hpp"

namespace wif_core
{


enum E_INTERSECTION
{
	/**
	 * line segments are parallel.
	 */
	EI_PARALLEL,

	/**
	 * line segments do not intersect, but lines do.
	 */
	EI_OUTSIDE,

	/**
	 * line segments intersect.
	 */
	EI_SEGMENT,

	/**
	 * line segments overlap,
	 */
	EI_COINCIDENT,

	/**
	 * line segments do not overlap, but lines do.
	*/
	EI_COINCIDENT_OUTSIDE
};


class line_2d_c
{
public:
	line_2d_c(const vector_2d_c &, const vector_2d_c &);

	line_2d_c(double x1, double y1, double x2, double y2);

	/**
	 * calculates lenght of line
	 */
	double get_length() const;

	/**
	 * calculates lenght of line squared. Faster then pow(get_length(),2)
	 */
	double get_length_sq() const;

	/**
	 * returns vector point
	 */
	vector_2d_c get_center_point() const;

	/**
	 * angle the line makes with x-axis in radians
	 */
	double get_angle() const;

	/**
	 * Calculates whether 2 line segments intersect or not, and sets the vector intersect on the intersection.
	 * different results are:
	 * EI_PARALLEL:  intersection is set to bodycenter of end points
	 * EI_OUTSIDE:   intersection is set at line intersection
	 * EI_SEGMENT: line segments do intersect. Intersection is set at line intersection
	 * EI_COINCIDENT:  intersection is set to middle of overlapping section
	 * EI_COINCIDENT_OUTSIDE: intersection is set to middel of overlapping section
	 */
	E_INTERSECTION get_intersection(const line_2d_c & other, vector_2d_c & intersection, double epsilon=0.001) const;

private:
	vector_2d_c get_difference() const;

public:
	vector_2d_c begin;
	vector_2d_c end;
};


std::ostream & operator << (std::ostream & , const line_2d_c &);


} // namespace wif_core


#endif // __LINE_2D_C_HPP_INCLUDED__

