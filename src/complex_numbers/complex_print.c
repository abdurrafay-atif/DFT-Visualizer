#include "../include/src/complex.h"

// NOTE: print functions do not add '\n', must be added manually

// prints the complex number in this form: "a +j*(b)"
void complex_print_rect(complex_number_t complex_number)
{
    printf("%lf + j*(%lf)", complex_number.real, complex_number.imaginary);
}

// prints the complex number in this form: "|z|∠z"
// converts the angle to degrees
void complex_print_polar(complex_number_t complex_number)
{
    printf("|%lf|∠%lf°", complex_number.modulus, complex_number.angle * 180 / M_PI);
}

// prints the complex number in this form: "z*e^(j*∠z)"
// angle in radians here
void complex_print_exponential(complex_number_t complex_number)
{
    printf("%lf*e^(j*(%lf))", complex_number.modulus, complex_number.angle);
}

// prints the complex number in a specified format
// note by default it prints in rectangular form
void complex_print(complex_number_t complex_number, int format)
{
    switch(format)
    {
        case RECT: complex_print_rect(complex_number);
        case POLAR: complex_print_polar(complex_number);
        case EXP: complex_print_exponential(complex_number);
        default: complex_print_rect(complex_number);
    }
}

// prints all 3 forms of the complex number (basically just calls the first 3 functions)
void complex_print_all_forms(complex_number_t complex_number)
{
    printf("Rectangular Form: ");
    complex_print_rect(complex_number);
    printf("\nPolar Form: ");
    complex_print_polar(complex_number);
    printf("\nExponential Form: ");
    complex_print_exponential(complex_number);
    printf("\n");
}