#include "leastsquares.h"
#include "graphdatareader.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "You didn't supply the filename! (Or supplied too many arguments!). Should be [./polyfitter `filename`]" << std::endl;
        exit(0);
    }

    GraphDataReader dr(argv[1]);
    dr.readtxt();

    std::vector<double> x = dr.get_x_data();
    std::vector<double> y = dr.get_y_data();
    std::vector<double> u = dr.get_unc_data();

    LeastSquares lls(y, x, u);

    lls.fit();
    lls.fitReport();

    return 0;
}
