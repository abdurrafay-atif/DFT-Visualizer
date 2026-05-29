#include "../include/src/cvector.h"

// places a complex number at the specified index in the vector via cartesian coordinates
int cvector_place(cvector_t *v, int index, double real, double imaginary)
{
    // error-handling
    if(v == NULL || index < 0 || index >= v->size)
    {
        return 1;
    }
    complex_num_init(&v->vec[index], real, imaginary);
    return 0;
}

// places a complex number at the specified index in the vector via polar coordinates
int cvector_rev_place(cvector_t *v, int index, double modulus, double angle)
{
    // error-handling
    if(v == NULL || index < 0 || index >= v->size)
    {
        return 1;
    }
    complex_num_rev_init(&v->vec[index], modulus, angle);
    return 0;
}

// applies the complex conjugate onto each element of 'v,' stores into a new vector
cvector_t *cvector_conj(cvector_t v)
{
    // initialize the conjugate vector
    cvector_t *conj = cvector_init_empty(v.size);
    // apply conjugate to each element
    for(int ele = 0; ele < conj->size; ele ++)
    {
        cvector_place(conj, ele, v.vec[ele].real, -v.vec[ele].imaginary);
    }
    return conj;
}

// multiplies each element of the vector by the scaling factor (a complex number)
cvector_t *cvector_scale(cvector_t v, complex_number_t scale)
{
    // allocate a new vector
    cvector_t *res = cvector_init_empty(v.size);
    // perform scaling
    for(int ele = 0; ele < res->size; ele++)
    {
        complex_prod(&res->vec[ele], v.vec[ele], scale);
    }
    return res;
}

// adds the elements of the two vectors together to form a new vector, element-by-element
cvector_t *cvector_add(cvector_t v1, cvector_t v2)
{
    // error-handling
    if(v1.size != v2.size)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *res = cvector_init_empty(v1.size);
    // perform addition element-by-element
    for(int ele = 0; ele < res->size; ele++)
    {
        complex_add(&res->vec[ele], v1.vec[ele], v2.vec[ele]);
    }
    return res;
}

// multiplies the elements of the two vectors together to form a new vector, element-by-element
cvector_t *cvector_element_product(cvector_t v1, cvector_t v2)
{
    // error-handling
    if(v1.size != v2.size)
    {
        return NULL;
    }
    // allocate a new vector
    cvector_t *res = cvector_init_empty(v1.size);
    // perform element by element product operation
    for(int ele = 0; ele < res->size; ele++)
    {
        complex_prod(&res->vec[ele], v1.vec[ele], v2.vec[ele]);
    }
    return res;
}