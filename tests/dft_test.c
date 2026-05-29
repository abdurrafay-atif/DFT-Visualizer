#include <assert.h> // for testing only
#include "../include/src/dft.h"
#include "../include/tests/dft_test.h"

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

// tests all files related to the DFT
int main()
{
    printf("-------------------------------------------------------------\n");
    printf("Running dft_test.c\n");
    printf("-------------------------------------------------------------\n");
    dft_test1();
    dft_test2();
    dft_test3();
    dft_test4();
    dft_zero_pad_test();
    printf("-------------------------------------------------------------\n");
    printf("All tests in dft_test.c have passed!\n");
    printf("-------------------------------------------------------------\n\n");
    return 0;
}

// example 1: [2j 4 -2j 1]
void dft_test1()
{
    // obtain time-domain vector from file
    FILE *file1 = fopen("tests/files/dft1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file1, vec1, RECT);
    assert(ret1 == 0);
    fclose(file1);
    // apply frequency-domain vector from file
    FILE *file2 = fopen("tests/files/idft1.txt", "r");
    cvector_t *vec2 = cvector_init_empty(4);
    int ret2 = cvector_read(file2, vec2, RECT);
    assert(ret2 == 0);
    fclose(file2);
    // apply DFT & IDFT
    cvector_t *freq = dft(*vec1);
    cvector_t *time = idft(*vec2);
    // check that vectors are accurate
    assert(cvector_equal(*time, *vec1));
    assert(cvector_equal(*freq, *vec2));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(freq);
    cvector_free(time);
    printf("Test 'dft_test1' --> PASSED!\n");
}

// example 2: [2j 1 -2j 4]
void dft_test2()
{
    // obtain time-domain vector from file
    FILE *file1 = fopen("tests/files/dft2.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file1, vec1, RECT);
    assert(ret1 == 0);
    fclose(file1);
    // apply frequency-domain vector from file
    FILE *file2 = fopen("tests/files/idft2.txt", "r");
    cvector_t *vec2 = cvector_init_empty(4);
    int ret2 = cvector_read(file2, vec2, RECT);
    assert(ret2 == 0);
    fclose(file2);
    // apply DFT & IDFT
    cvector_t *freq = dft(*vec1);
    cvector_t *time = idft(*vec2);
    // check that vectors are accurate
    assert(cvector_equal(*time, *vec1));
    assert(cvector_equal(*freq, *vec2));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(freq);
    cvector_free(time);
    printf("Test 'dft_test2' --> PASSED!\n");
}

// example 3: [-2j 4 2j 1]
void dft_test3()
{
    // obtain time-domain vector from file
    FILE *file1 = fopen("tests/files/dft3.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file1, vec1, RECT);
    assert(ret1 == 0);
    fclose(file1);
    // apply frequency-domain vector from file
    FILE *file2 = fopen("tests/files/idft3.txt", "r");
    cvector_t *vec2 = cvector_init_empty(4);
    int ret2 = cvector_read(file2, vec2, RECT);
    assert(ret2 == 0);
    fclose(file2);
    // apply DFT & IDFT
    cvector_t *freq = dft(*vec1);
    cvector_t *time = idft(*vec2);
    // check that vectors are accurate
    assert(cvector_equal(*time, *vec1));
    assert(cvector_equal(*freq, *vec2));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(freq);
    cvector_free(time);
    printf("Test 'dft_test3' --> PASSED!\n");
}

// example 4: [0 4 0 1]
void dft_test4()
{
    // obtain time-domain vector from file
    FILE *file1 = fopen("tests/files/dft4.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file1, vec1, RECT);
    assert(ret1 == 0);
    fclose(file1);
    // apply frequency-domain vector from file
    FILE *file2 = fopen("tests/files/idft4.txt", "r");
    cvector_t *vec2 = cvector_init_empty(4);
    int ret2 = cvector_read(file2, vec2, RECT);
    assert(ret2 == 0);
    fclose(file2);
    // apply DFT & IDFT
    cvector_t *freq = dft(*vec1);
    cvector_t *time = idft(*vec2);
    // check that vectors are accurate
    assert(cvector_equal(*time, *vec1));
    assert(cvector_equal(*freq, *vec2));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(freq);
    cvector_free(time);
    printf("Test 'dft_test4' --> PASSED!\n");
}

// checks that zero-pad works as intended
void dft_zero_pad_test()
{
    // obtain time-domain vector from file
    FILE *file1 = fopen("tests/files/dft1.txt", "r");
    cvector_t *vec1 = cvector_init_empty(4);
    int ret1 = cvector_read(file1, vec1, RECT);
    assert(ret1 == 0);
    fclose(file1);
    // apply frequency-domain vector from file
    FILE *file2 = fopen("tests/files/idft1.txt", "r");
    cvector_t *vec2 = cvector_init_empty(4);
    int ret2 = cvector_read(file2, vec2, RECT);
    assert(ret2 == 0);
    fclose(file2);
    // apply DFT with zero-pad
    cvector_t *freq = dft_zero_pad(*vec1, 4);
    assert(fequals(freq->vec[0].real, 5) && fequals(freq->vec[0].imaginary, 0));
    assert(fequals(freq->vec[2].real, 0) && fequals(freq->vec[2].imaginary, 1));
    assert(fequals(freq->vec[4].real, -5) && fequals(freq->vec[4].imaginary, 0));
    assert(fequals(freq->vec[6].real, 0) && fequals(freq->vec[6].imaginary, 7));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(freq);
    printf("Test 'dft_zero_pad_test' --> PASSED!\n");
}

