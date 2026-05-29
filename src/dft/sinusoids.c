#include "../include/src/sinusoids.h"

// constructs the sinusoid based on struct parameters
sinusoid_t *construct_sinusoid(double amplitude, double ang_freq, double phase, int num_samples)
{
    // handle invalid input
    if(amplitude < 0 || num_samples < 1)
    {
        return NULL;
    }
    // heap allocate a new sinusoid_t
    sinusoid_t *sinusoid = malloc(sizeof(sinusoid_t));
    // normalize angular frequency & phase
    ang_freq = normalize_angle(ang_freq);
    phase = normalize_angle(phase);
    // set parameters
    sinusoid->amplitude = amplitude;
    sinusoid->ang_freq = ang_freq;
    sinusoid->phase = phase;
    sinusoid->num_samples = num_samples;
    sinusoid->samples = malloc(sizeof(complex_number_t) * num_samples);
    // set all samples
    for(int sample = 0; sample < num_samples; sample++)
    {
        complex_num_rev_init(&sinusoid->samples[sample], amplitude, ang_freq * sample + phase);
    }
    return sinusoid;
}

// free's all malloc'd material in the sinusoid_t struct
int sinusoid_free(sinusoid_t *sinusoid)
{
    // handle invalid input
    if(sinusoid == NULL)
    {
        return 1;
    }
    // free heap-allocated material
    free(sinusoid->samples);
    free(sinusoid);
    return 0;
}

// reads the sinusoid in this form: A*cos((w)*n + phi)
sinusoid_t *read_sinusoid(FILE *file, int num_samples)
{
    // handle invalid input
    if(file == NULL || num_samples < 1)
    {
        return NULL;
    }
    // obtain sinusoid parameters from file
    double amplitude, ang_freq, phase;
    int ret = fscanf(file, "%lf*cos((%lf)*n + %lf)", &amplitude, &ang_freq, &phase);
    // check that fscanf() obtained each parameter
    if(ret != 3)
    {
        return NULL; 
    }
    // construct sinusoid from the parameters obtained
    return construct_sinusoid(amplitude, ang_freq, phase, num_samples);
}