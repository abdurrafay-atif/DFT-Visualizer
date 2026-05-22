#include "../include/src/complex.h"

// scales the complex number by the passed in scaling factor
// scaled complex number stored in the first parameter (can be the same struct)
int complex_scale(complex_number_t *scale, complex_number_t cn, double scaling_factor)
{
    // error-checking
    if(scale == NULL)
    {
        return 1;
    }
    complex_num_init(scale, 
        cn.real * scaling_factor, 
        cn.imaginary * scaling_factor);
    return 0;
}

// adds the two complex numbers and stores it in the "sum" complex number
int complex_add(complex_number_t *sum, complex_number_t cn1, complex_number_t cn2)
{
    // error-checking
    if(sum == NULL)
    {
        return 1;
    }
    complex_num_init(sum, 
        cn1.real + cn2.real, 
        cn1.imaginary + cn2.imaginary);
    return 0;
}

// subtracts the second complex number from the first complex number, stores it in the "diff" complex number
int complex_sub(complex_number_t *diff, complex_number_t cn1, complex_number_t cn2)
{
    // error-checking
    if(diff == NULL)
    {
        return 1;
    }
    complex_num_init(diff, 
        cn1.real - cn2.real, 
        cn1.imaginary - cn2.imaginary);
    return 0;
}

// multiplies the two passed in complex numbers, stored in "product" complex number
int complex_prod(complex_number_t *product, complex_number_t cn1, complex_number_t cn2)
{
    // error-checking
    if(product == NULL)
    {
        return 1;
    }
    complex_num_rev_init(product, 
        cn1.modulus * cn2.modulus, 
        cn1.angle + cn2.angle);
    return 0;
}

// divides the first complex number by the second one, stores it in the "quotient" complex number
int complex_div(complex_number_t *quotient, complex_number_t cn1, complex_number_t cn2)
{
    // error-checking
    if(quotient == NULL)
    {
        return 1;
    }
    // need to obtain inverse of cn2 to divide
    complex_inv(&cn2, cn2);
    // use multiplication function with inverse
    complex_prod(quotient, cn1, cn2);
    return 0;
}

// raises the complex number by the power and stores it in "result"
int complex_pow(complex_number_t *result, complex_number_t cn, double power)
{
    // error-checking
    if(result == NULL)
    {
        return 1;
    }
    complex_num_rev_init(result, pow(cn.modulus, power), cn.angle * power);
    return 0;
}

// stores the inverse of the passed in complex number to "inverse" complex number
int complex_inv(complex_number_t *inverse, complex_number_t cn)
{
    // error-checking
    if(inverse == NULL)
    {
        return 1;
    }
    complex_pow(inverse, cn, -1);
    return 0;
}

// stores the conjugate of the passed in complex number to "conjugate" complex number
int complex_conj(complex_number_t *conjugate, complex_number_t cn)
{
    // error-checking
    if(conjugate == NULL)
    {
        return 1;
    }
    complex_num_init(conjugate, cn.real, -cn.imaginary);
    return 0;
}
