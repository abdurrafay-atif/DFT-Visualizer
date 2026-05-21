#include "../include/src/vector.h"

// sums all the elements in the given vector
// the result is a complex number
int cvec_sum(complex_number_t *cn, cvector_t v)
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
int cvec_dot_product(complex_number_t *cn, cvector_t v1, cvector_t v2)
{
    // error-handling
    if(cn == NULL || v1.size != v2.size)
    {
        return 1;
    }
    // obtain conjugate of v1
    cvector_t *conj = cvec_conj(v1);
    // calculate dot product (first find element product, then sum all elements)
    cvector_t *ele_prod = cvec_element_prod(*conj, v2);
    cvec_sum(cn, *ele_prod);
    // conj was malloc()'ed so must be free()'d
    cvec_free(conj);
    return 0;
}

// calculates the vector norm of the given number
// returns the real part of the complex number computed
// note: ||v|| = dot(v, v)^(1/2)
double cvec_norm(cvector_t v)
{
    complex_number_t cn;
    cvec_dot_product(&cn, v, v);
    complex_pow(&cn, cn, 0.5);
    return cn.real;
}

// calculates the projection of v2 onto v1
// projection of v2 onto v1 = dot(v1, v2) / (norm(v1, v1))^2
int cvec_project(complex_number_t *cn, cvector_t v1, cvector_t v2)
{   
    // error-checking
    if(cn == NULL)
    {
        return 1;
    }
    // calculate formula
    complex_number_t numer;
    cvec_dot_product(&numer, v1, v2);
    double denom = cvec_norm(v1);
    complex_scale(cn, numer, 1 / denom);
    return 0;
}