#include <iostream>
#include <exception>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "leastsquares.h"

int main(int argc, char** argv) {
    int n = 6;

    std::vector<double> x = {1.5, 1.8, 2.5, 2.9, 3.3, 3.8};
    std::vector<double> y = {10, 14, 2, 26, 31, 40};
    std::vector<double> u = {1, 2, 1, 3, 1, 1};

    LeastSquares lls(y, x, u);
    lls.fit();

    // for (double param : lls.getParameters()) {
    //     std::cout << "Parameters: " << param << std::endl;
    // }

    return 0;
}

// using matrix_d = std::vector<std::vector<double>>;

// void printMatrix(const matrix_d &matrix) {
//     std::cout << "------------- [MATRIX] -------------" << std::endl;
//     for (int i = 0; i < matrix.size(); ++i) {
//         for (int j = 0; j < matrix[i].size(); ++j) {
//             std::cout << matrix[i][j] << "\t";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "----------- [END MATRIX] -----------" << std::endl;
// }

// matrix_d populateErrorMatrix(int n, const double* uncertainties) {
//     /*
//         Generates a square diagonal matrix of uncertainties given a number of rows & columns 
//         and a 1D array of uncertainties related to the y_n'th error.
//     */

//     matrix_d matrix; // define dynamically allocated array & initialize rows
    
//     for (int i = 0; i < n; ++i) {
//         std::vector<double> row;
//         for (int j = 0; j < n; ++j) {
//             if (i == j)
//                 row.push_back(pow(uncertainties[i], 2));
//             else
//                 row.push_back(0);
//         }
//         matrix.push_back(row);
//     }
    
//     return matrix;
// }

// matrix_d polulateDataMatrix(int nrows, int ncols, const double* data) {
//     /*
//         Generates a matrix.
//     */

//     matrix_d matrix; // define dynamically allocated array & initialize rows
    
//     for (int i = 0; i < nrows; ++i) {
//         std::vector<double> row;
//         for (int j = 0; j < ncols; ++j) {
//             row.push_back(pow(data[i], j));
//         }
//         matrix.push_back(row);
//     }
    
//     return matrix;
// }

// matrix_d transposeMatrix(const matrix_d &matrix) {
//     /*
//         Generates a matrix.
//     */

//     matrix_d tmatrix(matrix[0].size(), std::vector<double>());
    
//     for (int i = 0; i < matrix.size(); ++i) {
//         for (int j = 0; j < matrix[0].size(); ++j) {
//             if (tmatrix[j].size() != matrix.size())
//                 tmatrix[j].resize(matrix.size());
//             tmatrix[j][i] = matrix[i][j];
//         }
//     }
    
//     return tmatrix;
// }

// matrix_d multiplyMatrix(const matrix_d &matrix1, const matrix_d &matrix2) {
//     /*
//         Returns the result of the matrix multiplication matrix1*matrix2.
//     */

//     int nrows1 = matrix1.size();
//     int ncols1 = matrix1[0].size();
//     int nrows2 = matrix2.size();
//     int ncols2 = matrix2[0].size();

//     if (ncols1 != nrows2) {
//         throw std::invalid_argument("Matrices have dissimilar rows/columns, thus cannot be multiplied!");
//     }

//     matrix_d product(nrows1, std::vector<double>());

//     for (int n = 0; n < nrows1; ++n) {
//         for (int m = 0; m < ncols2; ++m) {
//             product[n].push_back(0);
//         }
//     }

//     for(int i = 0; i < nrows1; ++i) {
//         for(int j = 0; j < ncols2; ++j) { 
//             for(int k = 0; k < ncols1; ++k) {
//                 product[i][j] += matrix1[i][k] * matrix2[k][j];
//             }
//         }
//     }

//     return product;
// }

// double determinant(matrix_d matrix) {
//     if (matrix.size()*matrix[0].size() == 1)
//         return matrix[0][0];
    
//     double det;

//     for (int i = 0; i < matrix[0].size(); ++i) {
//         matrix_d slice;

//         for (int n = 1; n < matrix.size(); ++n) {
//             std::vector<double> srow;
//             for (int m = 0; m < matrix[0].size(); ++m) {
//                 if (m != i)
//                     srow.push_back(matrix[n][m]);
//             }
//             slice.push_back(srow);
//         }

//         det += matrix[0][i]*pow(-1, 2 + i)*determinant(slice);
//     }

//     return det;
// }

// double cofactor(const matrix_d &matrix, int row, int col) {
//     matrix_d minor;

//     for (int i = 0; i < matrix.size(); ++i) {
//         if (i != row) {
//             std::vector<double> mrow;
//             for (int j = 0; j < matrix[0].size(); ++j) {
//                 if (j != col)
//                     mrow.push_back(matrix[i][j]);
//             }
//             minor.push_back(mrow);
//         }
//     }

//     return pow(-1, 2 + row + col)*determinant(minor);
// }

// matrix_d adjoint(const matrix_d &matrix) {
//     matrix_d adj(matrix.size(), std::vector<double>(matrix[0].size()));

//     for (int i = 0; i < matrix.size(); ++i) {
//         for (int j = 0; j < matrix[0].size(); ++j) {
//             adj[i][j] = cofactor(matrix, j, i); 
//         }
//     }

//     return adj;
// }

// matrix_d inverse(const matrix_d &matrix, const double &epsilon) {
//     /*
//         Inverts a matrix.
//     */

//     double det = determinant(matrix);
//     matrix_d adj = adjoint(matrix);

//     if (std::abs(det) <= epsilon) {
//         throw std::invalid_argument("The matrix is singular, det(matrix) = " + std::to_string(det));
//     }

//     matrix_d inv(matrix.size(), std::vector<double>(matrix[0].size()));

//     for (int i = 0; i < matrix.size(); ++i) {
//         for (int j = 0; j < matrix[0].size(); ++j) {
//             inv[i][j] = adj[i][j]/det;
//         }
//     }

//     return inv;
// }

// matrix_d genMatrix(int nrows, int ncols) {

//     matrix_d matrix;

//     for (int i = 0; i < nrows; ++i) {
//         std::vector<double> row;
//         for (int j = 0; j < ncols; ++j) {
//             double val = i*j;
//             row.push_back(val);
//         }
//         matrix.push_back(row);
//     }
    
//     return matrix;
// }

// int main(int argc, char** argv) {

//     Matrix A(2, 2);
//     Matrix B(2, 2);
//     Matrix C(3, 3);

//     double arra[4] = {3, 1, 4, 1};
//     double arrb[4] = {7, 5, 0, 2};

//     A.fill(arra);
//     B.fill(arrb);

//     Matrix A_T = A.transpose();
//     A.show();
//     A_T.show();

//     Matrix AB = A.multiply(B);
//     AB.show();  

//     // double arr[9] = {2, 5, 4, 3, 1, 2, 5, 4, 6};
//     double arrc[9] = {2, 1, 2, 3, 2, 2, 1, 2, 3};

//     C.fill(arrc);
//     C.show();

//     double d = C.determinant();

//     std::cout << "Det(C) = " << d << std::endl;

//     Matrix adj_c = C.adjoint();
//     adj_c.show();

//     Matrix inv_result = C.inverse();
//     inv_result.show();
    
//     return 0;
// }