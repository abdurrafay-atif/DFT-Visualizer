#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include "complex.h"
#include "sinusoids.h"

// struct representing a complex N-order vector
typedef struct 
{
    complex_number_t *vec;
    int size;
}
cvector_t;

// defining vector
cvector_t *cvec_init(complex_number_t *cn, int size); // initializing based on already existing array 
cvector_t *cvec_init_empty(int size); // empty vector
cvector_t *cvec_conj(cvector_t v); // for dot product
int cvec_free(cvector_t *v);
void cvec_print(cvector_t v, int format);

// vector computations
int cvec_sum(complex_number_t *cn, cvector_t v);
int cvec_dot_product(complex_number_t *cn, cvector_t v1, cvector_t v2);
double cvec_norm(cvector_t v);
int cvec_project(complex_number_t *cn, cvector_t v1, cvector_t v2); // projection of v2 onto v1

// vector operations
cvector_t *cvec_scale(cvector_t v, complex_number_t scale);
cvector_t *cvec_add(cvector_t v1, cvector_t v2);
cvector_t *cvec_element_prod(cvector_t v1, cvector_t v2);

// transformations
cvector_t *cvec_circ_reverse(cvector_t v);
cvector_t *cvec_circ_shift(cvector_t v, int shift);
cvector_t *cvec_fourier_modulate(cvector_t v, int index);

#endif
