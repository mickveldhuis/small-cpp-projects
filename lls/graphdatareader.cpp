#include "graphdatareader.h"

GraphDataReader::GraphDataReader(std::string filename) {
    this->fn = filename;
}

GraphDataReader::~GraphDataReader() {}


std::vector<std::string> GraphDataReader::vectorize_row(std::string &str) {
    std::vector<std::string> subs;
    
    std::string sub = "";
    for (int i = 0; i < str.size(); ++i) {
        if (std::isspace(str.at(i)) && !sub.empty()) {
            subs.push_back(sub);
            sub = "";
        } else if (!std::isspace(str.at(i))) {
            sub += str.at(i);
        }
    }

    if (!sub.empty())
        subs.push_back(sub);

    return subs;
}

std::vector<double> GraphDataReader::vstring_to_vdouble(std::vector<std::string> &vstr) {
    std::vector<double> vdouble;

    auto to_str = [&vdouble] (const std::string &str) { vdouble.push_back(std::stod(str)); };
    std::for_each(vstr.begin(), vstr.end(), to_str);

    return vdouble;
}

void GraphDataReader::readtxt(int ncols, int nx_col, int ny_col, int nunc_col) {
    std::ifstream file;
    file.open(this->fn);

    std::string cur_line;
    if (file.is_open()) {
        while (std::getline(file, cur_line)) {
            std::vector<std::string> row_items = this->vectorize_row(cur_line);
            std::vector<double> row_items_d = this->vstring_to_vdouble(row_items);

            this->x_data.push_back(row_items_d.at(nx_col - 1));
            this->y_data.push_back(row_items_d.at(ny_col - 1));
            this->unc_data.push_back(row_items_d.at(nunc_col - 1));
        }

        file.close();
    } else {
        std::cout << "Could not open file!" << std::endl;
    }
}


std::vector<double> GraphDataReader::get_x_data(){
    return this->x_data;
}

std::vector<double> GraphDataReader::get_y_data() {
    return this->y_data;
}

std::vector<double> GraphDataReader::get_unc_data() {
    return this->unc_data;
}