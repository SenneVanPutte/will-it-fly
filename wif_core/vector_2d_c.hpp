#ifndef __VECTOR_2D_C_HPP_INCLUDED__
#define __VECTOR_2D_C_HPP_INCLUDED__

#include <cmath>
#include <ostream>

namespace wif_core
{


class vector_2d_c
{
public:
    vector_2d_c(double x, double y); /// constuctior with x,y

    vector_2d_c();

    vector_2d_c(const vector_2d_c & other); /// copy contuctor

    vector_2d_c & operator=(const vector_2d_c & other);

    vector_2d_c operator+(const vector_2d_c & other) const; /// normal addition

    vector_2d_c operator-() const; /// returns negative vector

    vector_2d_c operator-(const vector_2d_c & other) const; /// normal substaction

    vector_2d_c operator*(double r) const;

    vector_2d_c operator/(double r) const;

    vector_2d_c & operator+=(const vector_2d_c & other); /// modifies vector, adds seconds vector

    vector_2d_c & operator-=(const vector_2d_c & other); /// modifies vector, substacts seconds vector

    vector_2d_c & operator*=(double r); /// modifies vector , multiplices

    vector_2d_c & operator/=(double r); /// modifies vector , multiplices

    double get_length() const;/// lenght of vector

    double get_length_sq() const;/// same as pow(get_length(),2) but faster

    double get_angle() const; ///angle with x-axis

    double cross(const vector_2d_c & other) const; ///magnetude of 3d cross product. Used in intersection math.

public:
    double x;
    double y;
};


vector_2d_c operator *(double, const vector_2d_c &);


std::ostream & operator << (std::ostream &, const vector_2d_c &);


} // namespace wif_core

#endif // __VECTOR_2D_C_HPP_INCLUDED__

