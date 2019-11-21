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

/**
    Fill a matrix row wise with the supplied array of elements.
    Note: the size of elements has to match the size of the matrix!
    
    @param elements the doubles array containing the elements to be entered into the matrix.
    @return the 'filled' matrix.
*/
void Matrix::fill(const double elements[]) {
    for (int i = 0; i < this->nrows; ++i) {
        std::vector<double> row;
        for (int j = 0; j < this->ncols; ++j) {
            double val = elements[this->ncols*i+j];
            row.push_back(val);
        }
        this->matrix.push_back(row);
    }
}

/**
    Returns the multiple of two matrices in the order:
    this_matrix*other_matrix. Note that the number of 
    columns of the first has to match the number of rows 
    of the second matrix.
    
    @param other_matrix the other matrix.
    @return the product of the two matrices.
*/
Matrix Matrix::multiply(Matrix &other_matrix) {
    const int onrows = other_matrix.getRowCount();
    const int oncols = other_matrix.getColCount();
    const matrix_d om = other_matrix.getMatrix();


    if (this->ncols != onrows) {
        throw std::invalid_argument("Matrices have dissimilar rows/columns, thus cannot be multiplied!");
    }

    double prod_el[this->nrows*oncols];

    for(int i = 0; i < this->nrows; ++i) {
        for(int j = 0; j < oncols; ++j) {
            double el = 0;

            for(int k = 0; k < this->ncols; ++k) {
                el += this->matrix[i][k] * om[k][j];
            }
            
            prod_el[oncols*i + j] = el;
        }
    }
    
    Matrix product(this->nrows, oncols, prod_el);

    return product;
}

/**
    Returns the inverse of the matrix, given some small 
    value epsilon meant as error (since zero might be 
    represented by a very small double).
    
    @param epsilon the double resembling an error term, often rather small.
    @return the inverse of this matrix.
*/
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
            inv_el[this->ncols*i + j] = adj_matrix[i][j]/det;
        }
    }
    
    Matrix inv(this->nrows, this->ncols, inv_el);

    return inv;
}

/**
    Yields the transpose of this matrix.
    
    @return the transpose of this matrix.
*/
Matrix Matrix::transpose() {
    double trans_el[this->nrows*this->ncols];
    
    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            trans_el[this->nrows*j + i] = matrix[i][j];
        }
    }

    Matrix tmatrix(this->ncols, this->nrows, trans_el);

    return tmatrix;
}

/**
    Yields the adjoint of this matrix.
    
    @return the adjoint of this matrix.
*/
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

/**
    Convert the matrix into a 1D vector.
    
    @return a vector of the elements of this matrix.
*/
std::vector<double> Matrix::flatten() {
    std::vector<double> flat;

    for (int i = 0; i < this->nrows; ++i) {
        for (int j = 0; j < this->ncols; ++j) {
            flat.push_back(this->matrix[i][j]); 
        }
    }

    return flat;
}

/**
    Yields the determinant of a matrix.

    @param mat the matrix of which the determinant will be calculated.
    @return the determinant of the matrix mat.
*/
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

/**
    Yields the determinant of this matrix.

    @return the determinant of this matrix.
*/
double Matrix::determinant() {
    const matrix_d M = this->matrix;
    return this->determinant(M);
}

/**
    Yields the cofactor of a matrix at a certain position.

    @param mat the matrix for which the cofactor will be calculated.
    @param row the integer row that will be expanded on.
    @param col the integer column that will be expanded on.
    @return the cofactor as a matrix.
*/
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

/**
    Displays this matrix.
*/
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