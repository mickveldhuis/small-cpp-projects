#include "leastsquares.h"

using matrix_d = std::vector< std::vector<double> >;

Matrix LeastSquares::populateErrorMatrix(int n, const double unc[]) {
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

LeastSquares::LeastSquares(double y[], double x[], double unc[]) {
    this->uncertainties = unc;
    this->y_data = y;
    this->x_data = x;

    this->N = sizeof(y)/sizeof(y[0]);

    int x_len = sizeof(x)/sizeof(x[0]);
    int unc_len = sizeof(unc)/sizeof(unc[0]);

    if (this->N != x_len || this->N != unc_len || x_len != unc_len) {
        throw std::invalid_argument("Arrays x, y, and unc don't all have the same dimensions!");
    }
}

LeastSquares::~LeastSquares() {
    delete this->uncertainties;
    delete this->x_data;
    delete this->y_data;
}

void LeastSquares::fit() {
    int n_params = 2;

    Matrix E = this->populateErrorMatrix(this->N, this->uncertainties);
    Matrix A = this->polulateDataMatrix(n_params, this->N, this->x_data);
    Matrix Y(1, this->N, this->y_data);

    Matrix E_inv = E.inverse();
    Matrix cov_matrix = (A.transpose().multiply(E_inv).multiply(A)).inverse();
    Matrix rest = A.transpose().multiply(E_inv).multiply(Y);

    Matrix params = cov_matrix.multiply(rest);

    this->cov = cov_matrix;
    this->parameters = params;
    this->chi_squared = this->calculateChi2();
}

std::vector<double> LeastSquares::getParameters() {
    /*
        Returns a pair containing the two parameters of the fit 
        with a linear model [y = ax + b].
    */
    std::vector<double> params;
    return params;
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
        // a_0+a_1*x+...
        // TODO: Add flatten method to matrix class!
    }
    
    return m_value;
}