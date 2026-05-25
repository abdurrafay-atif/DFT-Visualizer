#include "../include/src/complex.h"

// NOTE: print functions do not add '\n', must be added manually
// NOTE: file for output must be specified for each function

// prints the complex number in this form: "a + j*(b)"
int complex_print_rect(complex_number_t cn, FILE *file)
{
    // handling invalid input
    if(file == NULL)
    {
        return 1;
    }
    fprintf(file, "%.2lf + j*(%.2lf)", cn.real, cn.imaginary);
    return 0;
}

// prints the complex number in this form: "|z|∠z"
// converts the angle to degrees
int complex_print_polar(complex_number_t cn, FILE *file)
{
    // handling invalid input
    if(file == NULL)
    {
        return 1;
    }
    fprintf(file, "|%.2lf|∠%.2lf°", cn.modulus, cn.angle * 180 / M_PI);
    return 0;
}

// prints the complex number in this form: "z*e^(j*∠z)"
// angle in radians here
int complex_print_exp(complex_number_t cn, FILE *file)
{
    // handling invalid input
    if(file == NULL)
    {
        return 1;
    }
    fprintf(file, "%.2lf*e^(j*(%.2lf))", cn.modulus, cn.angle);
    return 0;
}

// prints the complex number in a specified format
// note: by default it prints in rectangular form
int complex_print(complex_number_t cn, FILE *file, int format)
{
    switch(format)
    {
        case RECT:  return complex_print_rect(cn, file);
        case POLAR: return complex_print_polar(cn, file);
        case EXP:   return complex_print_exp(cn, file);
        default:    return complex_print_rect(cn, file);
    }
    return 0;
}