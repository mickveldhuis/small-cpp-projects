#include "leastsquares.h"

using matrix_d = std::vector< std::vector<double> >;

Matrix LeastSquares::populateErrorMatrix(int n, const std::vector<double> unc) {
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

Matrix LeastSquares::polulateDataMatrix(int nrows, int ncols, const std::vector<double> data) {
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

LeastSquares::LeastSquares(std::vector<double> y, std::vector<double> x, std::vector<double> unc) {
    this->uncertainties = unc;
    this->y_data = y;
    this->x_data = x;

    this->N = y.size();

    if (this->N != this->x_data.size() || this->N != this->uncertainties.size() || this->x_data.size() != this->uncertainties.size()) {
        throw std::invalid_argument("Arrays x, y, and unc don't all have the same dimensions!");
    }
}

LeastSquares::~LeastSquares() {
}

void LeastSquares::fit() {
    int n_params = 2;

    Matrix E = this->populateErrorMatrix(this->N, this->uncertainties);
    Matrix A = this->polulateDataMatrix(n_params, this->N, this->x_data);
    Matrix Y(1, this->N, this->y_data.data);

    E.show();

    // Matrix E_inv = E.inverse();
    // Matrix cov_matrix = (A.transpose().multiply(E_inv).multiply(A)).inverse();
    // Matrix rest = A.transpose().multiply(E_inv).multiply(Y);

    // Matrix params = cov_matrix.multiply(rest);

    // this->cov = cov_matrix;
    // this->parameters = params.flatten();
    // this->chi_squared = this->calculateChi2();
}

std::vector<double> LeastSquares::getParameters() {
    /*
        Returns a pair containing the two parameters of the fit 
        with a linear model [y = ax + b].
    */
    return this->parameters;
}

double LeastSquares::calculateChi2() {
    double sum = 0;

    for (int i = 0; i < this->N; ++i) {
        double diff = this->y_data[i]-this->getModel(this->x_data[i]);
        sum += pow(diff/this->uncertainties[i], 2);
    }

    return sum;
}

double LeastSquares::getModel(double x) {
    double m_value = 0;

    for (int i = 0; i < 2; ++i) {
        m_value += this->parameters[i]*pow(x, i);
    }
    
    return m_value;
}