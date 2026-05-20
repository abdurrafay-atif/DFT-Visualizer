#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include "complex.h"

// struct representing a complex N-order vector
typedef struct 
{
    complex_number_t *vec;
    int size;
}
cvector_t;

// defining vector
cvector_t *cvector_init(int size);
cvector_t *cvector_conj(cvector_t v); // for dot product

// vector computations
double dot_product(cvector_t v1, cvector_t v2);
double vec_norm(cvector_t v1);
double vec_angle(cvector_t v1, cvector_t v2);
double vec_project(cvector_t v1, cvector_t v2); // projection of v2 onto v1

// vector operations
cvector_t *vec_scale(cvector_t v, complex_number_t scale);
cvector_t *vec_add(cvector_t v1, cvector_t v2);
cvector_t *element_prod(cvector_t v1, cvector_t v2);

// transformations
cvector_t *circ_reverse(cvector_t v);
cvector_t *circ_shift(cvector_t v);
cvector_t *fourier_modulate(cvector_t v);

#endif
