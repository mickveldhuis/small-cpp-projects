#ifndef __LEASTSQUARES_H_INCLUDED__
#define  __LEASTSQUARES_H_INCLUDED__ 

#include "matrices.h"

class LeastSquares {
    private:
        double slope;
        double intercept;
        Matrix cov;
        double chi_squared;

        Matrix polulateDataMatrix(int nrows, int ncols, const double data[]);
        Matrix populateErrorMatrix(int n, const double uncertainties[]);

    public:
        LeastSquares(const double y_data[], const double x_data[], const double uncertainties[]);
        ~LeastSquares();

        void fit();
        double getChi2();

        std::pair<double, double> getParameters();
        Matrix getCovarianceMatrix();
};

#endif 