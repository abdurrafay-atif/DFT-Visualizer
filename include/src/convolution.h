#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "cvector.h"

// struct representing a complex N x M matrix
typedef struct 
{
    complex_number_t **mat;
    int rows;
    int cols;
}
cmatrix_t;

// matrix & matrix ops
cmatrix_t *cmatrix_init(int rows, int cols);
int matrix_free(cmatrix_t *mat);
int cmatrix_place(cmatrix_t *mat, complex_number_t cn, int row, int col);
int cmatrix_fill_col(cmatrix_t *mat, cvector_t v, int col);
cmatrix_t *cmatrix_multiply(cmatrix_t mat1, cmatrix_t mat2);

// convolution
cmatrix_t *convolution_mat(cvector_t v1);
cvector_t *circ_convolve(cvector_t v1, cvector_t v2);

#endif