#include "../include/src/sinusoids.h"

// constructs the sinusoid based on struct parameters
sinusoid_t *construct_sinusoid(double amplitude, double ang_freq, double phase, int num_samples)
{
    // error-handling
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

// converts the given complex number to a sinusoid
// angular frequency & # of samples required for construction
sinusoid_t *construct_sinusoid_from_complex_number
    (complex_number_t complex_number, double ang_freq, int num_samples)
{
    return construct_sinusoid(complex_number.modulus, ang_freq, complex_number.angle, num_samples);
}

// free's all malloc'd material in the sinusoid_t struct
int sinusoid_free(sinusoid_t *sinusoid)
{
    // error-handling
    if(sinusoid == NULL)
    {
        return 1;
    }
    // free heap-allocated material
    free(sinusoid->samples);
    free(sinusoid);
    return 0;
}

// prints only the sinusoid sample components of the sinusoid
void print_sinusoid_vector(sinusoid_t sinusoid, int format)
{
    printf("[");
    for(int sample = 0; sample < sinusoid.num_samples; sample++)
    {
        complex_print(sinusoid.samples[sample], format);
        printf(" ");
    }
    printf("]\n");
}

// prints all information about the passed in sinusoid
void print_full_sinusoid(sinusoid_t sinusoid, int format)
{
    printf("Amplitude: %lf\n", sinusoid.amplitude);
    printf("Angular Frequency: %lf\n", sinusoid.amplitude);
    printf("Phase: %lf\n", sinusoid.amplitude);
    printf("# of Samples: %lf\n", sinusoid.amplitude);
    printf("Sample Vector: ");
    print_sinusoid_vector(sinusoid, format);
}