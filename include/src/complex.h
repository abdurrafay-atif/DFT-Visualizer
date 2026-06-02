#ifndef COMPLEX_H  
#define COMPLEX_H  

#include <stdio.h> // for printing functions
#include <math.h> // for floating point library functions

// tags for each way a complex number can be represented
enum Complex_Format
{
    RECT = 1,
    POLAR = 2,
    EXP = 3,
};

// a struct which represents a complex number in cartesian / polar form
typedef struct 
{
    double real;
    double imaginary;
    double modulus;
    double angle;
}
complex_number_t;

// defining complex numbers
int complex_num_init(complex_number_t *cn, double real, double imaginary);
int complex_num_rev_init(complex_number_t *cn, double modulus, double angle);
int complex_num_empty(complex_number_t *cn);
double normalize_angle(double angle);

// writing complex numbers
int complex_write_rect(FILE *file, complex_number_t cn);
int complex_write_polar(FILE *file, complex_number_t cn);
int complex_write_exp(FILE *file, complex_number_t cn);
int complex_write(FILE *file, complex_number_t cn, int format);

// reading complex numbers
int complex_read_rect(FILE *file, complex_number_t *cn);
int complex_read_polar(FILE *file, complex_number_t *cn);
int complex_read_exp(FILE *file, complex_number_t *cn);
int complex_read(FILE *file, complex_number_t *cn, int format);

// complex number arithmetic
int complex_scale(complex_number_t *scale, complex_number_t cn, double scaling_factor);
int complex_add(complex_number_t *sum, complex_number_t cn1, complex_number_t cn2);
int complex_sub(complex_number_t *diff, complex_number_t cn1, complex_number_t cn2);
int complex_prod(complex_number_t *prod, complex_number_t cn1, complex_number_t cn2);
int complex_div(complex_number_t *quot, complex_number_t cn1, complex_number_t cn2);
int complex_pow(complex_number_t *res, complex_number_t cn, double power);
int complex_inv(complex_number_t *inv, complex_number_t cn);
int complex_conj(complex_number_t *conj, complex_number_t cn);

#endif
