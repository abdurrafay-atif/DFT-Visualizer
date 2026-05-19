#include <stdio.h>
#include <math.h>

// there are three ways complex numbers can be presented
enum Complex_Format
{
    RECT = 0,
    POLAR = 1,
    EXP = 2,
};

// a struct which represents a complex number + its modulus & angle
typedef struct 
{
    double real;
    double imaginary;
    double modulus;
    double angle;
}
complex_number_t;

// defining complex numbers
void complex_num_init(complex_number_t *complex_number, double real, double imaginary);
void complex_num_rev_init(complex_number_t *complex_number, double modulus, double angle);

// printing complex numbers
void complex_print_rect(complex_number_t complex_number);
void complex_print_polar(complex_number_t complex_number);
void complex_print_exponential(complex_number_t complex_number);
void complex_print(complex_number_t complex_number, int format);
void complex_print_all_forms(complex_number_t complex_number);

// complex number arithmetic
void complex_scale(complex_number_t *scale, complex_number_t complex_number, double scaling_factor);
void complex_add(complex_number_t *sum, complex_number_t complex_number_1, complex_number_t complex_number_2);
void complex_subtract(complex_number_t *diff, complex_number_t complex_number_1, complex_number_t complex_number_2);
void complex_multiply(complex_number_t *product, complex_number_t complex_number_1, complex_number_t complex_number_2);
void complex_divide(complex_number_t *quotient, complex_number_t complex_number_1, complex_number_t complex_number_2);
void complex_pow(complex_number_t *result, complex_number_t complex_number, double power);

// miscelleanous functions (included in complex_arith.c)
double normalize_angle(double angle);
void complex_inverse(complex_number_t *inverse, complex_number_t complex_number);
void complex_conjugate(complex_number_t *conjugate, complex_number_t complex_number);
