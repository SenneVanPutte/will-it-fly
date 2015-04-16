#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>


int main()
{
    std::cout << wif_core::get_version() << std::endl;
    std::cout << wif_algo::get_version() << std::endl;
    std::cout << wif_viz::get_version()  << std::endl;

    for (double i = 0; i < 10; i++)
    {
        for (double j = 0; j < 10; j++)
        {
            for (double k = 0; k < 10; k++)
            {
                wif_core::line_2d_c line1(0, 0, i, j);
                wif_core::line_2d_c line2(j,i, k, k);
                wif_core::vector_2d_c intersect(0, 0);
                wif_core::E_INTERSECTION Eint = line1.get_intersection(line2, intersect);
                std::cout << line1 <<  " and " << line2 <<  "-> " << Eint << " in " << intersect << std::endl;
            }
        }
    }
}
