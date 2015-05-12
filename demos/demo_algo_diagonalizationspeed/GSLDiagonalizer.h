#ifndef GSLDIAGONALIZER_H
#define GSLDIAGONALIZER_H

#include <vector>

/*

• LU Decomposition:	  					works, (square)
• QR Decomposition:	  					works, (rectangular)
• QRPT Decomposition with Column Pivoting:	  		works, (rectangular)
• SV Singular Value Decomposition:				works, (rectangular)
• SVM Singular Value Decomposition Modified:			works, (rectangular)
• SVJ Singular Value Decomposition Jacobi:			works, (rectangular)
• Cholesky Decomposition:	  				works, (symmetric, square, positive definite)

*/

class GSLDiagonalizer{
public:
	GSLDiagonalizer(std::vector<double>, std::vector<double>, int, int);
	std::vector<double> diagonalize(std::string);

private:
	int rows;
	int columns;
	std::vector<double> matrixA;
	std::vector<double> vecB;
};

#endif
