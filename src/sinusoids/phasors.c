#include "../include/src/sinusoids.h"

// converts the given complex number to a sinusoid
// angular frequency & # of samples required for construction
sinusoid_t *construct_sinusoid_from_complex_number
    (complex_number_t complex_number, double ang_freq, int num_samples)
{
    return construct_sinusoid(complex_number.modulus, ang_freq, complex_number.angle, num_samples);
}

// uses the amplitude & phase of the sinusoid to convert it to a complex number (its phasor)
// does not return the angular frequency
int convert_sinusoid_to_complex_number(complex_number_t *complex_number, sinusoid_t sinusoid)
{
    return complex_num_rev_init(complex_number, sinusoid.amplitude, sinusoid.phase);
}

// adds the two passed in sinusoids via phasors
sinusoid_t *add_sinusoids(sinusoid_t sinusoid_1, sinusoid_t sinusoid_2)
{
    // cannot add sinusoids with differing frequencies or # of samples
    if(sinusoid_1.ang_freq != sinusoid_2.ang_freq || sinusoid_1.num_samples != sinusoid_2.num_samples)
    {
        return NULL;
    }
    complex_number_t cn1;
    complex_number_t cn2;
    complex_number_t phasor_sum;
    convert_sinusoid_to_complex_number(&cn1, sinusoid_1);
    convert_sinusoid_to_complex_number(&cn2, sinusoid_2);
    complex_add(&phasor_sum, cn1, cn2);
    sinusoid_t *sum = construct_sinusoid_from_complex_number(phasor_sum, sinusoid_1.ang_freq, sinusoid_1.num_samples);
    return sum;
}