#include "../include/src/complex.h"

// scales the complex number by the passed in scaling factor
// scaled complex number stored in the first parameter (can be the same struct)
int complex_scale(complex_number_t *scale, complex_number_t cn, double scaling_factor)
{
    // handling invalid input
    if(scale == NULL)
    {
        return 1;
    }
    // set fields accordingly
    scale->real = cn.real * scaling_factor;
    scale->imaginary = cn.imaginary * scaling_factor;
    scale->modulus = cn.modulus * scaling_factor;
    scale->angle = cn.angle;
    return 0;
}

// adds the two complex numbers and stores it in the "sum" complex number
int complex_add(complex_number_t *sum, complex_number_t cn1, complex_number_t cn2)
{
    // handling invalid input
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
int complex_prod(complex_number_t *prod, complex_number_t cn1, complex_number_t cn2)
{
    // error-checking
    if(prod == NULL)
    {
        return 1;
    }
    complex_num_rev_init(prod, 
        cn1.modulus * cn2.modulus, 
        cn1.angle + cn2.angle);
    return 0;
}

// divides the first complex number by the second one, stores it in the "quotient" complex number
int complex_div(complex_number_t *quot, complex_number_t cn1, complex_number_t cn2)
{
    // error-checking
    if(quot == NULL)
    {
        return 1;
    }
    // need to obtain inverse of cn2 to divide
    complex_inv(&cn2, cn2);
    // use multiplication function with inverse
    complex_prod(quot, cn1, cn2);
    return 0;
}

// raises the complex number by the power and stores it in "result"
int complex_pow(complex_number_t *res, complex_number_t cn, double power)
{
    // error-checking
    if(res == NULL)
    {
        return 1;
    }
    complex_num_rev_init(res, pow(cn.modulus, power), cn.angle * power);
    return 0;
}

// stores the inverse of the passed in complex number to "inverse" complex number
int complex_inv(complex_number_t *inv, complex_number_t cn)
{
    // error-checking
    if(inv == NULL)
    {
        return 1;
    }
    complex_pow(inv, cn, -1);
    return 0;
}

// stores the conjugate of the passed in complex number to "conjugate" complex number
int complex_conj(complex_number_t *conj, complex_number_t cn)
{
    // error-checking
    if(conj == NULL)
    {
        return 1;
    }
    complex_num_init(conj, cn.real, -cn.imaginary);
    return 0;
}
