#include "visualization_root.hpp"
#include <vector>
#include "TROOT.h"
#include "TArrow.h"
#include "THistPainter.h"
#include "TCanvas.h"
#include "TH2.h"
#include <iostream>
#include "TStyle.h"
#include "TF2.h"
namespace wif_viz
{


visualization_root_c::visualization_root_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range) :
	visualization_c(flow, min_range, max_range)
{
	Flow = flow;
}


visualization_root_c::~visualization_root_c()
{
	//
}

void visualization_root_c::draw(const std::string & filename)
{
	FillBins();
	//fillbinStagnatie();
	/*if(velocity_bins.x != 0 && velocity_bins.y != 0)
	{
		//std::string filename1 = filename + "velocity";
		//const char * savename = filename1.c_str();

		const char * savename1 = filename.c_str();
		std::cout<<"making canvas"<std::endl;
		TCanvas * c = new TCanvas("c", "c", 1000, 1000);
		std::cout<<"canvas made"<std::endl;
		//velocity->SetContour(number_of_contours, contour_locations);
		velocity->Draw("CONT1Z");
		addArrows();
		stag->Draw("CONT1 same");
		velocity->GetXaxis()->SetTitle("x");
		velocity->GetYaxis()->SetTitle("y");
		velocity->GetXaxis()->CenterTitle();
		velocity->GetYaxis()->CenterTitle();
		velocity->SetTitle("contour plot velocity");
		std::cout << "saving";
		c->SaveAs(savename1);
		c->Destructor();
	}*/

	if(psi_bins.x != 0 && psi_bins.y != 0)
	{
		std::string filename2 = filename+"psi.pdf";
		const char * savename = filename2.c_str();
		TCanvas * c = new TCanvas("c", "c", 1000, 1000);
		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		psi->Draw("CONT1Z");
		psi->GetXaxis()->SetTitle("x");
		psi->GetYaxis()->SetTitle("y");
		psi->GetXaxis()->CenterTitle();
		psi->GetYaxis()->CenterTitle();
		psi->SetTitle("psi");
		c->SaveAs(savename);
		c->Destructor();
	}

	if(phi_bins.x != 0 && phi_bins.y != 0)
	{
		std::string filename3 = filename + "phi.pdf";
		const char * savename = filename3.c_str();
		TCanvas * c = new TCanvas("c", "c", 1000, 1000);
		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		/*double_t contours[contour_locations.size()];
		for(unsigned int i=0;i<contour_locations.size();i++)
		{
		contours[i]=contour_locations[i];
		}

		phi->SetContour(contour_locations.size(), contours);*/
		phi->Draw("CONT1Z");
		phi->GetXaxis()->SetTitle("x");
		phi->GetYaxis()->SetTitle("y");
		phi->GetXaxis()->CenterTitle();
		phi->GetYaxis()->CenterTitle();
		phi->SetTitle("contour plot phi");
		c->SaveAs(savename);
		c->Destructor();
	}

}

void visualization_root_c::FillBins()
{
	if(velocity_bins.x!=0 && velocity_bins.y!=0)
	{
		velocity = new TH2F("harr", "test", velocity_bins.x, min_range.x, max_range.x, velocity_bins.y, min_range.y, max_range.y);
	}
	psi = new TH2F("harr1", "test", psi_bins.x, min_range.x, max_range.x, psi_bins.y, min_range.y, max_range.y);
	phi = new TH2F("harr2", "test", phi_bins.x, min_range.x, max_range.x, phi_bins.y, min_range.y, max_range.y);
	std::vector<wif_core::vector_2d_c> flows(3);
	flows[0] = velocity_bins;
	flows[1] = psi_bins;
	flows[2] = phi_bins;
	wif_core::vector_2d_c pos;


	for(int k = 0; k <= 2; k++)
	{

		double stepsx = (max_range.x - min_range.x) / flows[k].x;
		double stepsy = (max_range.y - min_range.y) / flows[k].y;
		//std::cout<<max_range.x<<"  "<<min_range.x<<std::endl;
		for(int i = 1; i <= flows[k].x; i++)
		{
			for(int j = 1; j <= flows[k].y; j++)
			{
				double evaluateX = min_range.x + i * stepsx - stepsx / 2;
				double evaluateY = min_range.y + j * stepsy - stepsy / 2;
				pos.x = evaluateX;
				pos.y = evaluateY;

				/*if(k == 0)
				{
					wif_core::vector_2d_c vel = flow->get_velocity(pos);
					velocity->SetBinContent(i, j, sqrt(pow(vel.x, 2) + pow(vel.y, 2)));
				}
				else*/ if(k == 1)
				{

					psi->SetBinContent(i, j, Flow->get_psi(pos));

				}
				else if(k == 2)
				{


					phi->SetBinContent(i, j, Flow->get_phi(pos));

				}

			}
		}



	}

}

void visualization_root_c::addArrows()
{
	double vwdex=(max_range.x-min_range.x)/6;
    double vwdey=(max_range.y-min_range.y)/6;
	double stepsx = (max_range.x - min_range.x) / velocity_bins.x;
	double stepsy = (max_range.y - min_range.y) / velocity_bins.y;
	wif_core::vector_2d_c pos;
	wif_core::vector_2d_c vel;
	TArrow ARR(0,0,0,0,1,">");
    for (int i=1;i<velocity_bins.x+1;i++) {
        for (int j=1;j<velocity_bins.y+1;j++) {
            double evaluateX = min_range.x + i * stepsx - stepsx / 2;
			double evaluateY = min_range.y + j * stepsy - stepsy / 2;
			pos.x = evaluateX;
			pos.y = evaluateY;
			vel=flow->get_velocity(pos);
            double Vx=evaluateX+0.2*(vel.x);
            double Vy=evaluateY+0.2*(vel.y);
            if (Vx>max_range.x || Vy>max_range.y || Vx<min_range.x || Vy<min_range.y|| abs(Vx-evaluateX)>abs(vwdex) || abs(Vy-evaluateY)>abs(vwdey)){
            }
            else {
                ARR.DrawArrow(evaluateX,evaluateY,Vx,Vy,0.01,">");
            }
        }
    }
}

void visualization_root_c::fillbinStagnatie()
{
	//double stepsx = (max_range.x - min_range.x) / phi_bins.x;
	//double stepsy = (max_range.y - min_range.y) / phi_bins.y;
	if(velocity_bins.x!=0 && velocity_bins.y!=0)
	{
		stag = new TH2F("harr4", "test", velocity_bins.x, min_range.x, max_range.x, velocity_bins.y, min_range.y, max_range.y);
		for (int i=1;i<velocity_bins.x+1;i++) {
			for (int j=1;j<velocity_bins.y+1;j++) {
				//double evaluateX = min_range.x + i * stepsx - stepsx / 2;
				//double evaluateY = min_range.y + j * stepsy - stepsy / 2;
				double velstag=velocity->GetBinContent(i,j);
				if(velstag==0)
				{
					std::cout<<"0 found"<<std::endl;
					stag->SetBinContent(i, j, 10);
				}
			}
		}
	}
}

}// namespace wif_viz
