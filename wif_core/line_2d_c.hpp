#ifndef __LINE_2D_C_INCLUDED__
#define __LINE_2D_C_INCLUDED__
#include "vector_2d_c.hpp"
#define EPSILON 0.00001

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
    vector_2d_c begin;
    vector_2d_c end;
    line_2d_c (vector_2d_c, vector_2d_c);
    line_2d_c (double, double, double, double);
    double get_length() const;
    double get_length_sq() const;
    vector_2d_c get_center_point() const;
    double get_angle() const; // Hoek met de x-as
    E_INTERSECTION get_intersection (const line_2d_c & other, vector_2d_c & intersection) const; // Returnt true als er een intersectie is, en zal deze opslaan in intersection.

private:
    vector_2d_c get_difference() const;


}; // class


std::ostream & operator << (std::ostream & , const line_2d_c & );

} // namespace wif_core

#endif // __LINE_2D_C_INCLUDED__

