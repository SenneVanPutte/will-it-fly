#include <algorithm>
#include <iostream>

#include "ROOTDiagonalizer.h"
#include <TMatrix.h>
#include <TDecompLU.h>
#include <TDecompQRH.h>
#include <TDecompSVD.h>
#include <TVector.h>


ROOTDiagonalizer::ROOTDiagonalizer(std::vector<double> matrixA, std::vector<double> vecB, int rows, int columns): rows(rows), columns(columns), matrixA(matrixA), vecB(vecB)
{
}


std::vector<double> ROOTDiagonalizer::diagonalize(std::string method)
{
	std::string lowerMethod = method;
	std::transform(lowerMethod.begin(), lowerMethod.end(), lowerMethod.begin(), ::tolower);
	std::vector<double> solutions;


	double arrayA[rows * columns];
	double arrayB[rows];
	std::copy(matrixA.begin(), matrixA.end(), arrayA);
	std::copy(vecB.begin(), vecB.end(), arrayB);

	TMatrixT<double> AMatrix(rows, columns, arrayA);
	TVectorT<double> bVec(columns, arrayB);
	Bool_t ok;
	TVectorD solutionsROOT(columns);

	if(lowerMethod == "lu")
	{
		TDecompLU decompLU(AMatrix);
		solutionsROOT = decompLU.Solve(bVec, ok);
	}
	else if(lowerMethod == "qr" || lowerMethod == "qrh")
	{
		TDecompQRH decompQRH(AMatrix);
		solutionsROOT = decompQRH.Solve(bVec, ok);
	}
	else if(lowerMethod == "svd")
	{
		TDecompSVD decompSVD(AMatrix);
		solutionsROOT = decompSVD.Solve(bVec, ok);
	}
	else
	{
		std::cerr << "Method not recognized." << std::endl;
	}

	for(int i = 0; i < columns; i++)
	{
		solutions.push_back(solutionsROOT[i]);
	}

	return solutions;
}
