#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>


std::string get_intersection_str(wif_core::E_INTERSECTION ei)
{
	switch(ei)
	{
		case wif_core::EI_PARALLEL:
			return "PARALLEL";

		case wif_core::EI_OUTSIDE:
			return "OUTSIDE";

		case wif_core::EI_SEGMENT:
			return "SEGMENT";

		case wif_core::EI_COINCIDENT:
			return "COINCIDENT";

		case wif_core::EI_COINCIDENT_OUTSIDE:
			return "COINCIDENT_OUTSIDE";

		default:
			return "ERROR";
	}
}


void demo_print_vector(const wif_core::vector_2d_c & v1, const wif_core::vector_2d_c & v2, const std::string & v3_name, const wif_core::vector_2d_c & v3)
{
	std::cout << "v1: " << v1 << ", v2: " << v2 << ", " << v3_name.c_str() << ": " << v3 << std::endl;
}


void demo_vectors()
{
	std::cout << "Demo vectors:" << std::endl;

	wif_core::vector_2d_c v1(1, 0);
	wif_core::vector_2d_c v2(0, 1);

	demo_print_vector(v1, v2, "v1 + v2", v1 + v2);
	demo_print_vector(v1, v2, "v1 - v2", v1 - v2);
}


void demo_intersection(const wif_core::line_2d_c & line1, const wif_core::line_2d_c & line2)
{
	wif_core::vector_2d_c intersect(0, 0);
	wif_core::E_INTERSECTION ei = line1.get_intersection(line2, intersect);

	std::cout << line1 <<  " and " << line2 <<  "-> " << get_intersection_str(ei).c_str() << " in " << intersect << std::endl;
}


int main()
{
	std::cout << wif_core::get_version() << std::endl;
	std::cout << wif_algo::get_version() << std::endl;
	std::cout << wif_viz::get_version()  << std::endl;

	demo_vectors();

	wif_core::vector_2d_c vec1(1, 0);
	wif_core::vector_2d_c vec2(0, 1);
	std::cout << vec1 << ";" << vec2 << ";"   << vec1 + vec2 << ";" << vec1 - vec2 << ";"
	          << vec1 * 2 << ";" << vec1 / 2 << ";" ;
	std::cout << (vec1 += vec2) << ";" ;
	std::cout << (vec2 -= vec1) << ";" ;
	std::cout << (vec1 *= 2) << ";" ;
	std::cout << (vec1 /= 2);
	demo_intersection(wif_core::line_2d_c(0, 0, 1, 1), wif_core::line_2d_c(0, 1, 1, 0));
	demo_intersection(wif_core::line_2d_c(0, 0, -1, -1), wif_core::line_2d_c(0, 1, 1, 0));
	demo_intersection(wif_core::line_2d_c(0, 0, -1, 1), wif_core::line_2d_c(0, 1, 1, 0));
	demo_intersection(wif_core::line_2d_c(0, 0, 2, 1), wif_core::line_2d_c(0, 1, 1, 0));
	demo_intersection(wif_core::line_2d_c(0, 0, 2, 2), wif_core::line_2d_c(1, 1, 3, 3));
	demo_intersection(wif_core::line_2d_c(0, 0, 1, 1), wif_core::line_2d_c(2, 2, 3, 3));
	demo_intersection(wif_core::line_2d_c(0, 0, 1, 1), wif_core::line_2d_c(1, 1, 2, 2));

}
