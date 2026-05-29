#include "../include/src/cvector.h"

// THIS FILE CONSISTS OF FUNCTIONS FOR CALCULATING CERTAIN QUANTITIES IN COMPLEX VECTORS

// obtains the maximum element (modulus) of the given vector
double cvector_max(cvector_t v)
{
    double max = -INFINITY;
    for(int ele = 0; ele < v.size; ele++)
    {
        double curr = v.vec[ele].modulus;
        if(curr > max)
        {
            max = curr;
        }
    }
    return max;
}

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
    cvector_t *ele_prod = cvector_element_product(*conj, v2);
    cvector_sum(cn, *ele_prod);
    // free() material malloc()'d in this function
    cvector_free(conj);
    cvector_free(ele_prod);
    return 0;
}