#ifndef APP_H
#define APP_H

#include "src/dft.h"

// note: default format is RECT

// reading vector from file
int extract_complex_num_from_file(FILE *file, complex_number_t *cn, int format);
int count_lines(FILE *file);
cvector_t *read_cvector_from_file(char *filename, int format); 

// plotting vectors (either time-domain or frequency-domain)
double cvector_max(cvector_t *v); // for determining height of plot
int plot_cvector(cvector_t *v); 

// writing vectors to files
int write_cvector_to_file(cvector_t *v, char *filename, int format);

// helper functions for commands
void print_help(FILE *file);

#endif