#include "leastsquares.h"
#include <vector>
#include <cmath>

using matrix_d = std::vector< std::vector<double> >;

matrix_d populateErrorMatrix(int n, const double* uncertainties) {
    /*
        Generates a square diagonal matrix of uncertainties given a number of rows & columns 
        and a 1D array of uncertainties related to the y_n'th error.
    */

    matrix_d matrix; // define dynamically allocated array & initialize rows
    
    for (int i = 0; i < n; ++i) {
        std::vector<double> row;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                row.push_back(pow(uncertainties[i], 2));
            else
                row.push_back(0);
        }
        matrix.push_back(row);
    }
    
    return matrix;
}

matrix_d polulateDataMatrix(int nrows, int ncols, const double* data) {
    /*
        Generates a matrix.
    */

    matrix_d matrix; // define dynamically allocated array & initialize rows
    
    for (int i = 0; i < nrows; ++i) {
        std::vector<double> row;
        for (int j = 0; j < ncols; ++j) {
            row.push_back(pow(data[i], j));
        }
        matrix.push_back(row);
    }
    
    return matrix;
}

LeastSquares::LeastSquares() {

}

LeastSquares::~LeastSquares() {

}

void LeastSquares::fit() {

}

std::pair<double, double> LeastSquares::getParameters() {
    /*
        Returns a pair containing the two parameters of the fit 
        with a linear model [y = ax + b].
    */
    std::pair<double, double> params = {this->slope, this->intercept};
    return params;
}
