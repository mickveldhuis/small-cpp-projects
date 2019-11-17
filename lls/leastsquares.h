#ifndef __LEASTSQUARES_H_INCLUDED__
#define  __LEASTSQUARES_H_INCLUDED__ 

#include "matrices.h"

class LeastSquares {
    private:
        // Matrix parameters;
        std::vector<double> parameters;
        // Matrix cov; // Needs default constructor!
        double chi_squared;

        std::vector<double> uncertainties;
        std::vector<double> y_data;
        std::vector<double> x_data;
        
        int N;
        int num_params;

        double calculateChi2();
        double getModel(double x);

        Matrix polulateDataMatrix(int nrows, int ncols, const std::vector<double> data);
        Matrix populateErrorMatrix(int n, const std::vector<double> unc);

    public:
        LeastSquares(std::vector<double> y, std::vector<double> x, std::vector<double> unc, int n_params = 2);
        ~LeastSquares();

        void fit();
        double getChi2();
        void fitReport();

        std::vector<double> getParameters();
        Matrix getCovarianceMatrix();
};

#endif 