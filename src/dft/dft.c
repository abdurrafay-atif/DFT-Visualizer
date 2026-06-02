#include "../include/src/dft.h"

// applies the DFT to the given vector (brings it from time domain to frequency domain)
cvector_t *dft(cvector_t input)
{
    // generate a new, empty vector to place DFT coefficients
    cvector_t *dft = cvector_init_empty(input.size);
    // DFT algorithm: loop through all fourier sinusoids, take dot product of it & input vector
    for(int index = 0; index < input.size; index++)
    {
        sinusoid_t *fourier_sinusoid = construct_sinusoid(1, (2 * M_PI * index) / input.size, 0, input.size);
        cvector_t *sinusoid_vector = cvector_init(fourier_sinusoid->samples, fourier_sinusoid->num_samples);
        cvector_dot_product(&dft->vec[index], *sinusoid_vector, input);
        sinusoid_free(fourier_sinusoid);
        cvector_free(sinusoid_vector);
    }
    return dft;
}

// applies the DFT to the given vector with a zero-pad
// adds the given # of zeros to the end
cvector_t *dft_zero_pad(cvector_t input, int zero_pad)
{
    // create a new vector which consists of the input vector + "zero-pad" # of zeros
    cvector_t *padded_input = cvector_append_zeros(input, zero_pad);
    // check that the vector is non-NULL
    if(padded_input == NULL)
    {
        return NULL;
    }
    // apply the DFT to this new, zero-padded vector
    cvector_t *freq = dft(*padded_input);
    cvector_free(padded_input);
    return freq;
}

// applies the Inverse DFT (takes a vector from frequency domain to time domain)
cvector_t *idft(cvector_t input)
{
    // scale the input by 1 / input.size as part of IDFT procedure
    complex_number_t scale;
    complex_num_init(&scale, 1.0 / input.size, 0);
    cvector_t *scaled_input = cvector_scale(input, scale);
    // generate a new, empty vector to place time domain coefficients
    cvector_t *idft = cvector_init_empty(input.size);
    // IDFT algorithm: loop through each coefficient
    // scale fourier sinusoid by corresponding DFT coefficient * 1 / input.size
    // sum all vectors
    for(int coeff = 0; coeff < input.size; coeff++)
    {
        sinusoid_t *fourier_sinusoid = construct_sinusoid(1, (2 * M_PI * coeff) / input.size, 0, input.size);
        cvector_t *sinusoid_vector = cvector_init(fourier_sinusoid->samples, fourier_sinusoid->num_samples);
        cvector_t *scaled_sinusoid_vector = cvector_scale(*sinusoid_vector, scaled_input->vec[coeff]);
        // add to the IDFT
        for(int index = 0; index < idft->size; index++)
        {
            complex_add(&idft->vec[index], idft->vec[index], scaled_sinusoid_vector->vec[index]);
        }
        sinusoid_free(fourier_sinusoid);
        cvector_free(sinusoid_vector);
        cvector_free(scaled_sinusoid_vector);
    }
    cvector_free(scaled_input);
    return idft;
}