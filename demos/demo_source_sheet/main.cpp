#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

using wif_core::source_sheet_c;
using wif_core::flow_sheet_c;
using std::cout;
using wif_core::vector_2d_c;
using wif_core::line_2d_c;
using wif_core::flow_c;

void test_source_sheets(source_sheet_c &);
void test_flow();


int main()
{
	line_2d_c line = line_2d_c(5, 3, 1, 2);
	source_sheet_c sheet = source_sheet_c(line, 5);
	test_source_sheets(sheet);

	void test_flow();

	return 0;
}

void test_source_sheets(source_sheet_c & sheet)
{
	cout << sheet.psi(1, 1) << "\n";
	cout << sheet.phi(1, 1) << "\n";
	vector_2d_c vec = sheet.v(1, 1);
	cout << vec.x << " " << vec.y << "\n";
}

void test_flow()
{
	flow_c flow = flow_c(vector_2d_c(1, 3));
	flow.add_source_sheet(line_2d_c(1, 1, 3, 5), 3);

	vector_2d_c pos = vector_2d_c(1, 1);

	cout << flow.psi(pos) << "\n";
	cout << flow.phi(pos) << "\n";
	vector_2d_c vec = flow.v(pos);
	cout << vec.x << " " << vec.y << "\n";
}
