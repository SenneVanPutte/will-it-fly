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

	Double_t n=8;
	Double_t m=8;

	TVectorD b(n);
	TMatrixD A(n,m);

	Double_t U_inf=1;
	Double_t R=1; //radius
	Double_t r=R*(1+sqrt(2))/sqrt(4+2*sqrt(2)); //inradius
	
	Double_t s_0=0;
	Double_t s_1=R*2/sqrt(4+2*sqrt(2));
	
	TF1 Z("Z",func_A,s_0,s_1,3);
	Z.SetParameter(0,R);
	Z.SetParameter(1,r);

	ROOT::Math::GaussIntegrator GI;
	GI.SetRelTolerance(0.001);
		
	for (int i= 0; i < n; i++) {
		b(i)= -U_inf*cos(TMath::Pi()/4*i);
		Z.SetParameter(2, TMath::Pi()/4*i);
		ROOT::Math::WrappedTF1 wrap_Z(Z);
		GI.SetFunction(wrap_Z);
		
		for (int j= 0; j < m; j++) {
			if (i==j) {A(i,j)=0.5;}
			else {A(i,j)=0.5/TMath::Pi()*GI.Integral(s_0,s_1);}
		}
	}
	
	///////////////////////////////////////////////////

	TDecompLU lu(A);
	Bool_t ok;
	TVectorD x=lu.Solve(b,ok);

	if (x.IsValid()){
		//A.Print();
		//b.Print();
		x.Print();
		cout << "solved with tol = " << lu.GetTol() << endl;
		TVectorD r=b-A*x;
		cout << "residue = " << lu.Condition()*r.NormInf()/A.NormInf()/x.NormInf() << endl; //?cond(A)=cond(lu)
		cout << "cond = " << lu.Condition() << endl;
		//lu.Print();
		}
	else
		{cout << "solving failed " << endl;}

	return 0;
}
