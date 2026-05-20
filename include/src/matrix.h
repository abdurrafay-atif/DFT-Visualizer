#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "complex.h"

// struct representing a complex N x M matrix
typedef struct 
{
    complex_number_t **mat;
    int rows;
    int cols;
}
cmatrix_t;

// defining matrix
cmatrix_t *cmatrix_init(int rows, int cols);

// matrix operations
int cmatrix_place(cmatrix_t *m, complex_number_t cn, int row, int col);
cmatrix_t *cmatrix_add(cmatrix_t m1, cmatrix_t m2);
cmatrix_t *cmatrix_scale(cmatrix_t m, double scale);
cmatrix_t *cmatrix_multiply(cmatrix_t m1, cmatrix_t m2);

#endif

