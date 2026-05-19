#include "../include/complex_numbers/complex.h"

// scales the complex number by the passed in scaling factor
// scaled complex number stored in the first parameter (can be the same struct)
void complex_scale(complex_number_t *scale, complex_number_t complex_number, double scaling_factor)
{
    complex_num_init(scale, 
        complex_number.real * scaling_factor, 
        complex_number.imaginary * scaling_factor);
}

// adds the two complex numbers and stores it in the "sum" complex number
void complex_add(complex_number_t *sum, complex_number_t complex_number_1, complex_number_t complex_number_2)
{
    complex_num_init(sum, 
        complex_number_1.real + complex_number_2.real, 
        complex_number_1.imaginary + complex_number_2.imaginary);
}

// subtracts the second complex number from the first complex number, stores it in the "diff" complex number
void complex_subtract(complex_number_t *diff, complex_number_t complex_number_1, complex_number_t complex_number_2)
{
    complex_num_init(diff, 
        complex_number_1.real - complex_number_2.real, 
        complex_number_1.imaginary - complex_number_2.imaginary);
}

// multiplies the two passed in complex numbers, stored in "product" complex number
void complex_multiply(complex_number_t *product, complex_number_t complex_number_1, complex_number_t complex_number_2)
{
    complex_num_rev_init(product, 
        complex_number_1.modulus * complex_number_2.modulus, 
        complex_number_1.angle + complex_number_2.angle);
}

// divides the first complex number by the second one, stores it in the "quotient" complex number
void complex_divide(complex_number_t *quotient, complex_number_t complex_number_1, complex_number_t complex_number_2)
{
    // need to obtain inverse of complex_number_2 to divide
    complex_inverse(&complex_number_2, complex_number_2);
    // use multiplication function with inverse
    complex_multiply(quotient, complex_number_1, complex_number_2);
}

// raises the complex number by the power and stores it in "result"
void complex_pow(complex_number_t *result, complex_number_t complex_number, double power)
{
    complex_num_rev_init(result, pow(complex_number.modulus, power), complex_number.angle * power);
}

// stores the inverse of the passed in complex number to "inverse" complex number
void complex_inverse(complex_number_t *inverse, complex_number_t complex_number)
{
    complex_pow(inverse, complex_number, -1);
}

// stores the conjugate of the passed in complex number to "conjugate" complex number
void complex_conjugate(complex_number_t *conjugate, complex_number_t complex_number)
{
    complex_num_init(conjugate, complex_number.real, -complex_number.imaginary);
}
