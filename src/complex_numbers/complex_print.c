#include "../include/src/complex.h"

// NOTE: print functions do not add '\n', must be added manually
// NOTE: file for output must be specified for each function

// prints the complex number in this form: "a + j*(b)"
void complex_print_rect(complex_number_t cn, FILE *file)
{
    fprintf(file, "%.2lf + j*(%.2lf)", cn.real, cn.imaginary);
}

// prints the complex number in this form: "|z|∠z"
// converts the angle to degrees
void complex_print_polar(complex_number_t cn, FILE *file)
{
    fprintf(file, "|%.2lf|∠%.2lf°", cn.modulus, cn.angle * 180 / M_PI);
}

// prints the complex number in this form: "z*e^(j*∠z)"
// angle in radians here
void complex_print_exp(complex_number_t cn, FILE *file)
{
    fprintf(file, "%.2lf*e^(j*(%.2lf))", cn.modulus, cn.angle);
}

// prints the complex number in a specified format
// note by default it prints in rectangular form
void complex_print(complex_number_t cn, FILE *file, int format)
{
    switch(format)
    {
        case RECT: 
            complex_print_rect(cn, file);
            break;
        case POLAR: 
            complex_print_polar(cn, file);
            break;
        case EXP: 
            complex_print_exp(cn, file);
            break;
        default: complex_print_rect(cn, file);
            break;
    }
}