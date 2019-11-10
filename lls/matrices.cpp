#include "matrices.h"

Matrix::Matrix(int nrows, int ncols) {
    this->nrows = nrows;
    this->ncols = ncols;
}

Matrix::Matrix(int nrows, int ncols, const double elements[]) : Matrix(nrows, ncols) {
    this->fill(elements);
}

Matrix::~Matrix() {
    this->matrix.clear();
}

void Matrix::fill(const double elements[]) {
    for (int i = 0; i < nrows; ++i) {
        std::vector<double> row;
        for (int j = 0; j < ncols; ++j) {
            double val = elements[this->nrows*i+j];
            row.push_back(val);
        }
        this->matrix.push_back(row);
    }
}

Matrix Matrix::multiply(Matrix &other_matrix) {
    const int onrows = other_matrix.getRowCount();
    const int oncols = other_matrix.getColCount();
    const matrix_d om = other_matrix.getMatrix();


    if (this->ncols != onrows) {
        throw std::invalid_argument("Matrices have dissimilar rows/columns, thus cannot be multiplied!");
    }

    double prod_el[this->nrows*oncols];
    std::vector<double> prod_elem;

    for(int i = 0; i < this->nrows; ++i) {
        for(int j = 0; j < oncols; ++j) {
            double el = 0;

            for(int k = 0; k < this->ncols; ++k) {
                el += this->matrix[i][k] * om[k][j];
            }
            
            prod_el[this->nrows*i + j] = el;
        }
    }

    Matrix product(this->nrows, oncols, prod_el);

    return product;
}

Matrix Matrix::inverse(const double &epsilon) {
    double det = this->determinant();
    Matrix adj = this->adjoint();

    if (std::abs(det) <= epsilon) {
        throw std::invalid_argument("The matrix is singular, det(matrix) = " + std::to_string(det));
    }
    
    double inv_el[this->nrows*this->ncols];

    matrix_d adj_matrix = adj.getMatrix();

    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            inv_el[this->nrows*i + j] = adj_matrix[i][j]/det;
        }
    }
    
    Matrix inv(this->nrows, this->ncols, inv_el);

    return inv;
}

Matrix Matrix::transpose() {
    /*
        Returns the transpose of the matrix.
    */

   double trans_el[this->nrows*this->ncols];
    
    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            // tmatrix[j][i] = matrix[i][j];
            trans_el[this->nrows*j + i] = matrix[i][j];
        }
    }

    Matrix tmatrix(this->ncols, this->nrows, trans_el);

    return tmatrix;
}

Matrix Matrix::adjoint() {
    double adj_el[this->nrows*this->ncols];

    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            adj_el[this->nrows*i + j] = cofactor(this->matrix, j, i); 
        }
    }

    Matrix adj(this->nrows, this->ncols, adj_el);

    return adj;
}

matrix_d Matrix::getMatrix() {
    return this->matrix;
}

double Matrix::determinant(const matrix_d &mat) {
    if (mat.size()*mat[0].size() == 1)
        return mat[0][0];
    
    double det;

    for (int i = 0; i < mat[0].size(); ++i) {
        matrix_d slice;

        for (int n = 1; n < mat.size(); ++n) {
            std::vector<double> srow;
            
            for (int m = 0; m < mat[0].size(); ++m) {
                if (m != i) {
                    srow.push_back(mat[n][m]);
                }
            }
            slice.push_back(srow);
        }

        det += mat[0][i]*pow(-1, 2 + i)*determinant(slice);
    }

    return det;
}

double Matrix::determinant() {
    const matrix_d M = this->matrix;
    return this->determinant(M);
}

double Matrix::cofactor(const matrix_d &mat, int row, int col) {
    matrix_d minor;

    for (int i = 0; i < mat.size(); ++i) {
        if (i != row) {
            std::vector<double> mrow;
            for (int j = 0; j < mat[0].size(); ++j) {
                if (j != col)
                    mrow.push_back(mat[i][j]);
            }
            minor.push_back(mrow);
        }
    }

    return pow(-1, 2 + row + col)*determinant(minor);    
}

void Matrix::show() {
    std::cout << "-------------- [  MATRIX  ] --------------" << std::endl;
    
    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            std::cout << this->matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    std::cout << "-------------- [END MATRIX] --------------" << std::endl;
}

int Matrix::getRowCount() {
    return this->nrows;
}

int Matrix::getColCount() {
    return this->ncols;
}