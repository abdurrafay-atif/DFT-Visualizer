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

// appends the specified # of zero's to the passed in vector
cvector_t *cvector_append_zeros(cvector_t v, int zero_pad)
{
    // handle invalid input
    if(zero_pad < 0)
    {
        return NULL;
    }
    // create a new vector which consists of the input vector + "zero-pad" # of zeros
    cvector_t *padded_input = cvector_init_empty(v.size + zero_pad);
    // place the input into the DFT vector
    for(int ele = 0; ele < v.size; ele++)
    {
        cvector_place(padded_input, ele, v.vec[ele].real, v.vec[ele].imaginary);
    }
    return padded_input;
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

// performs circular convolution between the two vectors
// checks that both vectors are the same length, if not appends 0's to the shorter vector
cvector_t *cvector_circ_convolve(cvector_t v1, cvector_t v2)
{
    // determine the longer vector (this will be the length of the result vector)
    int size = (v1.size > v2.size) ? v1.size : v2.size;
    // zero-append the shorter vector
    cvector_t *shorter;
    cvector_t *longer;
    if(size == v1.size)
    {
        shorter = cvector_append_zeros(v1, v2.size - v1.size);
        longer = &v2;
    }
    else
    {
        shorter = cvector_append_zeros(v2, v1.size - v2.size);
        longer = &v1;
    }
    // form vector which stores the circular convolution between v1 & v2
    cvector_t *circ_conv = cvector_init_empty(size);
    // perform circular reversal of shorter vector (useful for calculating circular convolution)
    cvector_t *rev_short = cvector_circ_reverse(v1);
    // compute the circular convolution 
    // ALGORITHM: Loop through the shorter vector "size" times
    // Each loop, run through a "reverse shifted" version of the original vector (via modulus)
    for(int shift = 0; shift < size; shift++)
    {
        // initialize complex number to store at the given index after computation
        complex_number_t cn;
        complex_num_empty(&cn);
        // loop through all elements of the longer vector
        // based on current shift, sum products of corresponding elements
        for(int ele = 0; ele < size; ele++)
        {
            int shorter_index = (((ele - shift) % size) + size) % size;
            complex_number_t prod;
            complex_prod(&prod, rev_short->vec[shorter_index], longer->vec[ele]);
            complex_add(&cn, cn, prod);
        }
        // store the fully calculated value into the corresponding spot in the result vector
        cvector_place(circ_conv, shift, cn.real, cn.imaginary);
    }
    // free vectors allocated in the process of circular convolution
    if(size == v1.size)
    {
        cvector_free(shorter);
    }
    else
    {
        cvector_free(longer);
    }
    cvector_free(rev_short);
    return circ_conv;
}