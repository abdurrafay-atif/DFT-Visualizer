#ifndef APP_H
#define APP_H

#include "src/dft.h"

// main functions
cvector_t *read_vector_from_file(char *filename);
int plot_vector(cvector_t *v); // plots magnitude spectrum
int write_vector_to_file(cvector_t *v, char *filename);

// helper functions
double cvector_max(cvector_t *v);

#endif