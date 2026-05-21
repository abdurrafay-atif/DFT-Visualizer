#include "../include/src/vector.h"

// initializes vector based on an array of complex numbers
cvector_t *cvec_init(complex_number_t *cn, int size)
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
    vec->vec = cn;
    vec->size = size;
    return vec;
}

// returns an empty vector of the given size
cvector_t *cvec_init_empty(int size)
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

// applies the complex conjugate onto each element of 'v,' stores into a new vector
cvector_t *cvec_conj(cvector_t v)
{
    // initialize the conjugate vector
    cvector_t *conj = cvec_init(v.vec, v.size);
    // apply conjugate to each element
    for(int ele = 0; ele < conj->size; ele ++)
    {
        complex_conjugate(&conj->vec[ele], conj->vec[ele]);
    }
    return conj;
}

// free()'s all malloc()'d material in the cvector_t struct
int cvec_free(cvector_t *v)
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
void cvec_print(cvector_t v, int format)
{
    printf("Size: %d\n", v.size);
    printf("Vector: [    ");
    for(int ele = 0; ele < v.size; ele++)
    {
        complex_print(v.vec[ele], format);
        printf("    ");
    }
    printf("]\n");
}


