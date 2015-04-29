#include <algorithm>
#include <gsl/gsl_linalg.h>
#include <iostream>

#include "GSLDiagonalizer.h"



GSLDiagonalizer::GSLDiagonalizer(std::vector<double> matrixA, std::vector<double> vecB, int Rows, int Columns):rows(Rows), columns(Columns),matrixA(matrixA), vecB(vecB){

}

std::vector<double> GSLDiagonalizer::diagonalize(std::string method){
	std::string lowerMethod = method;
	std::transform(lowerMethod.begin(), lowerMethod.end(), lowerMethod.begin(), ::tolower);
	std::vector<double> solutions;


	double arrayA[rows*columns];
	double arrayB[rows];
	std::copy(matrixA.begin(), matrixA.end(), arrayA);
	std::copy(vecB.begin(), vecB.end(), arrayB);


	gsl_matrix_view mA = gsl_matrix_view_array(arrayA, rows, columns);
	gsl_vector_view vB = gsl_vector_view_array(arrayB, rows);
	gsl_vector *x = gsl_vector_alloc(columns);


	if (lowerMethod == "lu"){
		int s;
		gsl_permutation *p = gsl_permutation_alloc(rows);

		gsl_linalg_LU_decomp(&mA.matrix, p, &s);
		gsl_linalg_LU_solve(&mA.matrix, p, &vB.vector, x);

		gsl_permutation_free(p);
	}
	else if (lowerMethod == "qr"){
		gsl_vector *tau = gsl_vector_alloc(rows);

		gsl_linalg_QR_decomp(&mA.matrix, tau);
		gsl_linalg_QR_solve(&mA.matrix, tau, &vB.vector, x);

		gsl_vector_free(tau);
	}
	else if (lowerMethod == "qrpt"){
		int s;
		gsl_permutation *p = gsl_permutation_alloc(rows);
		gsl_vector *tau = gsl_vector_alloc(rows);
		gsl_vector *norm = gsl_vector_alloc(columns);

		gsl_linalg_QRPT_decomp(&mA.matrix, tau, p, &s, norm);
		gsl_linalg_QRPT_solve(&mA.matrix, tau, p, &vB.vector, x);

		gsl_permutation_free(p);
		gsl_vector_free(tau);
		gsl_vector_free(norm);
	}
	else if (lowerMethod == "sv"){
		gsl_matrix *V = gsl_matrix_alloc(rows, columns);
		gsl_vector *S = gsl_vector_alloc(columns);
		gsl_vector *work = gsl_vector_alloc(columns);

		gsl_linalg_SV_decomp(&mA.matrix, V, S, work);
		gsl_linalg_SV_solve(&mA.matrix, V, S, &vB.vector, x);

		gsl_matrix_free(V);
		gsl_vector_free(S);
		gsl_vector_free(work);
	}
	else if (lowerMethod == "svm"){
		gsl_matrix *X = gsl_matrix_alloc(columns, columns);
		gsl_matrix *V = gsl_matrix_alloc(rows, columns);
		gsl_vector *S = gsl_vector_alloc(columns);
		gsl_vector *work = gsl_vector_alloc(columns);

		gsl_linalg_SV_decomp_mod(&mA.matrix, X, V, S, work);
		gsl_linalg_SV_solve(&mA.matrix, V, S, &vB.vector, x);

		gsl_matrix_free(X);
		gsl_matrix_free(V);
		gsl_vector_free(S);
		gsl_vector_free(work);
	}
	else if (lowerMethod == "svj"){
		gsl_matrix *V = gsl_matrix_alloc(rows, columns);
		gsl_vector *S = gsl_vector_alloc(columns);

		gsl_linalg_SV_decomp_jacobi(&mA.matrix, V, S);
		gsl_linalg_SV_solve(&mA.matrix, V, S, &vB.vector, x);

		gsl_matrix_free(V);
		gsl_vector_free(S);
	}
	else{
		std::cerr << "Method not recognized" << std::endl;
	}


	for (int i=0; i<columns; i++){
		solutions.push_back(gsl_vector_get(x,i));
	}

	gsl_vector_free(x);
	return solutions;
}
