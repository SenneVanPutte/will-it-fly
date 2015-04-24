//Amy
//Integration in ROOT

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

//Velocity dv_x
Double_t func_dvx(Double_t * coord, Double_t * par)
{
	Double_t ksi = coord[0];
	return par[2] / 2 / TMath::Pi() * par[0] / (par[0] * par[0] + (par[1] - ksi) * (par[1] - ksi));
}

//Velocity v_x analytical solution
Double_t func_vx(Double_t ksi_min, Double_t ksi_max)
{
	//return sigma * x / 2 / TMath::Pi() * TMath::Log((x * x + (y - ksi_min)) / (x * x + (y - ksi_max)));
	return -sigma/2/ TMath::Pi()*(atan2(y-ksi_max,x)-atan2(y-ksi_min,x));
}

//Velocity dv_y
Double_t func_dvy(Double_t * coord, Double_t * par)
{
	Double_t ksi = coord[0];
	return par[2] / 2 / TMath::Pi() * (par[1] - ksi) / (par[0] * par[0] + (par[1] - ksi) * (par[1] - ksi));
}

//Velocity v_y analytical solution
Double_t func_vy(Double_t ksi_min, Double_t ksi_max)
{
	//return sigma / TMath::Pi() * TMath::Log((x * x + (y - ksi_min)*(y - ksi_min)) / (x * x + (y - ksi_max)*(y - ksi_max)));
	return sigma /4/TMath::Pi() * TMath::Log((x * x + (y - ksi_min)*(y - ksi_min)) / (x * x + (y - ksi_max)*(y - ksi_max)));
}


//A_i_j
Double_t func_A(Double_t * coord, Double_t * par)
{
	Double_t s = coord[0];
	Double_t x_c=par[1]*cos(par[2]);
	Double_t y_c=par[1]*sin(par[2]);
	Double_t x_a=par[0]*cos(par[2]-TMath::Pi()/8);
	Double_t y_a=par[0]*sin(par[2]-TMath::Pi()/8);
	
	Double_t a=(x_c-(x_a-s*sin(par[2])))*cos(par[2])+(y_c-(y_a-s*cos(par[2])))*sin(par[2]);
	Double_t b=pow(x_c-(x_a-s*sin(par[2])),2)+pow(y_c-(y_a-s*cos(par[2])),2);
	return a/b;
}

int main()
{
	clock_t start;
	Double_t duration;

	TF1 vx("vx", func_dvx, a, b, 3);
	vx.SetParameter(0, x);
	vx.SetParameter(1, y);
	vx.SetParameter(2, sigma);
	Double_t I_vx;
	
	TF1 vy("vy", func_dvy, a, b, 3);
	vy.SetParameter(0, x);
	vy.SetParameter(1, y);
	vy.SetParameter(2, sigma);
	Double_t I_vy;
	
	ROOT::Math::WrappedTF1 wrap_vx(vx);
	ROOT::Math::WrappedTF1 wrap_vy(vy);

	//printf("exact result vx\t= % .7f\n", func_vx(a, b));
	//printf("exact result vy\t= % .7f\n", func_vy(a, b));
	
	//Methode: GaussIntegrator
	ROOT::Math::GaussIntegrator GI;
	GI.SetRelTolerance(0.001);
	
	GI.SetFunction(wrap_vx);
	start = clock();
	for(int i = 0; i < 1000; i++) I_vx= GI.Integral(a,b);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	printf("Methode:GaussIntegrator, ");
	printf("vx:\n");
	printf("result \t\t= % .10f\n", I_vx);
	printf("error \t\t= % .10f\n", I_vx - func_vx(a, b));
	printf("duration \t= % .10f\n", duration);

	GI.SetFunction(wrap_vy);
	start = clock();
	for(int i = 0; i < 1000; i++) I_vy= GI.Integral(a,b);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	printf("Methode:GaussIntegrator, ");
	printf("vy:\n");
	printf("result \t\t= % .10f\n", I_vy);
	printf("error \t\t= % .10f\n", I_vy - func_vy(a, b));
	printf("duration \t= % .10f\n", duration);
	
	//Methode: GaussLegendreIntegrator
	ROOT::Math::GaussLegendreIntegrator GLI;
	GLI.SetRelTolerance(0.001);
	GLI.SetNumberPoints(1000);
	
	GLI.SetFunction(wrap_vx);
	start = clock();
	for(int i = 0; i < 1000; i++) I_vx = GLI.Integral(a, b);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	printf("Methode:GaussLegendreIntegrator, ");
	printf("vx:\n");
	printf("result \t\t= % .10f\n", I_vx);
	printf("error \t\t= % .10f\n", I_vx - func_vx(a, b));
	printf("duration \t= % .10f\n", duration);

	GLI.SetFunction(wrap_vy);
	start = clock();
	for(int i = 0; i < 1000; i++) I_vy = GLI.Integral(a, b);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	printf("Methode:GaussLegendreIntegrator, ");
	printf("vy:\n");
	printf("result \t\t= % .10f\n", I_vy);
	printf("error \t\t= % .10f\n", I_vy - func_vy(a, b));
	printf("duration \t= % .10f\n", duration);

	//Methode: GSL
	start = clock();
	for(int i = 0; i < 1000; i++) I_vx = vx.Integral(a, b);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	printf("Methode:GSL, ");
	printf("vx:\n");
	printf("result \t\t= % .10f\n", I_vx);
	printf("error \t\t= % .10f\n", I_vx - func_vx(a, b));
	printf("duration \t= % .10f\n", duration);

	start = clock();
	for(int i = 0; i < 1000; i++) I_vy = vy.Integral(a, b);
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	printf("Methode:GSL, ");
	printf("vy:\n");
	printf("result \t\t= % .10f\n", I_vy);
	printf("error \t\t= % .10f\n", I_vy - func_vy(a, b));
	printf("duration \t= % .10f\n", duration);
	
	
	/////////////////////////////////////////////////////
	Double_t i=1;
	Double_t R=1; //radius
	Double_t r=R*(1+sqrt(2))/sqrt(4+2*sqrt(2)); //inradius
	Double_t s_0=0;
	Double_t s_1=R*2/sqrt(4+2*sqrt(2));
	
	TF1 Z("Z", func_A, s_0,s_1, 3);
	Z.SetParameter(0, R);
	Z.SetParameter(1, r);
	Z.SetParameter(2, TMath::Pi()/4*i);
	
	ROOT::Math::WrappedTF1 wrap_Z(Z);
	
	//Methode: GaussIntegrator
	GI.SetFunction(wrap_Z);
	printf("Methode:GaussIntegrator\n");
	printf("result \t\t= % .10f\n", GI.Integral(s_0,s_1));
	//printf("error \t\t= % .10f\n", 0);

	
	//Methode: GaussLegendreIntegrator
	GLI.SetFunction(wrap_Z);
	printf("Methode:GaussLegendreIntegrator\n");
	printf("result \t\t= % .10f\n", GLI.Integral(s_0,s_1));
	//printf("error \t\t= % .10f\n", 0);


	//Methode: GSL
	printf("Methode:GSL\n");
	printf("result \t\t= % .10f\n", Z.Integral(s_0,s_1));
	//printf("error \t\t= % .10f\n", 0);

	
	
	return 0;
}
