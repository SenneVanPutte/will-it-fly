#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

using wif_core::source_sheet;
using wif_core::flow_sheet;
using std::cout;
using wif_core::vector_2d_c;
using wif_core::line_2d_c;

void test_source_sheets(source_sheet&);


int main()
{
	line_2d_c line = line_2d_c(5,3,1,2);
	source_sheet sheet = source_sheet(line,5);
	test_source_sheets(sheet);


	return 0;
}

void test_source_sheets(source_sheet& sheet)
{
	cout << sheet.psi(1,1) << "\n";
	cout << sheet.phi(1,1) << "\n";
	vector_2d_c vec = sheet.v(1,1);
	cout << vec.x << " " << vec.y << "\n";
}
