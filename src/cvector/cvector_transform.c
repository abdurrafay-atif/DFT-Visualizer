#include "../include/src/cvector.h"

// performs the circular reversal operation on the passed in vector
cvector_t *cvector_circ_reverse(cvector_t v)
{
    // allocate a new vector
    cvector_t *reverse = cvector_init(v.vec, v.size);
    // calculate circularly reversed vector
    // involves switching each k & size - k - 1 element
    for(int ele = 1; ele <= (reverse->size) / 2; ele++)
    {
        reverse->vec[ele] = v.vec[reverse->size - ele];
        reverse->vec[reverse->size - ele] = v.vec[ele];
    }
    return reverse;
}

// performs the circular shift operation on the passed in vector
cvector_t *cvector_circ_shift(cvector_t v, int shift)
{
    // take modulus of shift with the length of the vector (following accounts for negative shifts)
    shift = ((shift % v.size) + v.size) % v.size;
    // allocate a new vector
    cvector_t *shifted = cvector_init(v.vec, v.size);
    // perform shifting (via modulus)
    for(int ele = 0; ele < shifted->size; ele++)
    {
        shifted->vec[(ele + shift) % shifted->size] = v.vec[ele];
    }
    return shifted;
}

// applies fourier modulation on the passed in vector with the specified fourier sinusoid
cvector_t *cvector_fourier_modulate(cvector_t v, int index)
{
    // form specified sinusoid, convert the sample vector to a complex_vector_t
    sinusoid_t *fourier_sinusoid = construct_sinusoid(1, (2 * M_PI * index) / v.size, 0, v.size);
    cvector_t *sinusoid_vec = cvector_init(fourier_sinusoid->samples, fourier_sinusoid->num_samples);
    // perform element-by-element product
    cvector_t *modulation = cvector_element_product(v, *sinusoid_vec);
    // free malloc()'d material
    sinusoid_free(fourier_sinusoid);
    cvector_free(sinusoid_vec);
    return modulation;
}