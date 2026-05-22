#include "../include/src/cvector.h"

// initializes vector based on an array of complex numbers
cvector_t *cvector_init(complex_number_t *cn, int size)
{
    // error-checking
    if(cn == NULL)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *vec = malloc(sizeof(cvector_t));
    vec->vec = malloc(sizeof(complex_number_t) * size);
    // set fields
    vec->size = size;
    for(int ele = 0; ele < size; ele++)
    {
        complex_num_init(&vec->vec[ele], cn[ele].real, cn[ele].imaginary);
    }
    return vec;
}

// returns an empty vector of the given size
cvector_t *cvector_init_empty(int size)
{
    // allocate a new vector
    cvector_t *vec = malloc(sizeof(cvector_t));
    vec->vec = malloc(sizeof(complex_number_t) * size);
    // set fields
    vec->size = size;
    for(int ele = 0; ele < size; ele++)
    {
        complex_num_init(&vec->vec[ele], 0, 0);
    }
    return vec;
}

// free()'s all malloc()'d material in the cvector_t struct
int cvector_free(cvector_t *v)
{  
    // error-checking
    if(v == NULL)
    {
        return 1;
    }
    free(v->vec);
    free(v);
    return 0;
}

// prints the passed in vector in [] format
// complex number printing done as specified by format
void cvector_print(cvector_t v, FILE *file, int format)
{
    fprintf(file, "Size: %d\n", v.size);
    fprintf(file, "Vector: [    ");
    for(int ele = 0; ele < v.size; ele++)
    {
        complex_print(v.vec[ele], file, format);
        fprintf(file, "    ");
    }
    fprintf(file, "]\n");
}


