#ifndef ROOTDIAGONALIZER_H
#define ROOTDIAGONALIZER_H



class ROOTDiagonalizer{
public:
	ROOTDiagonalizer(std::vector<double>, std::vector<double>, int, int);
	std::vector<double> diagonalize(std::string);

private:
	int rows;
	int columns;
	std::vector<double> matrixA;
	std::vector<double> vecB;
};


#endif
