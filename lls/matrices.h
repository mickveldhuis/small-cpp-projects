#ifndef __MAT_H_INCLUDED__
#define  __MAT_H_INCLUDED__ 

#include <iostream>
#include <exception>
#include <vector>
#include <cmath>

using matrix_d = std::vector<std::vector<double>>;

class Matrix {
    private:
        matrix_d matrix;
        // double elements[];
        int nrows;
        int ncols;

        double determinant(const matrix_d &matrix);
        double cofactor(const matrix_d &matrix, int row, int col);

    public:
        Matrix(int nrows, int ncols);
        Matrix(int nrows, int ncols, const double elements[]);
        ~Matrix();

        Matrix multiply(Matrix &other_matrix);
        Matrix inverse(const double &epsilon = 0.0000001);
        Matrix transpose();
        Matrix adjoint();

        std::vector<double> flatten();
        
        double determinant();

        void show();
        void fill(const double elements[]);

        int getRowCount();
        int getColCount();

        matrix_d getMatrix();
};

#endif 