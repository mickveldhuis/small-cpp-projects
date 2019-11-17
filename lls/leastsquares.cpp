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
            data_el[ncols*i + j] = pow(data[i], j);
        }
    }
    
    Matrix matrix(nrows, ncols, data_el);

    return matrix;
}

LeastSquares::LeastSquares(std::vector<double> y, std::vector<double> x, std::vector<double> unc, int n_params) {
    this->uncertainties = unc;
    this->y_data = y;
    this->x_data = x;

    this->N = y.size();
    this->num_params = n_params;

    if (this->N != this->x_data.size() || this->N != this->uncertainties.size() || this->x_data.size() != this->uncertainties.size()) {
        throw std::invalid_argument("Arrays x, y, and unc don't all have the same dimensions!");
    }
}

LeastSquares::~LeastSquares() {
}

void LeastSquares::fit() {
    int n_params = 2;
    
    Matrix E = this->populateErrorMatrix(this->N, this->uncertainties);
    Matrix A = this->polulateDataMatrix(this->N, n_params, this->x_data);
    Matrix Y(this->N, 1, this->y_data.data());

    Matrix E_inv = E.inverse();
    Matrix A_trans = A.transpose();

    Matrix cov_matrix = (A_trans.multiply(E_inv).multiply(A)).inverse();
    Matrix rest = A_trans.multiply(E_inv).multiply(Y);
    
    Matrix params = cov_matrix.multiply(rest);

    // this->cov = cov_matrix;
    this->parameters = params.flatten();
    this->chi_squared = this->calculateChi2();
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

double LeastSquares::getChi2() {
    return this->chi_squared;
}

void LeastSquares::fitReport() {
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "|   Model: y = a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n [with n = " << this->num_params  << "]   |" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;
    std::cout << "    Parameters = { ";
    for (int i = 0; i < this->num_params; ++i) {
        std::string prefix = "";

        if (i != 0)
            prefix = ", ";

        std::cout << prefix << "a[" << i << "] = " << this->parameters[i];
    }
    std::cout << " }" << std::endl;

    std::cout << "    Chi^2      = " << this->chi_squared << std::endl;
}