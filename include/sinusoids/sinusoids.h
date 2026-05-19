#include <stdio.h>
#include <stdlib.h>
#include "../complex_numbers/complex.h"

typedef struct 
{
    double amplitude;
    double ang_freq;
    double phase;
    int num_samples;
    complex_number_t *samples;
}
sinusoid_t;

// constructing / free'ing sinusoids
sinusoid_t *construct_sinusoid(double amplitude, double ang_freq, double phase, int num_samples);
sinusoid_t *construct_sinusoid_from_complex_number
    (complex_number_t complex_number, double ang_freq, int num_samples);
void sinusoid_free(sinusoid_t *sinusoid);

// printing sinusoids
void print_sinusoid_vector(sinusoid_t sinusoid, int format);
void print_full_sinusoid(sinusoid_t sinusoid, int format);

// phasors
void convert_sinusoid_to_complex_number(complex_number_t *complex_number, sinusoid_t sinusoid);
sinusoid_t *add_sinusoids(sinusoid_t sinusoid_1, sinusoid_t sinusoid_2);
