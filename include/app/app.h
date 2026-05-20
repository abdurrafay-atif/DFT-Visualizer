#ifndef APP_H
#define APP_H

#include "dft.h"

// main functions
cvector_t *read_vector_from_file(char *filename);
int plot_dft(cvector_t *dft); // plots magnitude spectrum
int write_vector_to_file(cvector_t *v, char *filename);

// helper functions
double cvec_max(cvector_t *v);

#endif