#include <iostream>
#include <cstdio>
#include <ctime>
#include <TF1.h>
#include <TMath.h>
#include <Math/WrappedTF1.h>
#include <Math/GaussIntegrator.h>
#include <Math/GaussLegendreIntegrator.h>

using namespace std;

Double_t x = 1;
Double_t y = 1;
Double_t sigma = 1;
Double_t a = -1;
Double_t b = 1;


Double_t func_vx(Double_t * coord, Double_t * par)
{
	Double_t ksi = coord[0];
	return par[2] / 2 / TMath::Pi() * par[0] / (par[0] * par[0] + (par[1] - ksi) * (par[1] - ksi));
}


Double_t func_I_vx(Double_t ksi_min, Double_t ksi_max)
{
	return sigma * x / 2 / TMath::Pi() * TMath::Log((x * x + (y - ksi_min)) / (x * x + (y - ksi_max)));
}


int main()
{

	clock_t start;
	Double_t duration;

	TF1 f("f", func_vx, a, b, 3);
	f.SetParameter(0, x);
	f.SetParameter(1, y);
	f.SetParameter(2, sigma);

	ROOT::Math::WrappedTF1 wf1(f);

	//Methode: GaussIntegrator
	ROOT::Math::GaussIntegrator ig;
	ig.SetFunction(wf1);
	ig.SetRelTolerance(0.001);

	start = clock();
	Double_t I_vx_1;

	for(int i = 0; i < 1000; i++)
	{
		I_vx_1 = ig.Integral(a, b);
	}

	duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	printf("Methode:GaussIntegrator\n");
	printf("result \t\t= % .7f\n", I_vx_1);
	printf("exact result \t= % .7f\n", func_I_vx(a, b));
	printf("error \t\t= % .7f\n", I_vx_1 - func_I_vx(a, b));
	printf("duration \t= % .7f\n", duration);


	//Methode: GaussLegendreIntegrator
	ROOT::Math::GaussLegendreIntegrator ig_2;
	ig_2.SetFunction(wf1);
	ig_2.SetRelTolerance(0.001);
	ig_2.SetNumberPoints(40);

	start = std::clock();
	Double_t I_vx_2;

	for(int i = 0; i < 1000; i++)
	{
		I_vx_2 = ig_2.Integral(a, b);
	}

	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	printf("Methode:GaussLegendreIntegrator\n");
	printf("result \t\t= % .7f\n", I_vx_2);
	printf("exact result \t= % .7f\n", func_I_vx(a, b));
	printf("error \t\t= % .7f\n", I_vx_2 - func_I_vx(a, b));
	printf("duration \t= % .7f\n", duration);


	//Methode: GSL
	start = std::clock();
	Double_t I_vx;

	for(int i = 0; i < 1000; i++)
	{
		I_vx = f.Integral(a, b);
	}

	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	printf("Methode:GSL\n");
	printf("result \t\t= % .7f\n", I_vx);
	printf("exact result \t= % .7f\n", func_I_vx(a, b));
	printf("error \t\t= % .7f\n", I_vx - func_I_vx(a, b));
	printf("duration \t= % .7f\n", duration);

	return 0;
}
