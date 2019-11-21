#include "graphdatareader.h"

GraphDataReader::GraphDataReader(std::string filename) {
    this->fn = filename;
}

GraphDataReader::~GraphDataReader() {}

/**
    Splits the string of the row of data in individual data elements.
    
    @param str the string that resembles a row in the data file.
    @return the vector containing all data elements in a row in the data file.
*/
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

/**
    Convert a vector of strings to a vector of doubles.
    
    @param vstr the vector of strings.
    @return the vector of doubles.
*/
std::vector<double> GraphDataReader::vstring_to_vdouble(std::vector<std::string> &vstr) {
    std::vector<double> vdouble;

    auto to_str = [&vdouble] (const std::string &str) { vdouble.push_back(std::stod(str)); };
    std::for_each(vstr.begin(), vstr.end(), to_str);

    return vdouble;
}

/**
    Read the data in the file and convert it to usable  data of type double.
    Note the structure of the file should be: containing three columns of data, 
    using a dot to seperate the decimal parts. And the columns should be 
    seperated by spaces.
*/
void GraphDataReader::readtxt() {
    std::ifstream file(this->fn);

    if (file.fail()) {
        std::cerr << "Could not open the supplied file!" << std::endl;
        exit(0);
    }

    std::string cur_line;
    if (file.is_open()) {
        while (std::getline(file, cur_line)) {
            std::vector<std::string> row_items = this->vectorize_row(cur_line);
            std::vector<double> row_items_d = this->vstring_to_vdouble(row_items);

            this->x_data.push_back(row_items_d.at(0));
            this->y_data.push_back(row_items_d.at(1));
            this->unc_data.push_back(row_items_d.at(2));
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