#ifndef MAT_VEC_H
#define MAT_VEC_H

#include "matrix.h"
#include "vector.h"

// this file includes functions involving both matrices & vectors

// filling matrices with vectors
int fill_row(cmatrix_t *m, cvector_t v, int row);
int fill_col(cmatrix_t *m, cvector_t v, int col);

// operations
cvector_t *circ_convolve(cvector_t v);

#endif