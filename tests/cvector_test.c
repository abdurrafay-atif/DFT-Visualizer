#include <assert.h> // for testing only
#include "../include/src/cvector.h"
#include "../include/tests/cvector_test.h"

const double EPSILON = 1e-6; // for floating point comparisons

// checks if two floating point numbers are very close in equality
// due to the usage of floating point numbers in complex numbers, this is necessary for testing
int fequals(double a, double b) 
{
    return fabs(a - b) < EPSILON;
}

// checks that two complex numbers are equal
int complex_equal(complex_number_t cn1, complex_number_t cn2)
{
    return fequals(cn1.real, cn2.real) && fequals(cn1.imaginary, cn2.imaginary);
}

// check that two vectors are equal
int cvector_equal(cvector_t v1, cvector_t v2)
{
    // two vectors of unequal size are not equal
    if(v1.size != v2.size)
    {
        return 0;
    }
    // compare each corresponding entries, check if they are equivalent via complex_equal()
    for(int ele = 0; ele < v1.size; ele++)
    {
        if(complex_equal(v1.vec[ele], v2.vec[ele]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

// tests all files associated with the cvector_t struct
int main()
{
    printf("-------------------------------------------------------------\n");
    printf("Running cvector_test.c\n");
    printf("-------------------------------------------------------------\n");
    test_cvector_init_empty_error();
    test_cvector_init_empty();
    test_cvector_init();
    test_cvector_conj();
    test_cvector_scale();
    test_cvector_add_error();
    test_cvector_add();
    test_cvector_ele_prod();
    test_cvector_circ_conv();
    test_cvector_max();
    test_cvector_sum();
    test_cvector_dot();
    test_circ_reverse_one_ele();
    test_circ_reverse_odd();
    test_circ_reverse_even();
    test_circ_shift();
    test_fourier_modulate();
    printf("-------------------------------------------------------------\n");
    printf("All tests in cvector_test.c have passed!\n");
    printf("-------------------------------------------------------------\n\n");
    return 0;
}

// tests the cvector_init_empty() function when given invalid input
void test_cvector_init_empty_error()
{
    cvector_t *error = cvector_init_empty(0);
    assert(error == NULL);
    printf("Test 'test_cvector_init_empty_error' --> PASSED!\n");
}

// tests the cvector_init_empty() function to ensure it works as intended (all entries are (0, 0))
void test_cvector_init_empty()
{
    cvector_t *vec = cvector_init_empty(5);
    assert(vec != NULL);
    for(int ele = 0; ele < vec->size; ele++)
    {
        assert(fequals(vec->vec[ele].real, 0));
        assert(fequals(vec->vec[ele].imaginary, 0));
    }
    cvector_free(vec);
    printf("Test 'test_cvector_init_empty' --> PASSED!\n");
}

// tests the cvector_init() function as well as cvector_read()
void test_cvector_init()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // copy over to another vector via cvector_init()
    cvector_t *vec2;
    vec2 = cvector_init(vec1->vec, vec1->size); // deep copy
    // check that vec2 has the correct elements
    assert(fequals(vec2->vec[0].real, 4));
    assert(fequals(vec2->vec[0].imaginary, 7));
    assert(fequals(vec2->vec[1].real, 9));
    assert(fequals(vec2->vec[1].imaginary, -3));
    assert(fequals(vec2->vec[2].real, 6));
    assert(fequals(vec2->vec[2].imaginary, -1));
    assert(fequals(vec2->vec[3].real, -1));
    assert(fequals(vec2->vec[3].imaginary, 6));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_cvector_init' --> PASSED!\n");
}

// tests the cvector_conj() function
void test_cvector_conj()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // copy the conjugate to another vector
    cvector_t *vec2 = cvector_conj(*vec1); 
    // check that vec2 has the correct elements
    assert(fequals(vec2->vec[0].real, 4));
    assert(fequals(vec2->vec[0].imaginary, -7));
    assert(fequals(vec2->vec[1].real, 9));
    assert(fequals(vec2->vec[1].imaginary, 3));
    assert(fequals(vec2->vec[2].real, 6));
    assert(fequals(vec2->vec[2].imaginary, 1));
    assert(fequals(vec2->vec[3].real, -1));
    assert(fequals(vec2->vec[3].imaginary, -6));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_cvector_conj' --> PASSED!\n");
}

// tests the cvector_scale() function
void test_cvector_scale()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // perform scaling
    complex_number_t cn;
    complex_num_init(&cn, 3.0, 6.0);
    cvector_t *vec2 = cvector_scale(*vec1, cn);
    // check that vec2 has the correct elements
    assert(fequals(vec2->vec[0].real, -30));
    assert(fequals(vec2->vec[0].imaginary, 45));
    assert(fequals(vec2->vec[1].real, 45));
    assert(fequals(vec2->vec[1].imaginary, 45));
    assert(fequals(vec2->vec[2].real, 24));
    assert(fequals(vec2->vec[2].imaginary, 33));
    assert(fequals(vec2->vec[3].real, -39));
    assert(fequals(vec2->vec[3].imaginary, 12));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_cvector_scale' --> PASSED!\n");
}

// tests that cvectors with non-matching sizes cannot be added
void test_cvector_add_error()
{
    cvector_t *vec1 = cvector_init_empty(8);
    cvector_t *vec2 = cvector_init_empty(4);
    cvector_t *ret = cvector_add(*vec1, *vec2);
    assert(ret == NULL);
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(ret);
    printf("Test 'test_cvector_add_error' --> PASSED!\n");
}

// tests the cvector_add() function (specially on sum of indentical complex vectors)
void test_cvector_add()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // obtain sum of vec1 & itself
    cvector_t *vec2 = cvector_add(*vec1, *vec1);
    // assert correctness
    assert(fequals(vec2->vec[0].real, 8));
    assert(fequals(vec2->vec[0].imaginary, 14));
    assert(fequals(vec2->vec[1].real, 18));
    assert(fequals(vec2->vec[1].imaginary, -6));
    assert(fequals(vec2->vec[2].real, 12));
    assert(fequals(vec2->vec[2].imaginary, -2));
    assert(fequals(vec2->vec[3].real, -2));
    assert(fequals(vec2->vec[3].imaginary, 12));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_cvector_add' --> PASSED!\n");
}

// tests the cvector_ele_prod() function (specially on element product of indentical complex vectors)
void test_cvector_ele_prod()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // obtain sum of vec1 & itself
    cvector_t *vec2 = cvector_element_product(*vec1, *vec1);
    // assert correctness
    assert(fequals(vec2->vec[0].real, -33));
    assert(fequals(vec2->vec[0].imaginary, 56));
    assert(fequals(vec2->vec[1].real, 72));
    assert(fequals(vec2->vec[1].imaginary, -54));
    assert(fequals(vec2->vec[2].real, 35));
    assert(fequals(vec2->vec[2].imaginary, -12));
    assert(fequals(vec2->vec[3].real, -35));
    assert(fequals(vec2->vec[3].imaginary, -12));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_cvector_ele_prod' --> PASSED!\n");
}

// tests the cvector_circ_convolve() function
void test_cvector_circ_conv()
{
    // obtain LHS vector 
    FILE *file1 = fopen("tests/files/convolve1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file1, vec1, RECT);
    assert(ret1 == 0);
    fclose(file1);
    // obtain RHS vector
    FILE *file2 = fopen("tests/files/convolve2.txt", "r");
    cvector_t *vec2 = cvector_init_empty(4);
    int ret2 = cvector_read(file2, vec2, RECT);
    assert(ret2 == 0);
    fclose(file2);
    // obtain result vector
    FILE *file3 = fopen("tests/files/convolve12res.txt", "r");
    cvector_t *res = cvector_init_empty(4);
    int ret3 = cvector_read(file3, res, RECT);
    assert(ret3 == 0);
    fclose(file3);
    // perform circular convolution & verify results
    cvector_t *conv = cvector_circ_convolve(*vec1, *vec2);
    assert(cvector_equal(*res, *conv));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(res);
    cvector_free(conv);
    printf("Test 'test_cvector_circ_conv' --> PASSED!\n");
}

// tests that the cvector_max() function gives the correct output
void test_cvector_max()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // determine if max (maximum modulus) can be obtained correctly
    double max = cvector_max(*vec1);
    assert(fequals(max, 9.48683298051));
    cvector_free(vec1);
    printf("Test 'test_cvector_max' --> PASSED!\n");
}

// tests that the cvector_sum() function gives correct output for an example vector
// it is suppose to obtain the sum of Real & Imaginary components across all indices of vector
void test_cvector_sum()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // obtain sum & verify
    complex_number_t cn;
    int ret2 = cvector_sum(&cn, *vec1);
    assert(ret2 == 0);
    assert(fequals(cn.real, 18));
    assert(fequals(cn.imaginary, 9));
    cvector_free(vec1);
    printf("Test 'test_cvector_sum' --> PASSED!\n");
}

// test that cvector_dot_product() works as intended
void test_cvector_dot()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // obtain sum & verify
    complex_number_t cn;
    int ret2 = cvector_dot_product(&cn, *vec1, *vec1);
    assert(ret2 == 0);
    assert(fequals(cn.real, 229));
    assert(fequals(cn.imaginary, 0));
    cvector_free(vec1);
    printf("Test 'test_cvector_dot' --> PASSED!\n");
}

// tests the cvector_circ_reverse() function on a vector with one element
void test_circ_reverse_one_ele()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_num_rect.txt", "r");
    cvector_t *vec1 = cvector_init_empty(1);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // reverse & verify functionality
    cvector_t *vec2 = cvector_circ_reverse(*vec1);
    assert(fequals(vec2->vec[0].real, 4));
    assert(fequals(vec2->vec[0].imaginary, 3));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_circ_reverse_one_ele' --> PASSED!\n");
}

// tests the cvector_circ_reverse() function on a vector with an odd number of elements
// this means that all elements (besides the first) swap location with another
void test_circ_reverse_odd()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_2.txt", "r");
    cvector_t *vec1 = cvector_init_empty(5);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // reverse & verify functionality
    cvector_t *vec2 = cvector_circ_reverse(*vec1);
    assert(fequals(vec2->vec[0].real, 4));
    assert(fequals(vec2->vec[0].imaginary, 7));
    assert(fequals(vec2->vec[1].real, 10));
    assert(fequals(vec2->vec[1].imaginary, -4));
    assert(fequals(vec2->vec[2].real, -1));
    assert(fequals(vec2->vec[2].imaginary, 6));
    assert(fequals(vec2->vec[3].real, 6));
    assert(fequals(vec2->vec[3].imaginary, -1));
    assert(fequals(vec2->vec[4].real, 9));
    assert(fequals(vec2->vec[4].imaginary, -3));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_circ_reverse_odd' --> PASSED!\n");
}

// tests the cvector_circ_reverse() function on a vector with an even number of elements
// this means that the first & middle elements do not swap with any other element
void test_circ_reverse_even()
{
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file, vec1, RECT);
    assert(ret1 == 0);
    fclose(file);
    // reverse & verify functionality
    cvector_t *vec2 = cvector_circ_reverse(*vec1);
    assert(fequals(vec2->vec[0].real, 4));
    assert(fequals(vec2->vec[0].imaginary, 7));
    assert(fequals(vec2->vec[1].real, -1));
    assert(fequals(vec2->vec[1].imaginary, 6));
    assert(fequals(vec2->vec[2].real, 6));
    assert(fequals(vec2->vec[2].imaginary, -1));
    assert(fequals(vec2->vec[3].real, 9));
    assert(fequals(vec2->vec[3].imaginary, -3));
    cvector_free(vec1);
    cvector_free(vec2);
    printf("Test 'test_circ_reverse_even' --> PASSED!\n");
}

// tests the cvector_circular_shift() function with shifts within & out-of-bounds
void test_circ_shift()
{   
    // obtain vector from file
    FILE *file = fopen("tests/files/complex_nums_2.txt", "r");
    cvector_t *vec = cvector_init_empty(5);
    int ret1 = cvector_read(file, vec, RECT);
    assert(ret1 == 0);
    fclose(file);
    // perform shifting 
    cvector_t *nshift1 = cvector_circ_shift(*vec, -1);
    cvector_t *shift0 = cvector_circ_shift(*vec, 0);
    cvector_t *shift1 = cvector_circ_shift(*vec, 1);
    cvector_t *shift2 = cvector_circ_shift(*vec, 2);
    cvector_t *shift3 = cvector_circ_shift(*vec, 3);
    cvector_t *shift4 = cvector_circ_shift(*vec, 4);
    cvector_t *shift5 = cvector_circ_shift(*vec, 5);
    // verify nshift1
    assert(fequals(nshift1->vec[0].real, 9));
    assert(fequals(nshift1->vec[0].imaginary, -3));
    assert(fequals(nshift1->vec[1].real, 6));
    assert(fequals(nshift1->vec[1].imaginary, -1));
    assert(fequals(nshift1->vec[2].real, -1));
    assert(fequals(nshift1->vec[2].imaginary, 6));
    assert(fequals(nshift1->vec[3].real, 10));
    assert(fequals(nshift1->vec[3].imaginary, -4));
    assert(fequals(nshift1->vec[4].real, 4));
    assert(fequals(nshift1->vec[4].imaginary, 7));
    // verify shift0
    assert(fequals(shift0->vec[0].real, 4));
    assert(fequals(shift0->vec[0].imaginary, 7));
    assert(fequals(shift0->vec[1].real, 9));
    assert(fequals(shift0->vec[1].imaginary, -3));
    assert(fequals(shift0->vec[2].real, 6));
    assert(fequals(shift0->vec[2].imaginary, -1));
    assert(fequals(shift0->vec[3].real, -1));
    assert(fequals(shift0->vec[3].imaginary, 6));
    assert(fequals(shift0->vec[4].real, 10));
    assert(fequals(shift0->vec[4].imaginary, -4));
    // verify shift1
    assert(fequals(shift1->vec[0].real, 10));
    assert(fequals(shift1->vec[0].imaginary, -4));
    assert(fequals(shift1->vec[1].real, 4));
    assert(fequals(shift1->vec[1].imaginary, 7));
    assert(fequals(shift1->vec[2].real, 9));
    assert(fequals(shift1->vec[2].imaginary, -3));
    assert(fequals(shift1->vec[3].real, 6));
    assert(fequals(shift1->vec[3].imaginary, -1));
    assert(fequals(shift1->vec[4].real, -1));
    assert(fequals(shift1->vec[4].imaginary, 6));
    // verify shift2
    assert(fequals(shift2->vec[0].real, -1));
    assert(fequals(shift2->vec[0].imaginary, 6));
    assert(fequals(shift2->vec[1].real, 10));
    assert(fequals(shift2->vec[1].imaginary, -4));
    assert(fequals(shift2->vec[2].real, 4));
    assert(fequals(shift2->vec[2].imaginary, 7));
    assert(fequals(shift2->vec[3].real, 9));
    assert(fequals(shift2->vec[3].imaginary, -3));
    assert(fequals(shift2->vec[4].real, 6));
    assert(fequals(shift2->vec[4].imaginary, -1));
    // verify shift3
    assert(fequals(shift3->vec[0].real, 6));
    assert(fequals(shift3->vec[0].imaginary, -1));
    assert(fequals(shift3->vec[1].real, -1));
    assert(fequals(shift3->vec[1].imaginary, 6));
    assert(fequals(shift3->vec[2].real, 10));
    assert(fequals(shift3->vec[2].imaginary, -4));
    assert(fequals(shift3->vec[3].real, 4));
    assert(fequals(shift3->vec[3].imaginary, 7));
    assert(fequals(shift3->vec[4].real, 9));
    assert(fequals(shift3->vec[4].imaginary, -3));
    // verify shift4
    assert(fequals(shift4->vec[0].real, 9));
    assert(fequals(shift4->vec[0].imaginary, -3));
    assert(fequals(shift4->vec[1].real, 6));
    assert(fequals(shift4->vec[1].imaginary, -1));
    assert(fequals(shift4->vec[2].real, -1));
    assert(fequals(shift4->vec[2].imaginary, 6));
    assert(fequals(shift4->vec[3].real, 10));
    assert(fequals(shift4->vec[3].imaginary, -4));
    assert(fequals(shift4->vec[4].real, 4));
    assert(fequals(shift4->vec[4].imaginary, 7));
    // verify shift5
    assert(fequals(shift5->vec[0].real, 4));
    assert(fequals(shift5->vec[0].imaginary, 7));
    assert(fequals(shift5->vec[1].real, 9));
    assert(fequals(shift5->vec[1].imaginary, -3));
    assert(fequals(shift5->vec[2].real, 6));
    assert(fequals(shift5->vec[2].imaginary, -1));
    assert(fequals(shift5->vec[3].real, -1));
    assert(fequals(shift5->vec[3].imaginary, 6));
    assert(fequals(shift5->vec[4].real, 10));
    assert(fequals(shift5->vec[4].imaginary, -4));
    // free allocated material
    cvector_free(vec);
    cvector_free(nshift1);
    cvector_free(shift0);
    cvector_free(shift1);
    cvector_free(shift2);
    cvector_free(shift3);
    cvector_free(shift4);
    cvector_free(shift5);
    printf("Test 'test_circ_shift' --> PASSED!\n");
}

// tests fourier modulation on a size 4 vector consisting of 1's
void test_fourier_modulate()
{
    // form
    cvector_t *vec = cvector_init_empty(4);
    cvector_place(vec, 0, 1.0, 0.0);
    cvector_place(vec, 1, 1.0, 0.0);
    cvector_place(vec, 2, 1.0, 0.0);
    cvector_place(vec, 3, 1.0, 0.0);
    cvector_t *f0 = cvector_fourier_modulate(*vec, 0);
    cvector_t *f1 = cvector_fourier_modulate(*vec, 1);
    cvector_t *f2 = cvector_fourier_modulate(*vec, 2);
    cvector_t *f3 = cvector_fourier_modulate(*vec, 3);
    // verify f0
    assert(fequals(f0->vec[0].real, 1) && fequals(f0->vec[0].imaginary, 0));
    assert(fequals(f0->vec[1].real, 1) && fequals(f0->vec[1].imaginary, 0));
    assert(fequals(f0->vec[2].real, 1) && fequals(f0->vec[2].imaginary, 0));
    assert(fequals(f0->vec[3].real, 1) && fequals(f0->vec[3].imaginary, 0));
    // verify f1
    assert(fequals(f1->vec[0].real, 1) && fequals(f1->vec[0].imaginary, 0));
    assert(fequals(f1->vec[1].real, 0) && fequals(f1->vec[1].imaginary, 1));
    assert(fequals(f1->vec[2].real, -1) && fequals(f1->vec[2].imaginary, 0));
    assert(fequals(f1->vec[3].real, 0) && fequals(f1->vec[3].imaginary, -1));
    // verify f2
    assert(fequals(f2->vec[0].real, 1) && fequals(f2->vec[0].imaginary, 0));
    assert(fequals(f2->vec[1].real, -1) && fequals(f2->vec[1].imaginary, 0));
    assert(fequals(f2->vec[2].real, 1) && fequals(f2->vec[2].imaginary, 0));
    assert(fequals(f2->vec[3].real, -1) && fequals(f2->vec[3].imaginary, 0));
    // verify f3
    assert(fequals(f3->vec[0].real, 1) && fequals(f3->vec[0].imaginary, 0));
    assert(fequals(f3->vec[1].real, 0) && fequals(f3->vec[1].imaginary, -1));
    assert(fequals(f3->vec[2].real, -1) && fequals(f3->vec[2].imaginary, 0));
    assert(fequals(f3->vec[3].real, 0) && fequals(f3->vec[3].imaginary, 1));
    cvector_free(vec);
    cvector_free(f0);
    cvector_free(f1);
    cvector_free(f2);
    cvector_free(f3);
    printf("Test 'test_fourier_modulate' --> PASSED!\n");
}