#ifndef SINUSOIDS_H 
#define SINUSOIDS_H 

#include <stdlib.h> // sinusoids need to be allocated to the heap due to unknown size 
#include "complex.h" // we are dealing with complex sinusoids

// represents a discrete sinusoid 
typedef struct 
{
    double amplitude;
    double ang_freq;
    double phase;
    int num_samples;
    complex_number_t *samples;
}
sinusoid_t;

// constructing / free'ing / printing sinusoids
sinusoid_t *construct_sinusoid(double amplitude, double ang_freq, double phase, int num_samples);
int sinusoid_free(sinusoid_t *sinusoid);
void print_sinusoid_as_cosine(sinusoid_t sinusoid, FILE *file);

// phasors
sinusoid_t *construct_sinusoid_from_complex_number
    (complex_number_t complex_number, double ang_freq, int num_samples);
int convert_sinusoid_to_complex_number(complex_number_t *complex_number, sinusoid_t sinusoid);
sinusoid_t *add_sinusoids(sinusoid_t sinusoid_1, sinusoid_t sinusoid_2);

#endif
