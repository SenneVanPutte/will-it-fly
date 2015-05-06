#include "visualization_root.hpp"

namespace wif_viz
{


visualization_root_c::visualization_root_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	visualization_c(flow, min_range, max_range)
{
	flow = flow;
	set_range(min_range, max_range);
}


visualization_root_c::~visualization_root_c()
{
	//
}

void visualization_root_c::draw(const std::string & filename)
{
	if(velocity_bins.x != 0 && velocity_bins.y != 0)
	{

	}

	if(psi_bins.x != 0 && psi_bins.y != 0)
	{
		const char * savename = filename.c_str();
		//const char* Drawtype=drawtype.c_str();
		//const char* Title=title.c_str();
		TCanvas * c1 = new TCanvas("c1", "c1", 600, 400);
		TH2F * harr = new TH2F("harr", "test", psi_bins.x, min_range.x, max_range.x, psi_bins.y, min_range.y, max_range.y);
		harr->GetXaxis()->SetTitle("X-positie");
		harr->GetYaxis()->SetTitle("Y-positie");

		wif_core::vector_2d_c pos;
		double stepsx = (max_range.x - min_range.x) / psi_bins.x;
		double stepsy = (max_range.y - min_range.y) / psi_bins.y;

		for(int i = 1; i <= psi_bins.x; i++)
		{
			for(int j = 1; j <= psi_bins.y; j++)
			{
				double evaluateX = min_range.x + i * stepsx - stepsx / 2;
				double evaluateY = min_range.y + j * stepsy - stepsy / 2;

				pos.x = evaluateX;
				pos.y = evaluateY;

				double bincontent = flow->get_psi(pos);
				harr->SetBinContent(i, j, bincontent);
			}
		}

		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		harr->Draw("CONT1Z");
		c1->SaveAs(savename);
		c1->Destructor();
		harr->~TH1();
	}

	if(phi_bins.x != 0 && phi_bins.y != 0)
	{
	}

}


} // namespace wif_viz
