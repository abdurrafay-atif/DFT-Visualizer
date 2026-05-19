#include "../include/sinusoids/sinusoids.h"

// uses the amplitude & phase of the sinusoid to convert it to a complex number (its phasor)
// does not return the angular frequency
void convert_sinusoid_to_complex_number(complex_number_t *complex_number, sinusoid_t sinusoid)
{
    complex_num_rev_init(complex_number, sinusoid.amplitude, sinusoid.phase);
}

// adds the two passed in sinusoids via phasors
sinusoid_t *add_sinusoids(sinusoid_t sinusoid_1, sinusoid_t sinusoid_2)
{
    // cannot add sinusoids with differing frequencies or # of samples
    if(sinusoid_1.ang_freq != sinusoid_2.ang_freq || sinusoid_1.num_samples != sinusoid_2.num_samples)
    {
        return NULL;
    }
    complex_number_t complex_number_1;
    complex_number_t complex_number_2;
    complex_number_t phasor_sum;
    convert_sinusoid_to_complex_number(&complex_number_1, sinusoid_1);
    convert_sinusoid_to_complex_number(&complex_number_2, sinusoid_2);
    complex_add(&phasor_sum, complex_number_1, complex_number_2);
    sinusoid_t *sum = construct_sinusoid_from_complex_number(phasor_sum, sinusoid_1.ang_freq, sinusoid_1.num_samples);
    return sum;
}