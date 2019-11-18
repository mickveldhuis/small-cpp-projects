#include "leastsquares.h"
#include "graphdatareader.h"

int main(int argc, char** argv) {
    GraphDataReader dr("data.txt");
    dr.readtxt(3);

    std::vector<double> x = dr.get_x_data();
    std::vector<double> y = dr.get_y_data();
    std::vector<double> u = dr.get_unc_data();

    LeastSquares lls(y, x, u);
    lls.fit();
    lls.fitReport();

    return 0;
}