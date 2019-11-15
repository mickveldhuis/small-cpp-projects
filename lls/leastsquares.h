#ifndef __LEASTSQUARES_H_INCLUDED__
#define  __LEASTSQUARES_H_INCLUDED__ 

#include "matrices.h"

class LeastSquares {
    private:
        Matrix parameters;
        Matrix cov;
        double chi_squared;

        double* uncertainties;
        double* y_data;
        double* x_data;
        
        int N;

        double calculateChi2();
        double getModel(double x);

        Matrix polulateDataMatrix(int nrows, int ncols, const double data[]);
        Matrix populateErrorMatrix(int n, const double unc[]);

    public:
        LeastSquares(double y[], double x[], double unc[]);
        ~LeastSquares();

        void fit();
        double getChi2();

        std::vector<double> getParameters();
        Matrix getCovarianceMatrix();
};

#endif 