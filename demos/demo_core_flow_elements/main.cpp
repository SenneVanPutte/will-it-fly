#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

using wif_core::source_sheet_c;
using wif_core::flow_c;
using std::cout;
using wif_core::vector_2d_c;
using wif_core::line_2d_c;
using wif_core::flow_accumulate_c;

void test_source_sheets(source_sheet_c&);
void test_flow_acc();


int main()
{
	line_2d_c line = line_2d_c(5,3,1,2);
	source_sheet_c sheet = source_sheet_c(line,5);
	//test_source_sheets(sheet);

	test_flow_acc();

	return 0;
}

void test_source_sheets(source_sheet_c& sheet)
{
	cout << sheet.get_psi(vector_2d_c(1,1)) << "\n";
	cout << sheet.get_phi(vector_2d_c(1,1)) << "\n";
	vector_2d_c vec = sheet.get_velocity(vector_2d_c(1,1));
	cout << vec.x << " " << vec.y << "\n";
}

void test_flow_acc()
{
	flow_accumulate_c flow= flow_accumulate_c();
	flow.add_source_sheet(line_2d_c(1,1,3,5),3);

	vector_2d_c pos = vector_2d_c(8,5);

	cout << flow.get_psi(pos) << "\n";
	cout << flow.get_phi(pos) << "\n";
	vector_2d_c vec = flow.get_velocity(pos);
	cout << vec.x << " " << vec.y << "\n";
}
