#ifndef DFT_H
#define DFT_H

#include "sinusoids.h"
#include "cvector.h"

// functions for DFT / IDFT
cvector_t *dft(cvector_t input);
cvector_t *dft_zero_pad(cvector_t input, int zero_pad);
cvector_t *idft(cvector_t dft);

#endif