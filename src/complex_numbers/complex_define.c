// this file consists of functions for defining complex numbers
#include "../include/src/complex.h"

// defines the complex number struct based on rectangular form
// this function fills in the "modulus" & "angle" fields through the following formulas:
// |z| = sqrt(real^2 + imaginary^2)
// ∠z = arctan(imaginary / real) (radians)
// Note that if the real part is negative, PI is added to the angle (done with the atan2() function)
// The angle is always defined within 0 to 2 * PI; another function should be used to re-calibrate to -pi to pi
int complex_num_init(complex_number_t *cn, double real, double imaginary)
{
    // handling invalid input
    if(cn == NULL)
    {
        return 1;
    }
    // set fields for parameters
    cn->real = real;
    cn->imaginary = imaginary;
    // calculate & set the modulus
    cn->modulus = sqrt(pow(real, 2) + pow(imaginary, 2));
    // calculate, set, & re-calibrate the angle (atan2() performs addition of PI when necessary)
    cn->angle = normalize_angle(atan2(imaginary, real));
    return 0;
}

// defines the complex number struct based on polar form
// fills "real" & "imaginary" fields based on passed in parameters
// real = modulus*cos(angle)
// imaginary = modulus*sine(angle)
// note: if negative modulus given, function returns error value
int complex_num_rev_init(complex_number_t *cn, double modulus, double angle)
{
    // handling invalid input
    if(cn == NULL || modulus < 0)
    {
        return 1;
    }
    // re-calibrate angle (in case user input is out-of-bounds)
    angle = normalize_angle(angle);
    // set the fields accordingly
    cn->real = modulus * cos(angle);
    cn->imaginary = modulus * sin(angle);
    cn->modulus = modulus;
    cn->angle = angle;
    return 0;
}

// sets the complex number to (0, 0)
// this is a helper function for setting complex numbers in larger data structures
int complex_num_empty(complex_number_t *cn)
{
    // handling invalid input
    if(cn == NULL)
    {
        return 1;
    }
    // set all fields to 0 (complex number at origin)
    cn->real = 0;
    cn->imaginary = 0;
    cn->modulus = 0;
    cn->angle = 0;
    return 0;
}

// places the passed in angle in the range [0, 2*M_PI) (2*M_PI is excluded)
double normalize_angle(double angle)
{
    // determine if angle is out of range 0 to 2 * PI, recalibrate if so
    while(angle < 0 || angle >= (2 * M_PI))
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
