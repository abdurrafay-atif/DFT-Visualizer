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

// vector I/O operations
int cvector_display(FILE *file, cvector_t v, int format);   // for output file of program
int cvector_write(FILE *file, cvector_t v, int format);     // inserting vector contents into external file
int cvector_read(FILE *file, cvector_t *v, int format);     // extracting from an external file
int cvector_plot(FILE *file, cvector_t v, int height, int low, int high); // for main function

// vector operations
int cvector_place(cvector_t *v, int index, double real, double imaginary);
int cvector_rev_place(cvector_t *v, int index, double modulus, double angle);
cvector_t *cvector_append_zeros(cvector_t v, int zero_pad);
cvector_t *cvector_conj(cvector_t v); // for dot product
cvector_t *cvector_scale(cvector_t v, complex_number_t scale);
cvector_t *cvector_add(cvector_t v1, cvector_t v2);
cvector_t *cvector_element_product(cvector_t v1, cvector_t v2);
cvector_t *cvector_circ_convolve(cvector_t v1, cvector_t v2);

// vector calculations
double cvector_max(cvector_t v);
int cvector_sum(complex_number_t *cn, cvector_t v);
int cvector_dot_product(complex_number_t *cn, cvector_t v1, cvector_t v2);

// transformations
cvector_t *cvector_circ_reverse(cvector_t v);
cvector_t *cvector_circ_shift(cvector_t v, int shift);
cvector_t *cvector_fourier_modulate(cvector_t v, int index);

#endif
