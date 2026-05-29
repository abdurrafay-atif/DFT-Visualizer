#include "../include/src/complex.h"

// reads the complex number from the file in rectangular form
// uses the complex_num_init() function to initialize the complex number
int complex_read_rect(FILE *file, complex_number_t *cn)
{
    // handling invalid input
    if(file == NULL || cn == NULL)
    {
        return 1;
    }
    // obtain real & imaginary components of complex number from file
    double real, imaginary;
    int ret = fscanf(file, "%lf + j*(%lf)", &real, &imaginary);
    // check that fscanf() was able to obtain both components of the complex number
    if(ret != 2)
    {
        return -1; // special code indicating incorrect file format
    }
    // set the complex number
    complex_num_init(cn, real, imaginary);
    return 0;
}

// reads the complex number from the file in polar form
// uses the complex_num_rev_init() function to initialize the complex number
int complex_read_polar(FILE *file, complex_number_t *cn)
{
    // handle invalid input
    if(file == NULL || cn == NULL)
    {
        return 1;
    }
    // obtain modulus & angle components of complex number from file
    double modulus, angle;
    int ret = fscanf(file, "|%lf|∠%lf", &modulus, &angle);
    // check that fscanf() was able to obtain both components of the complex number
    if(ret != 2)
    {
        return -1; // special code indicating incorrect file format
    }
    // set the complex number
    complex_num_rev_init(cn, modulus, angle);
    return 0;
}

// reads the complex number from the file in exponential form
// uses the complex_num_rev_init() function to initialize the complex number
int complex_read_exp(FILE *file, complex_number_t *cn)
{
    // handle invalid input
    if(file == NULL || cn == NULL)
    {
        return 1;
    }
    // obtain modulus & angle components of complex number from file
    double modulus, angle;
    int ret = fscanf(file, "%lf*e^(j*(%lf))", &modulus, &angle);
    // check that fscanf() was able to obtain both components of the complex number
    if(ret != 2)
    {
        return -1; // special code indicating incorrect file format
    }
    // set the complex number
    complex_num_rev_init(cn, modulus, angle);
    return 0;
}

// reads the complex number in the specified format
// note: by default it reads in rectangular form
int complex_read(FILE *file, complex_number_t *cn, int format)
{
    switch(format)
    {
        case RECT:  return complex_read_rect(file, cn);
        case POLAR: return complex_read_polar(file, cn);
        case EXP:   return complex_read_exp(file, cn);
        default:    return complex_read_rect(file, cn);
    }
    return 0;
}