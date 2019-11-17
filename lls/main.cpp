#include "leastsquares.h"

int main(int argc, char** argv) {
    int n = 6;

    std::vector<double> x = {1.5, 1.8, 2.5, 2.9, 3.3, 3.8};
    std::vector<double> y = {10, 14, 21, 26, 31, 40};
    std::vector<double> u = {1, 2, 1, 3, 2, 1};

    LeastSquares lls(y, x, u);
    lls.fit();

    for (double param : lls.getParameters()) {
        std::cout << "Parameters: " << param << std::endl;
    }

    std::cout << "Chi^2 = " << lls.getChi2() << std::endl;

    return 0;
}