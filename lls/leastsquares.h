#ifndef __LEASTSQUARES_H_INCLUDED__
#define  __LEASTSQUARES_H_INCLUDED__ 

#include <vector>

class LeastSquares {
    private:
        double slope;
        double intercept;

    public:
        LeastSquares();
        ~LeastSquares();

        void fit();
        std::pair<double, double> getParameters();
};

#endif 