#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

#include <memory>

using wif_core::source_sheet_c;
using wif_core::flow_c;
using std::cout;
using wif_core::vector_2d_c;
using wif_core::line_2d_c;
using wif_core::flow_accumulate_c;
using std::shared_ptr;
using std::make_shared;
using wif_core::source_sink_c;
using wif_core::vortex_sheet_c;
using wif_core::uniform_flow_c;

void test_source_sheets(source_sheet_c &);
void test_flow_acc();


int main()
{
	line_2d_c line = line_2d_c(5, 3, 1, 2);
	source_sheet_c sheet = source_sheet_c(line, 5);
	test_source_sheets(sheet);

	test_flow_acc();

	return 0;
}

void test_source_sheets(source_sheet_c & sheet)
{
	vector_2d_c pos = vector_2d_c(1, 1);
	cout << sheet.get_psi(pos) << "\n";
	cout << sheet.get_phi(pos) << "\n";
	vector_2d_c vec = sheet.get_velocity(pos);
	cout << vec.x << " " << vec.y << "\n";
}

void test_flow_acc()
{
	flow_accumulate_c flow = flow_accumulate_c();
	flow.add_source_sheet(line_2d_c(1, 1, 3, 5), 3);
	flow.add_source_sheet(line_2d_c(1, 1, 3, 5), 3);

	vector_2d_c pos = vector_2d_c(1, 1);

	cout << flow.get_psi(pos) << "\n";
	cout << flow.get_phi(pos) << "\n";
	vector_2d_c vec = flow.get_velocity(pos);
	cout << vec.x << " " << vec.y << "\n";

	flow.add_flow(make_shared<source_sink_c>(vector_2d_c(1, 0), 1));
	cout << flow.get_phi(pos) << "\n";
	flow.add_flow(make_shared<vortex_sheet_c>());
	cout << flow.get_psi(pos) << "\n";
	flow.add_flow(make_shared<uniform_flow_c>(1.6, 2));
	vector_2d_c vec2 = flow.get_velocity(pos);
	cout << vec2.x << " " << vec2.y << "\n";
}
