#ifndef SINUSOIDS_H 
#define SINUSOIDS_H 

#include <stdlib.h> // sinusoids need to be allocated to the heap due to unknown size 
#include "complex.h" // we are dealing with complex sinusoids

// represents a complex, discrete sinusoid 
typedef struct 
{
    double amplitude;
    double ang_freq;
    double phase;
    int num_samples;
    complex_number_t *samples;
}
sinusoid_t;

// constructing / free'ing / reading sinusoids
sinusoid_t *construct_sinusoid(double amplitude, double ang_freq, double phase, int num_samples);
int sinusoid_free(sinusoid_t *sinusoid);
sinusoid_t *read_sinusoid(FILE *file, int num_samples);

#endif
