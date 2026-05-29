#include "../include/src/complex.h"

// NOTE: print functions do not add '\n', must be added manually
// NOTE: file for output must be specified for each function

// prints the complex number in this form: "a + j*(b)"
int complex_write_rect(FILE *file, complex_number_t cn)
{
    // handle invalid input
    if(file == NULL)
    {
        return 1;
    }
    // print output to the specified file
    fprintf(file, "%.2lf + j*(%.2lf)", cn.real, cn.imaginary);
    return 0;
}

// prints the complex number in this form: "|z|∠z"
int complex_write_polar(FILE *file, complex_number_t cn)
{
    // handle invalid input
    if(file == NULL)
    {
        return 1;
    }
    // print output to the specified file
    fprintf(file, "|%.2lf|∠%.2lf", cn.modulus, cn.angle);
    return 0;
}

// prints the complex number in this form: "z*e^(j*∠z)"
// angle in radians here
int complex_write_exp(FILE *file, complex_number_t cn)
{
    // handle invalid input
    if(file == NULL)
    {
        return 1;
    }
    // print output to the specified file
    fprintf(file, "%.2lf*e^(j*(%.2lf))", cn.modulus, cn.angle);
    return 0;
}

// prints the complex number in the specified format
// note: by default it prints in rectangular form
int complex_write(FILE *file, complex_number_t cn, int format)
{
    switch(format)
    {
        case RECT:  return complex_write_rect(file, cn);
        case POLAR: return complex_write_polar(file, cn);
        case EXP:   return complex_write_exp(file, cn);
        default:    return complex_write_rect(file, cn);
    }
    return 0;
}