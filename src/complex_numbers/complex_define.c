// this file consists of functions for defining complex numbers
#include "../include/src/complex.h"

// defines the complex number struct based on rectangular form
// this function fills in the "modulus" & "angle" fields through the following formulas:
// |z| = sqrt(real^2 + imaginary^2)
// ∠z = arctan(imaginary / real) (radians)
// Note that if the real part is negative, PI is added to the angle
// The angle is always defined within 0 to 2 * PI; another function should be used to re-calibrate to -pi to pi
int complex_num_init(complex_number_t *complex_number, double real, double imaginary)
{
    // error-handling
    if(complex_number == NULL)
    {
        return 1;
    }
    // set fields for parameters
    complex_number->real = real;
    complex_number->imaginary = imaginary;
    // calculate & set the modulus
    complex_number->modulus = sqrt(pow(real, 2) + pow(imaginary, 2));
    // calculate & set the angle (atan2() performs addition of PI when necessary)
    complex_number->angle = atan2(imaginary, real);
    // re-calibrate angle
    complex_number->angle = normalize_angle(complex_number->angle);
    return 0;
}

// defines the complex number struct based on polar form
// fills "real" & "imaginary" fields based on passed in parameters
// a = modulus*cos(angle)
// b = modulus*sine(angle)
// note: if negative modulus given, function returns error value
int complex_num_rev_init(complex_number_t *complex_number, double modulus, double angle)
{
    // error-handling
    if(complex_number == NULL || modulus < 0)
    {
        return 1;
    }
    // re-calibrate angle
    angle = normalize_angle(angle);
    // set the fields accordingly
    complex_number->real = modulus * cos(angle);
    complex_number->imaginary = modulus * sin(angle);
    complex_number->modulus = modulus;
    complex_number->angle = angle;
    return 0;
}

// sets the complex_number to (0, 0); helper function
int complex_num_empty(complex_number_t *complex_number)
{
    return complex_num_init(complex_number, 0, 0);
}

// places angle in 0 to 2*PI range
double normalize_angle(double angle)
{
    // determine if angle is out of range 0 to 2 * PI, recalibrate if so
    while(angle < 0 || angle >= 2 * M_PI)
    {
        // add to the angle if it is negative
        if(angle < 0)
        {
            angle = angle + 2 * M_PI;
        }
        // subtract from the angle if it is over 2 * PI
        if(angle >= 2 * M_PI)
        {
            angle = angle - 2 * M_PI;
        }
    }
    return angle;
}
