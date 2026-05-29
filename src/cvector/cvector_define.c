#include "../include/src/cvector.h"

// initializes vector based on an array of complex numbers
cvector_t *cvector_init(complex_number_t *cn, int size)
{
    // handle invalid input
    if(cn == NULL || size < 0)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *v = malloc(sizeof(cvector_t));
    v->vec = malloc(sizeof(complex_number_t) * size);
    // set fields
    v->size = size;
    for(int ele = 0; ele < size; ele++)
    {
        cvector_place(v, ele, cn[ele].real, cn[ele].imaginary);
    }
    return v;
}

// returns an empty vector of the given size
cvector_t *cvector_init_empty(int size)
{
    // handle invalid input
    if(size <= 0)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *v = malloc(sizeof(cvector_t));
    v->vec = malloc(sizeof(complex_number_t) * size);
    // set fields
    v->size = size;
    for(int ele = 0; ele < size; ele++)
    {
        complex_num_init(&v->vec[ele], 0, 0);
    }
    return v;
}

// free()'s all malloc()'d material in the cvector_t struct
int cvector_free(cvector_t *v)
{  
    // handle invalid input
    if(v == NULL)
    {
        return 1;
    }
    free(v->vec);
    free(v);
    return 0;
}
