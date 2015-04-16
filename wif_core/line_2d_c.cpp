#include "line_2d_c.hpp"

namespace wif_core
{
line_2d_c::line_2d_c( vector_2d_c begin, vector_2d_c end ) : begin( begin ), end( end ) {};

line_2d_c::line_2d_c(double x1,double y1,double x2, double y2) : begin( vector_2d_c(x1,y1) ), end(  vector_2d_c(x2,y2)  ) {};

vector_2d_c line_2d_c::get_difference() const
{
    return ( end - begin );
}


double line_2d_c::get_length() const
{
    return ( get_difference().get_length() );
}

double line_2d_c::get_length_sq() const
{
    return ( get_difference().get_length_sq() );
}

double line_2d_c::get_angle() const
{
    return ( get_difference().get_angle() );
}

vector_2d_c line_2d_c::get_center_point() const
{
    return ( ( begin + end ) / 2 );
}

E_INTERSECTION line_2d_c::get_intersection( const line_2d_c & other, vector_2d_c & intersection ) const
{
    //check eindpunten
    vector_2d_c dif1 = get_difference();
    vector_2d_c dif2 = other.get_difference();
    vector_2d_c bdif = other.begin - begin;
    if( abs( dif1.cross( dif2 ) ) < EPSILON ) //evenwijdig of samenvallend
    {
        if( abs( bdif.cross( dif1 ) ) < EPSILON ) //als het lijnstuk tussen 2 van de eindpunte ook evenwijdig is, vallen ze samen
        {
            double begin_second = bdif.get_length() / dif1.get_length(); ///0 is begin_first, 1= end_first
            double end_second = ( bdif + dif2 ).get_length() / dif1.get_length();
            double min_second = begin_second > end_second ? end_second : begin_second;
            double max_second = begin_second < end_second ? end_second : begin_second;
            if( max_second < 0 )
            {
                intersection = begin + max_second / 2 * dif1;
                return( EI_COINCIDENT_OUTSIDE );
            }
            else if( min_second > 1 )
            {
                intersection = begin + ( min_second / 2 + 0.5 ) * dif1;
                return( EI_COINCIDENT_OUTSIDE );
            }
            else
            {
                double inter_dist = (( min_second > 0 ? min_second : 0 ) + ( max_second < 1 ? max_second : 1 ))/2;
                intersection = begin + inter_dist * dif1;
                return( EI_COINCIDENT );
            }
        }
        else
        {
            intersection = ( begin + end + other.begin + other.end ) / 4;
            return ( EI_PARALLEL );
        }
    }
    double rel_dist1 = bdif.cross( dif2 ) / dif1.cross( dif2 ); //aftand van het beginpuntn tot de intersectie gedeelt door de vector
    double rel_dist2 = bdif.cross( dif1 ) / dif1.cross( dif2 ); //aftand van het beginpuntn tot de intersectie gedeelt door de vector
    intersection = rel_dist1 * dif1 + begin;//positie van de intersectie
    return ( ( ( rel_dist1 >= 0 ) & ( rel_dist1 <= 1 ) & ( rel_dist2 >= 0 ) & ( rel_dist2 <= 1 ) ) ? EI_SEGMENT : EI_OUTSIDE );
}
std::ostream & operator << (std::ostream& output,const line_2d_c & line)
{
    output << "[" << line.begin << ", " << line.end << "]";
    return(output);
};


}
