
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

	//par[0]=x_c
	//par[1]y_c
	//par[2]=beta_j
	//par[3]=beta_i
	//par[4]=x_a
	//par[5]=y_a

	Double_t x_c = par[0];
	Double_t y_c = par[1];

	Double_t x_a = par[4];
	Double_t y_a = par[5];

	Double_t a = (x_c - (x_a - s * sin(par[2]))) * cos(par[3]) + (y_c - (y_a + s * cos(par[2]))) * sin(par[3]);
	Double_t b = pow(x_c - (x_a - s * sin(par[2])), 2) + pow(y_c - (y_a + s * cos(par[2])), 2);

	return a / b;
}


Double_t func_vortex_sheet(Double_t * coord, Double_t * par)
{
	Double_t s = coord[0];

	//par[0]=x_c
	//par[1]y_c
	//par[2]=beta_j
	//par[3]=beta_i
	//par[4]=x_a
	//par[5]=y_a

	Double_t x_c = par[0];
	Double_t y_c = par[1];
	Double_t x_a = par[4];
	Double_t y_a = par[5];

	Double_t a = sin(par[3]) * (x_c - (x_a - s * sin(par[2]))) - cos(par[3]) * (y_c - (y_a + s * cos(par[2])));
	Double_t b = pow(x_c - (x_a - s * sin(par[2])), 2) + pow(y_c - (y_a + s * cos(par[2])), 2);

	return a / b;
}

Double_t func_vortex_sheet_2(Double_t * coord, Double_t * par)
{
	Double_t s = coord[0];

	//par[0]=x_c
	//par[1]y_c
	//par[2]=beta_j
	//par[3]=beta_i
	//par[4]=x_a
	//par[5]=y_a

	Double_t x_c = par[0];
	Double_t y_c = par[1];
	Double_t x_a = par[4];
	Double_t y_a = par[5];

	Double_t a = cos(par[3]) * (x_c - (x_a - s * sin(par[2]))) - sin(par[3]) * (y_c - (y_a + s * cos(par[2])));
	Double_t b = pow(x_c - (x_a - s * sin(par[2])), 2) + pow(y_c - (y_a + s * cos(par[2])), 2);

	return a / b;
}

int main()
{
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

	Double_t n = 8; //octagon

	//TVectorD b(n);
	//TMatrixD A(n,n);

	TVectorD b(n + 1);
	TMatrixD A(n + 1, n + 1);


	Double_t U_inf = 1;
	Double_t alpha = 0; //Angle of attack

	///////////////////////////////

	TVectorD x_c(n);
	TVectorD y_c(n);
	TVectorD x_a(n);
	TVectorD y_a(n);

	x_c(0) = 4;
	x_c(1) = 3;
	x_c(2) = 0;
	x_c(3) = -3;
	x_c(4) = -4;
	x_c(5) = -3;
	x_c(6) = 0;
	x_c(7) = 3;

	y_c(0) = 0;
	y_c(1) = 3;
	y_c(2) = 4;
	y_c(3) = 3;
	y_c(4) = 0;
	y_c(5) = -3;
	y_c(6) = -4;
	y_c(7) = -3;

	x_a(0) = 4;
	x_a(1) = 4;
	x_a(2) = 2;
	x_a(3) = -2;
	x_a(4) = -4;
	x_a(5) = -4;
	x_a(6) = -2;
	x_a(7) = 2;

	y_a(0) = -2;
	y_a(1) = 2;
	y_a(2) = 4;
	y_a(3) = 4;
	y_a(4) = 2;
	y_a(5) = -2;
	y_a(6) = -4;
	y_a(7) = -4;

	Double_t s_0 = 0;
	TVectorD s_1(n);

	s_1(0) = 4;
	s_1(1) = 2 * sqrt(2);
	s_1(2) = 4;
	s_1(3) = 2 * sqrt(2);
	s_1(4) = 4;
	s_1(5) = 2 * sqrt(2);
	s_1(6) = 4;
	s_1(7) = 2 * sqrt(2);

	////////////////////////////////



	ROOT::Math::GaussIntegrator GI_Z;
	GI_Z.SetRelTolerance(0.001);


	for(int i = 0; i < n; i++)
	{
		b(i) = -U_inf * cos(TMath::Pi() / 4 * i) * cos(alpha);

		for(int j = 0; j < n; j++)
		{
			if(i == j)
			{
				A(i, j) = 0.5;
			}
			else
			{

				//par[0]=x_c
				//par[1]y_c
				//par[2]=beta_j
				//par[3]=beta_i
				//par[4]=x_a
				//par[5]=y_a
				TF1 Z("Z", func_source_sheet, s_0, s_1(j), 6);
				Z.SetParameter(0, x_c(i));
				Z.SetParameter(1, y_c(i));
				Z.SetParameter(2, TMath::Pi() / 4 * j);
				Z.SetParameter(3, TMath::Pi() / 4 * i);
				Z.SetParameter(4, x_a(j));
				Z.SetParameter(5, y_a(j));

				ROOT::Math::WrappedTF1 wrap_Z(Z);
				GI_Z.SetFunction(wrap_Z);

				A(i, j) = 1. / 2. / TMath::Pi() * GI_Z.Integral(s_0, s_1(j));
			}
		}
	}


	//VORTEX: %%%FIX!!%%%

	Double_t gamma = 1; //vortex strength
	Double_t beta_l = TMath::Pi();
	Double_t beta_k = 0;



	ROOT::Math::GaussIntegrator GI_ZZ;
	GI_ZZ.SetRelTolerance(0.001);

	for(int i = 0; i < n; i++)
	{

		int j = n - 1;
		TF1 ZZ("ZZ", func_vortex_sheet, s_0, s_1(j), 6);

		ZZ.SetParameter(0, x_c(i));
		ZZ.SetParameter(1, y_c(i));
		ZZ.SetParameter(2, TMath::Pi() / 4 * j);
		ZZ.SetParameter(3, TMath::Pi() / 4 * i);
		ZZ.SetParameter(4, x_a(j));
		ZZ.SetParameter(5, y_a(j));

		ROOT::Math::WrappedTF1 wrap_ZZ(ZZ);
		GI_ZZ.SetFunction(wrap_ZZ);
		A(i, j + 1) = -0.5 * gamma / TMath::Pi() * GI_ZZ.Integral(s_0, s_1(j));
	}

	for(int j = 0; j < n; j++)
	{

		int i = n - 1;

		b(i) = -U_inf * cos(alpha - beta_k) - U_inf * cos(alpha - beta_l);

		TF1 ZZ("ZZ", func_vortex_sheet, s_0, s_1(j), 6);

		ZZ.SetParameter(0, x_c(i));
		ZZ.SetParameter(1, y_c(i));
		ZZ.SetParameter(3, TMath::Pi() / 4 * i);
		ZZ.SetParameter(4, x_a(j));
		ZZ.SetParameter(5, y_a(j));

		ZZ.SetParameter(2, beta_l);
		ROOT::Math::WrappedTF1 wrap_ZZ(ZZ);
		GI_ZZ.SetFunction(wrap_ZZ);
		A(i, j) = -0.5 * gamma / TMath::Pi() * GI_ZZ.Integral(s_0, s_1(j));

		ZZ.SetParameter(2, beta_k);
		ROOT::Math::WrappedTF1 wrap_ZZ_2(ZZ);
		GI_ZZ.SetFunction(wrap_ZZ_2);
		A(i, j + 1) = A(i, j + 1) - 0.5 * gamma / TMath::Pi() * GI_ZZ.Integral(s_0, s_1(j));

	}




	int i = n - 1;
	int j = n - 1;

	ROOT::Math::GaussIntegrator GI_ZZZ;
	GI_ZZZ.SetRelTolerance(0.001);


	TF1 ZZZ("ZZZ", func_vortex_sheet_2, s_0, s_1(j), 6);
	ZZZ.SetParameter(0, x_c(i));
	ZZZ.SetParameter(1, y_c(i));
	ZZZ.SetParameter(3, TMath::Pi() / 4 * i);
	ZZZ.SetParameter(4, x_a(j));
	ZZZ.SetParameter(5, y_a(j));

	ZZZ.SetParameter(2, beta_l);
	ROOT::Math::WrappedTF1 wrap_ZZZ(ZZZ);
	GI_ZZZ.SetFunction(wrap_ZZZ);
	A(i, j + 1) = -0.5 * gamma / TMath::Pi() * GI_ZZZ.Integral(s_0, s_1(j));

	ZZZ.SetParameter(2, beta_k);
	ROOT::Math::WrappedTF1 wrap_ZZZ_2(ZZZ);
	GI_ZZZ.SetFunction(wrap_ZZZ_2);
	A(i, j + 1) = A(i, j + 1) - 0.5 * gamma / TMath::Pi() * GI_ZZZ.Integral(s_0, s_1(j));


	///////////////////////////////////////////////////

	TDecompLU lu(A);
	Bool_t ok;
	TVectorD x = lu.Solve(b, ok);
	TVectorD ans = A * x;
	ans = b - ans;

	if(x.IsValid())
	{
		A.Print();
		b.Print();
		//lu.Print();
		x.Print();

		cout << "solved with tol = " << lu.GetTol() << endl;
		TVectorD r = b - A * x;
		cout << "residue = " << lu.Condition()*r.NormInf() / A.NormInf() / x.NormInf() << endl; //?cond(A)=cond(lu)
		cout << "cond = " << lu.Condition() << endl;
		cout << "b-A*x = "  << endl;
		ans.Print() ;

	}
	else
	{
		cout << "solving failed " << endl;
	}

	return 0;
}



