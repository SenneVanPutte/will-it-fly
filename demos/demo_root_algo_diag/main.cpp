//Amy
//Solving A*sigma=b in ROOT

#include <TMath.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <iostream>
#include <TDecompLU.h>
#include <TDecompQRH.h>
#include <TF1.h>
#include <Math/WrappedTF1.h>
#include <Math/GaussIntegrator.h>

using namespace std;


Double_t func_source_sheet(Double_t * coord, Double_t * par)
{
	Double_t s = coord[0];
	
	//par[0]=r inradius
	//par[1]=R outer radius
	//par[2]=beta_j
	//par[3]=beta_i
	
	Double_t x_c=par[1]*cos(par[3]);
	Double_t y_c=par[1]*sin(par[3]);
	
	Double_t x_a=par[0]*cos(par[2]-TMath::Pi()/8);
	Double_t y_a=par[0]*sin(par[2]-TMath::Pi()/8);
	
	Double_t a=(x_c-(x_a-s*sin(par[2])))*cos(par[3])+(y_c-(y_a+s*cos(par[2])))*sin(par[3]);
	Double_t b=pow(x_c-(x_a-s*sin(par[2])),2)+pow(y_c-(y_a+s*cos(par[2])),2);
		
	return a/b;
}

Double_t func_vortex_sheet(Double_t * coord, Double_t * par)
{
	Double_t s = coord[0];
	
	Double_t x_c=par[1]*cos(par[3]);
	Double_t y_c=par[1]*sin(par[3]);
	
	Double_t x_a=par[0]*cos(par[2]-TMath::Pi()/8);
	Double_t y_a=par[0]*sin(par[2]-TMath::Pi()/8);
	
	//par[0]=r inradius
	//par[1]=R outer radius
	//par[2]=beta_j
	//par[3]=beta_i
	
	Double_t a=sin(par[3])*(x_c-(x_a-s*sin(par[2])))-cos(par[3])*(y_c-(y_a+s*cos(par[2])));
	Double_t b=pow(x_c-(x_a-s*sin(par[2])),2)+pow(y_c-(y_a+s*cos(par[2])),2);
	
	return a/b;
}

Double_t func_vortex_sheet_2(Double_t * coord, Double_t * par)
{
	Double_t s = coord[0];
	
	Double_t x_c=par[1]*cos(par[3]);
	Double_t y_c=par[1]*sin(par[3]);
	
	Double_t x_a=par[0]*cos(par[2]-TMath::Pi()/8);
	Double_t y_a=par[0]*sin(par[2]-TMath::Pi()/8);
	
	//par[0]=r inradius
	//par[1]=R outer radius
	//par[2]=beta_j
	//par[3]=beta_i
	
	Double_t a=cos(par[3])*(x_c-(x_a-s*sin(par[2])))-sin(par[3])*(y_c-(y_a+s*cos(par[2])));
	Double_t b=pow(x_c-(x_a-s*sin(par[2])),2)+pow(y_c-(y_a+s*cos(par[2])),2);
	
	return a/b;
}

int main(){
	/*
	//Simple example:
	Double_t n=2;
	Double_t m=2;

	TVectorD b(n);
	TMatrixD A(n,m);

	//y=x
	//y=-2x+6
	//intersection: (y,x)=(2,2)
	A(0,0)=1;
	A(0,1)=-1;
	A(1,0)=1;
	A(1,1)=2;
	b(0)=0;
	b(1)=6;
	*/
	
	/////////////////////////////////////////////////
	//Octagon:

	Double_t n=8; //octagon

	TVectorD b(n+1);
	TMatrixD A(n+1,n+1);

	Double_t gamma=1; //vortex strength
	Double_t U_inf=1;
	Double_t alpha=0; //Angle of attack
	Double_t R=1; //outer radius 
	Double_t r=R*(1+sqrt(2))/sqrt(4+2*sqrt(2)); //inradius (octagon)
	
	Double_t s_0=0;
	Double_t s_1=R*2/sqrt(4+2*sqrt(2));
	
	TF1 Z("Z",func_source_sheet,s_0,s_1,4);
	Z.SetParameter(0,R);
	Z.SetParameter(1,r);

	ROOT::Math::GaussIntegrator GI_Z;
	GI_Z.SetRelTolerance(0.001);
	
		
	for (int i= 0; i < n; i++) {
		b(i)= -U_inf*cos(TMath::Pi()/4*i)*cos(alpha);
		ROOT::Math::WrappedTF1 wrap_Z(Z);
		GI_Z.SetFunction(wrap_Z);
		
		for (int j= 0; j < n; j++) {
			if (i==j) 
			{A(i,j)=0.5;}
			else {
				Z.SetParameter(2, TMath::Pi()/4*j);
				Z.SetParameter(3, TMath::Pi()/4*i);
				
				A(i,j)=0.5/TMath::Pi()*GI_Z.Integral(s_0,s_1);
				}
		}
	}
	
	//VORTEX:
	
	Double_t beta_l=TMath::Pi();
	Double_t beta_k=0;
	
	TF1 ZZ("ZZ",func_vortex_sheet,s_0,s_1,4);
	ZZ.SetParameter(0,R);
	ZZ.SetParameter(1,r);
	
	ROOT::Math::GaussIntegrator GI_ZZ;
	GI_ZZ.SetRelTolerance(0.001);
	
	for (int i= 0; i < n; i++) {
		
		int j=n;
				
		ROOT::Math::WrappedTF1 wrap_ZZ(ZZ);
		GI_ZZ.SetFunction(wrap_ZZ);
		
		ZZ.SetParameter(2, TMath::Pi()/4*j);
		ZZ.SetParameter(3, TMath::Pi()/4*i);
		
		A(i,j)= -0.5*gamma/TMath::Pi()*GI_ZZ.Integral(s_0,s_1);
	}
		
	for (int j= 0; j < n; j++) {
		
		int i=n;
		
		b(i)= -U_inf*cos(alpha-beta_k)-U_inf*cos(alpha-beta_l);
		
		ROOT::Math::WrappedTF1 wrap_ZZ(ZZ);
		GI_ZZ.SetFunction(wrap_ZZ);
		
		ZZ.SetParameter(3, TMath::Pi()/4*i);
		
		
		ZZ.SetParameter(2, beta_l);
		A(i,j)= -0.5*gamma/TMath::Pi()*GI_ZZ.Integral(s_0,s_1);
		
		ZZ.SetParameter(2, beta_k);
		A(i,j)= A(i,j)-0.5*gamma/TMath::Pi()*GI_ZZ.Integral(s_0,s_1);
		
	}
	
	
	TF1 ZZZ("ZZZ",func_vortex_sheet_2,s_0,s_1,4);
	ZZZ.SetParameter(0,R);
	ZZZ.SetParameter(1,r);
	
	int i=n;
	int j=n;
	
	ROOT::Math::GaussIntegrator GI_ZZZ;
	GI_ZZZ.SetRelTolerance(0.001);
	
	ROOT::Math::WrappedTF1 wrap_ZZZ(ZZ);
	GI_ZZZ.SetFunction(wrap_ZZZ);
	
	ZZZ.SetParameter(2, TMath::Pi()/4*j);
	ZZZ.SetParameter(3, TMath::Pi()/4*i);
	
	ZZZ.SetParameter(2, beta_l);
	A(i,j)= -0.5*gamma/TMath::Pi()*GI_ZZZ.Integral(s_0,s_1);
	
	ZZZ.SetParameter(2, beta_k);
	A(i,j)= A(i,j)-0.5*gamma/TMath::Pi()*GI_ZZZ.Integral(s_0,s_1);
		

	///////////////////////////////////////////////////

	TDecompLU lu(A);
	Bool_t ok;
	TVectorD x=lu.Solve(b,ok);
	TVectorD ans=A*x;
	ans=b-ans;
	
	if (x.IsValid()){
		//A.Print();
		//b.Print();
		//lu.Print();
		x.Print();
		
		cout << "solved with tol = " << lu.GetTol() << endl;
		TVectorD r=b-A*x;
		cout << "residue = " << lu.Condition()*r.NormInf()/A.NormInf()/x.NormInf() << endl; //?cond(A)=cond(lu)
		cout << "cond = " << lu.Condition() << endl;
		cout << "b-A*x = "  << endl; ans.Print() ;
		
		}
	else
		{cout << "solving failed " << endl;}

	return 0;
}
