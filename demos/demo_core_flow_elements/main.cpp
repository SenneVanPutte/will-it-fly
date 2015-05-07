#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

#include "THistPainter.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TImage.h"

using wif_core::source_sheet_c;
using wif_core::flow_c;
using wif_core::uniform_flow_c;
using std::cout;
using wif_core::vector_2d_c;
using wif_core::line_2d_c;
using wif_core::flow_accumulate_c;

void test_source_sheets(source_sheet_c &);
void test_flow_acc();
void draw_source_sheet();


int main()
{
	//line_2d_c line = line_2d_c(5, 3, 1, 2);
	//source_sheet_c sheet = source_sheet_c(line, 5);
	//test_source_sheets(sheet);

	draw_source_sheet();

	test_flow_acc();

	return 0;
}

void test_source_sheets(source_sheet_c & sheet)
{
	cout << sheet.get_psi(vector_2d_c(1, 1)) << "\n";
	cout << sheet.get_phi(vector_2d_c(1, 1)) << "\n";
	vector_2d_c vec = sheet.get_velocity(vector_2d_c(1, 1));
	cout << vec.x << " " << vec.y << "\n";
}

void test_flow_acc()
{
	shared_ptr<source_sheet_c> point = std::make_shared<source_sheet_c>();
	flow_accumulate_c flow = flow_accumulate_c(point);
	//flow.add_source_sheet(line_2d_c(1,2,3,4), 3);
	//flow.add_source_sheet(line_2d_c(3, 5, 6, 1), 2);

	vector_2d_c pos = vector_2d_c(1, 1);

	cout << "ttttt" << std::endl;
	cout << flow.get_psi(pos) << "\n";
	cout << flow.get_phi(pos) << "\n";
	vector_2d_c vec = flow.get_velocity(pos);
	cout << vec.x << " " << vec.y << "\n";
}

void draw_source_sheet()
{

	TCanvas * c1 = new TCanvas("c1", "c1", 600, 600);

	vector<double> sigmas(20, 2);
	wif_core::airfoil_c foilfull = wif_core::airfoil_c("/home/uauser/eindopdracht/will-it-fly/wif_core/airfoils/selig.dat");
	cout << "loaded";
	wif_core::airfoil_c foil = foilfull.get_circle_projection(4, vector_2d_c(0.5, 0), 0.5, 0.001);

	cout << foil;
	flow_accumulate_c flow = flow_accumulate_c();
	//flow_accumulate_c flow = flow_accumulate_c();
	//flow.add_flow(std::make_shared<source_sheet_c>(line_2d_c(0, -1, 0, 1), 2));
	//flow.add_flow(std::make_shared<uniform_flow_c>(0, 3));

	flow.add_source_sheets(sigmas, foil);
	//flow.add_vortex_sheets(1, foil);

	/*cout << flow.get_psi(pos) << "\n";
	cout << flow.get_phi(pos) << "\n";*/

	double xmin = -3;
	double xmax = 3;
	double ymin = -3;
	double ymax = 3;

	int lx = 1000;
	int ly = 1000;

	TH2F * hist = new TH2F("hist", "name", lx, xmin, xmax, ly, ymin, ymax);

	int xbinmax = hist->GetXaxis()->GetLast();
	int ybinmax = hist->GetYaxis()->GetLast();

	for(int i = hist->GetXaxis()->GetFirst(); i <= xbinmax; i++)
	{
		for(int j = hist->GetYaxis()->GetFirst(); j <= ybinmax; j++)
		{
			double x = hist->GetXaxis()->GetBinCenter(i);
			double y = hist->GetYaxis()->GetBinCenter(j);

			double a = flow.get_psi(vector_2d_c(x, y));

			hist->SetBinContent(i, j, atan(a));

		}
	}

	hist->SetContour(100);

	for(int i = 0; i < 100; i++)
	{
		hist->SetContourLevel(i, i * M_PI / 50 - M_PI);
	}

	hist->GetXaxis()->SetTitle("x");
	hist->GetYaxis()->SetTitle("Y");
	hist->SetStats(0);
	hist->SetLineColor(1);

	hist->Draw("CONT3");
	TImage * img = TImage::Create();

	img->FromPad(c1);
	img->WriteImage("demo.png");

	delete hist;
	delete img;
	delete c1;


}
