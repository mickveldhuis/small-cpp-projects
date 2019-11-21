#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include<algorithm>

class GraphDataReader {
    private:
        std::string fn;

        std::vector<double> x_data;
        std::vector<double> y_data;
        std::vector<double> unc_data;

        std::vector<std::string> vectorize_row(std::string &str);
        std::vector<double> vstring_to_vdouble(std::vector<std::string> &vstr);

    public:
        GraphDataReader(std::string filename);
        ~GraphDataReader();

        void readtxt();
        std::vector<double> get_x_data();
        std::vector<double> get_y_data();
        std::vector<double> get_unc_data();
};