#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

#include <wif_core/line_2d_c.hpp>

int main()
{
    std::cout << wif_core::get_version() << std::endl;
    std::cout << wif_algo::get_version() << std::endl;
    std::cout << wif_viz::get_version()  << std::endl;
    wif_core::line_2d_c line1(0,0,1,1);
    wif_core::line_2d_c line2(2,2,3,3);
    wif_core::vector_2d_c intersect(0,0);
    wif_core::E_INTERSECTION Eint = line1.get_intersection(line2,intersect);
    std::cout << Eint << line1 << line2 << intersect;

}
