#ifndef DFT_H
#define DFT_H

#include "sinusoids.h"
#include "cmatrix.h"
#include "cvector.h"

cvector_t *dft(cvector_t input);
cvector_t *dft_zero_pad(cvector_t input, int zero_pad);
cvector_t *idft(cvector_t dft);
cvector_t *circ_convolve(cvector_t v1, cvector_t v2);

#endif