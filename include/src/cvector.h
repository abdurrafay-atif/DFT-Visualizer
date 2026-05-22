#ifndef CVECTOR_H
#define CVECTOR_H

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
cvector_t *cvector_init(complex_number_t *cn, int size); // initializing based on already existing array 
cvector_t *cvector_init_empty(int size); // empty vector
int cvector_free(cvector_t *v);
void cvector_print(cvector_t v, FILE *file, int format);

// vector operations
cvector_t *cvector_conj(cvector_t v); // for dot product
int cvector_sum(complex_number_t *cn, cvector_t v);
int cvector_dot_product(complex_number_t *cn, cvector_t v1, cvector_t v2);
int cvector_place(cvector_t *v, int ele, double real, double imaginary);
int cvector_rev_place(cvector_t *v, int ele, double modulus, double angle);
cvector_t *cvector_scale(cvector_t v, complex_number_t scale);
cvector_t *cvector_add(cvector_t v1, cvector_t v2);
cvector_t *cvector_element_prod(cvector_t v1, cvector_t v2);

// transformations
cvector_t *cvector_circ_reverse(cvector_t v);
cvector_t *cvector_circ_shift(cvector_t v, int shift);
cvector_t *cvector_fourier_modulate(cvector_t v, int index);

#endif
