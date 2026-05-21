#include "../include/src/vector.h"

// multiplies each element of the vector by the scaling factor (a complex number)
cvector_t *cvec_scale(cvector_t v, complex_number_t scale)
{
    // allocate a new vector
    cvector_t *res = cvec_init_empty(v.size);
    // perform scaling
    for(int ele = 0; ele < res->size; ele++)
    {
        complex_multiply(&res->vec[ele], v.vec[ele], scale);
    }
    return res;
}

// adds the elements of the two vectors together to form a new vector, element-by-element
cvector_t *cvec_add(cvector_t v1, cvector_t v2)
{
    // error-handling
    if(v1.size != v2.size)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *res = cvec_init_empty(v1.size);
    // perform addition element-by-element
    for(int ele = 0; ele < res->size; ele++)
    {
        complex_add(&res->vec[ele], v1.vec[ele], v2.vec[ele]);
    }
    return res;
}

// multiplies the elements of the two vectors together to form a new vector, element-by-element
cvector_t *cvec_element_prod(cvector_t v1, cvector_t v2)
{
    // error-handling
    if(v1.size != v2.size)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *res = cvec_init_empty(v1.size);
    // perform element by element product operation
    for(int ele = 0; ele < res->size; ele++)
    {
        complex_multiply(&res->vec[ele], v1.vec[ele], v2.vec[ele]);
    }
    return res;
}