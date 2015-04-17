#ifndef __LINE_2D_C_HPP_INCLUDED__
#define __LINE_2D_C_HPP_INCLUDED__

#include "vector_2d_c.hpp"

namespace wif_core
{


enum E_INTERSECTION
{
	EI_PARALLEL,
	EI_OUTSIDE,
	EI_SEGMENT,
	EI_COINCIDENT,
	EI_COINCIDENT_OUTSIDE
};


class line_2d_c
{
public:
	line_2d_c(const vector_2d_c &, const vector_2d_c &);

	line_2d_c(double x1, double y1, double x2, double y2);

	double get_length() const;

	double get_length_sq() const;

	vector_2d_c get_center_point() const;

	double get_angle() const; // Hoek met de x-as
    /**
     * Calculates whether 2 line segments intersect or not, and sets the vector intersect on the intersection.
     * different results are:
	 * EI_PARALLEL: line segments are parallel. Intersection is set to bodycenter of end points.
	 * EI_OUTSIDE: line segments do not intersect, but lines do. Intersection is set at line intersection.
	 * EI_SEGMENT: line segments do intersect. Intersection is set at line intersection.
	 * EI_COINCIDENT: line segments overlap, intersection is set to middel of overlapping section.
	 * EI_COINCIDENT_OUTSIDE: line segments do not overlap, but lines do. intersection is set to middel of overlapping section.
    */
	E_INTERSECTION get_intersection(const line_2d_c & other, vector_2d_c & intersection, double epsilon=0.001) const; // Returnt true als er een intersectie is, en zal deze opslaan in intersection.

private:
	vector_2d_c get_difference() const;

public:
	vector_2d_c begin;
	vector_2d_c end;
};


std::ostream & operator << (std::ostream & , const line_2d_c &);


} // namespace wif_core


#endif // __LINE_2D_C_HPP_INCLUDED__

