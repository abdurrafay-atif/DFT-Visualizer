#include "../include/src/cvector.h"

// sums all the elements in the given vector
// the result is a complex number
int cvector_sum(complex_number_t *cn, cvector_t v)
{
    // error-checking
    if(cn == NULL)
    {
        return 1;
    }
    // empty out the complex number
    complex_num_empty(cn);
    // loop through each element, use the complex_add function to perform summing
    for(int ele = 0; ele < v.size; ele++)
    {
        complex_add(cn, *cn, v.vec[ele]);
    }
    return 0;
}

// computes the dot product of the two vectors
// the result is a complex number
int cvector_dot_product(complex_number_t *cn, cvector_t v1, cvector_t v2)
{
    // error-handling
    if(cn == NULL || v1.size != v2.size)
    {
        return 1;
    }
    // obtain conjugate of v1
    cvector_t *conj = cvector_conj(v1);
    // calculate dot product (first find element product, then sum all elements)
    cvector_t *ele_prod = cvector_element_prod(*conj, v2);
    cvector_sum(cn, *ele_prod);
    // conj was malloc()'ed so must be free()'d
    cvector_free(conj);
    cvector_free(ele_prod);
    return 0;
}