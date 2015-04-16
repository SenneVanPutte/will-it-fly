#include "vector_2d_c.hpp"

namespace wif_core
{

vector_2d_c::vector_2d_c(double const x , double const y) : x (x), y (y)
{
}

/*vector_2d_c::vector_2d_c(vector_2d_c & other) : x (other.x), y (other.y)
{
}*/

vector_2d_c::vector_2d_c() : x (0), y (0)
{
}


vector_2d_c vector_2d_c::operator+ (vector_2d_c const other) const
{
    vector_2d_c r(x + other.x, y + other.y);
    return (r);
}

vector_2d_c vector_2d_c::operator-() const
{
    vector_2d_c r(-x, -y);
    return (r);
}

vector_2d_c vector_2d_c::operator- (vector_2d_c const other) const
{
    vector_2d_c r(x-other.x, y-other.y);
    return (r);
}

vector_2d_c vector_2d_c::operator* (double const n) const
{
    vector_2d_c r(n * x, n * y);
    return (r);
}

vector_2d_c vector_2d_c::operator/ (double const n) const
{
    vector_2d_c r(x / n, y / n);
    return (r);
}


void vector_2d_c::operator+= (vector_2d_c const other)
{
    x += other.x;
    y += other.y;
}

void vector_2d_c::operator-= (vector_2d_c const other)
{
    x -= other.x;
    y -= other.y;
}

void vector_2d_c::operator*= (double const n)
{
    x *= n;
    y *= n;
}

void vector_2d_c::operator/= (double const n)
{
    x /= n;
    y /= n;
}

double vector_2d_c::get_lenght() const
{
    return(sqrt(get_lenght_sq()));
}

double vector_2d_c::get_lenght_sq() const
{
    return(x*x+y*y);
}

double vector_2d_c::get_angle() const
{
    return(atan2(y,x));
}

vector_2d_c operator * (double n, vector_2d_c vec)
{
    vector_2d_c r(n*vec.x,n*vec.y);
    return(r);
};



std::ostream & operator << (std::ostream& output,const vector_2d_c & vec)
{
    output << "(" << vec.x << ", " << vec.y << ")";
    return(output);
};



} // namespace wif_core
