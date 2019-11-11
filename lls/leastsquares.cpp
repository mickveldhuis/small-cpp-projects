#include "leastsquares.h"

using matrix_d = std::vector< std::vector<double> >;

Matrix LeastSquares::populateErrorMatrix(int n, const double uncertainties[]) {
    /*
        Generates a square diagonal matrix of uncertainties given a number of rows & columns 
        and a 1D array of uncertainties related to the y_n'th error.
    */
    double error_el[n*n];
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                error_el[n*i + j] = pow(uncertainties[i], 2);
            else
                error_el[n*i + j] = 0;
        }
    }

    Matrix matrix(n, n, error_el);
    
    return matrix;
}

Matrix LeastSquares::polulateDataMatrix(int nrows, int ncols, const double data[]) {
    /*
        Generates a `data` matrix.
    */
    double data_el[nrows*ncols];
    
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            data_el[nrows*i + j] = pow(data[i], j);
        }
    }
    
    Matrix matrix(nrows, ncols, data_el);

    return matrix;
}

LeastSquares::LeastSquares(const double y_data[], const double x_data[], const double uncertainties[]) {

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
