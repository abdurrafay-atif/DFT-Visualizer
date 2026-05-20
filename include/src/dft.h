#ifndef DFT_H
#define DFT_H

#include "sinusoids.h"
#include "matrix.h"
#include "vector.h"

// standard DFT
cvector_t *dft(cvector_t input);
cvector_t *dft(cvector_t input, int zero_pad);
cvector_t *idft(cvector_t input);

// fast fourier transform
cvector_t *fft(cvector_t input);
cvector_t *fft(cvector_t input, int zero_pad);
cvector_t *ifft(cvector_t input);

#endif