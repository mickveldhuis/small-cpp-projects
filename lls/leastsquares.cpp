#include "leastsquares.h"

using matrix_d = std::vector< std::vector<double> >;

/**
    Generates a square diagonal matrix of uncertainties given a number of rows & columns 
    and a 1D array of uncertainties related to the y_n'th error.
    
    @param n the number of columns and rows of the resulting matrix.
    @param unc the vector containing the uncertainty of the y-axis data points to be inserted in the matrix.
    @return the square diagonal matrix containing the squared uncertainties.
*/
Matrix LeastSquares::populateErrorMatrix(int n, const std::vector<double> unc) {
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

/**
    @param nrows the number of rows the data matrix should have, equal to the number of data points.
    @param ncols the number of columns the data matrix should have, equal to the number of parameters.
    @param data the vector containing the data to be inserted in the matrix.
    @return the matrix dealing with the x-axis data.
*/
Matrix LeastSquares::polulateDataMatrix(int nrows, int ncols, const std::vector<double> data) {
    double data_el[nrows*ncols];

    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            data_el[ncols*i + j] = pow(data[i], j);
        }
    }
    
    Matrix matrix(nrows, ncols, data_el);

    return matrix;
}

/**
    @param y the vector containing the data points on the y-axis.
    @param x the vector containing the data points on the x-axis.
    @param unc the vector containing the uncertainties in the data points on the y-axis.
    @param n_params the integer specifying the number of parameters the model should contain.
*/
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

/**
    Determine the parameters of the specified model.
*/
void LeastSquares::fit() {
    Matrix E = this->populateErrorMatrix(this->N, this->uncertainties);
    Matrix A = this->polulateDataMatrix(this->N, this->num_params, this->x_data);
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

/**
    Returns the parameters of the fit with a linear model.

    @return a vector containing the parameters.
*/
std::vector<double> LeastSquares::getParameters() {
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

/**
    Get the model a_0 + a_1*x + ... evaluated at the point x.

    @param x the value x for which to evaluate the model.
    @return the model evaluated at x.
*/
double LeastSquares::getModel(double x) {
    double m_value = 0;

    for (int i = 0; i < 2; ++i) {
        m_value += this->parameters[i]*pow(x, i);
    }
    
    return m_value;
}

/**
    Returns the chi^2 metric for the used model.

    @return chi^2.
*/
double LeastSquares::getChi2() {
    return this->chi_squared;
}

/**
    Prints the parameters and chi^2.
*/
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