#include <assert.h> // for testing only
#include "../include/src/vector.h"
#include "../include/tests/vector_test.h"

// keep track of # of tests (to show the tests are passing when new ones are added)
int num_tests_passed;
const double EPSILON = 1e-9; // for floating point comparisons

// checks if two floating point numbers are very close in equality
int fequals(double a, double b) 
{
    return fabs(a - b) < EPSILON;
}

// forms complex vector based on file
cvector_t *cvec_from_file(char *filename)
{
    // open file
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        return NULL;
    }
    int size = 0;
    char c;
    // count # of complex numbers contained in file
    while(fscanf(file, "%c", &c) != EOF)
    {
        if(c == '\n')
        {
            size++;
        }
    }
    rewind(file);
    // construct vector
    cvector_t *vec = cvec_init_empty(size);
    vec->size = size;
    for(int ele = 0; ele < vec->size; ele++)
    {
        double real;
        double imaginary;
        fscanf(file, "%lf + j*(%lf)", &real, &imaginary);
        complex_num_init(&vec->vec[ele], real, imaginary);
    }
    fclose(file);
    return vec;
}

int main()
{
    printf("Running vector_test.c ...\n");
    num_tests_passed = 0;
    test_cvec_empty_init();
    test_cvec_init();
    printf("All %d tests were successful!\n", num_tests_passed);
    return 0;
}

void test_cvec_empty_init()
{
    cvector_t *vec = cvec_init_empty(3);
    assert(vec != NULL);
    assert(vec->size == 3);
    assert(vec->vec[0].real == 0.0 && vec->vec[0].imaginary == 0.0);
    assert(vec->vec[1].real == 0.0 && vec->vec[1].imaginary == 0.0);
    assert(vec->vec[2].real == 0.0 && vec->vec[2].imaginary == 0.0);
    cvec_free(vec);
    num_tests_passed++;
}

void test_cvec_init()
{
    cvector_t *vec = cvec_from_file("tests/files/complex_nums_1.txt");
    cvec_print(*vec, RECT);
    assert(vec != NULL);
    assert(vec->size == 3);
    assert(vec->vec[0].real == 2.0 && vec->vec[0].imaginary == 0.0);
    assert(vec->vec[1].real == 3.0 && vec->vec[1].imaginary == 1.0);
    assert(vec->vec[2].real == 0.0 && vec->vec[2].imaginary == 5.0);
    cvec_free(vec);
    num_tests_passed++;
}

void test_cvec_conj()
{

}