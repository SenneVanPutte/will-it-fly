#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>


void demo_intersection(wif_core::line_2d_c const line1,
               wif_core::line_2d_c const line2)
{
    wif_core::vector_2d_c intersect(0, 0);
    wif_core::E_INTERSECTION Eint = line1.get_intersection(line2, intersect);
    std::cout << line1 <<  " and " << line2 <<  "-> " << Eint << " in " << intersect << std::endl;
}


int main()
{
    std::cout << wif_core::get_version() << std::endl;
    std::cout << wif_algo::get_version() << std::endl;
    std::cout << wif_viz::get_version()  << std::endl;
    wif_core::vector_2d_c vec1(1,0);
    wif_core::vector_2d_c vec2(0,1);
    std::cout << vec1 << ";" << vec2 << ";"   << vec1+vec2 << ";" << vec1-vec2 << ";"
              << vec1*2<< ";" <<vec1/2<< ";" ;
    std::cout << (vec1+=vec2) << ";" ;
    std::cout << (vec2-=vec1) << ";" ;
    std::cout << (vec1*=2) << ";" ;
    std::cout << (vec1/=2);
    std::cout << "\n0:EI_PARALLEL\n1:EI_OUTSIDE\n2:EI_SEGMENT\n3:EI_COINCIDENT\n4:EI_COINCIDENT_OUTSIDE\n";
    demo_intersection(wif_core::line_2d_c(0,0,1,1),wif_core::line_2d_c(0,1,1,0));
    demo_intersection(wif_core::line_2d_c(0,0,-1,-1),wif_core::line_2d_c(0,1,1,0));
    demo_intersection(wif_core::line_2d_c(0,0,-1,1),wif_core::line_2d_c(0,1,1,0));
    demo_intersection(wif_core::line_2d_c(0,0,2,1),wif_core::line_2d_c(0,1,1,0));
    demo_intersection(wif_core::line_2d_c(0,0,2,2),wif_core::line_2d_c(1,1,3,3));
    demo_intersection(wif_core::line_2d_c(0,0,1,1),wif_core::line_2d_c(2,2,3,3));
    demo_intersection(wif_core::line_2d_c(0,0,1,1),wif_core::line_2d_c(1,1,2,2));

}
