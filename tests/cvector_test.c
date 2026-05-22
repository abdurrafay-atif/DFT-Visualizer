#include <assert.h> // for testing only
#include "../include/src/cvector.h"
#include "../include/tests/cvector_test.h"

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
    cvector_t *vec = cvector_init_empty(size);
    vec->size = size;
    for(int ele = 0; ele < vec->size; ele++)
    {
        double real;
        double imaginary;
        fscanf(file, "%lf + j*(%lf)", &real, &imaginary);
        cvector_place(vec, ele, real, imaginary);
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
    test_cvec_conj();
    test_cvec_sum();
    test_cvec_dot();
    test_cvec_conj();
    test_cvec_add();
    test_cvec_prod();
    test_cvec_scale();
    test_cvec_reverse();
    printf("All %d tests were successful!\n", num_tests_passed);
    return 0;
}

void test_cvec_empty_init()
{
    cvector_t *vec = cvector_init_empty(3);
    assert(vec != NULL);
    assert(vec->size == 3);
    assert(vec->vec[0].real == 0.0 && vec->vec[0].imaginary == 0.0);
    assert(vec->vec[1].real == 0.0 && vec->vec[1].imaginary == 0.0);
    assert(vec->vec[2].real == 0.0 && vec->vec[2].imaginary == 0.0);
    cvector_free(vec);
    num_tests_passed++;
}

void test_cvec_init()
{
    cvector_t *vec = cvec_from_file("tests/files/complex_nums_1.txt");
    assert(vec != NULL);
    assert(vec->size == 3);
    assert(vec->vec[0].real == 2.0 && vec->vec[0].imaginary == 0.0);
    assert(vec->vec[1].real == 3.0 && vec->vec[1].imaginary == 1.0);
    assert(vec->vec[2].real == 0.0 && vec->vec[2].imaginary == 5.0);
    cvector_free(vec);
    num_tests_passed++;
}

void test_cvec_sum()
{
    cvector_t *vec = cvec_from_file("tests/files/complex_nums_1.txt");
    assert(vec != NULL);
    complex_number_t cn;
    cvector_sum(&cn, *vec);
    assert(cn.real == 5 && cn.imaginary == 6);
    cvector_free(vec);
    num_tests_passed++;
}

void test_cvec_dot()
{
    cvector_t *vec1 = cvec_from_file("tests/files/complex_nums_1.txt");
    cvector_t *vec2 = cvec_from_file("tests/files/complex_nums_2.txt");
    complex_number_t cn;
    cvector_dot_product(&cn, *vec1, *vec2);
    assert(fequals(cn.real, 4) && fequals(cn.imaginary, -7));
    cvector_dot_product(&cn, *vec1, *vec1); // norm^2
    assert(fequals(cn.real, 39) && fequals(cn.imaginary, 0));
    cvector_free(vec1);
    cvector_free(vec2);
    num_tests_passed++;
}

void test_cvec_conj()
{
    cvector_t *vec = cvec_from_file("tests/files/complex_nums_1.txt");
    assert(vec != NULL);
    cvector_t *conj_vec = cvector_conj(*vec);
    assert(conj_vec != NULL);
    assert(conj_vec->size == 3);
    assert(conj_vec->vec[0].real == 2.0 && conj_vec->vec[0].imaginary == 0.0);
    assert(conj_vec->vec[1].real == 3.0 && conj_vec->vec[1].imaginary == -1.0);
    assert(conj_vec->vec[2].real == 0.0 && conj_vec->vec[2].imaginary == -5.0);
    cvector_free(vec);
    cvector_free(conj_vec);
    num_tests_passed++;
}

void test_cvec_scale()
{
    cvector_t *vec = cvec_from_file("tests/files/complex_nums_1.txt");
    assert(vec != NULL);
    complex_number_t cn;
    complex_num_init(&cn, 4, 3);
    cvector_t *scale_vec = cvector_scale(*vec, cn);
    assert(scale_vec != NULL);
    assert(scale_vec->size == 3);
    assert(fequals(scale_vec->vec[0].real, 8.0) && fequals(scale_vec->vec[0].imaginary, 6.0));
    assert(fequals(scale_vec->vec[1].real, 9.0) && fequals(scale_vec->vec[1].imaginary, 13.0));
    assert(fequals(scale_vec->vec[2].real, -15.0) && fequals(scale_vec->vec[2].imaginary, 20.0));
    cvector_free(vec);
    cvector_free(scale_vec);
    num_tests_passed++;
}

void test_cvec_add()
{
    cvector_t *vec1 = cvec_from_file("tests/files/complex_nums_1.txt");
    cvector_t *vec2 = cvec_from_file("tests/files/complex_nums_2.txt");
    cvector_t *sum = cvector_add(*vec1, *vec2);
    assert(sum->size == 3);
    assert(sum->vec[0].real == 3 && sum->vec[0].imaginary == 1);
    assert(sum->vec[1].real == 7 && sum->vec[1].imaginary == 1);
    assert(sum->vec[2].real == 1 && sum->vec[2].imaginary == 3);
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(sum);
    num_tests_passed++;
}

void test_cvec_prod()
{
    cvector_t *vec1 = cvec_from_file("tests/files/complex_nums_1.txt");
    cvector_t *vec2 = cvec_from_file("tests/files/complex_nums_2.txt");
    cvector_t *prod = cvector_element_prod(*vec1, *vec2);
    assert(prod->size == 3);
    assert(fequals(prod->vec[0].real, 2) && fequals(prod->vec[0].imaginary, 2));
    assert(fequals(prod->vec[1].real, 12) && fequals(prod->vec[1].imaginary, 4));
    assert(fequals(prod->vec[2].real, 10) && fequals(prod->vec[2].imaginary, 5));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(prod);
    num_tests_passed++;
}

void test_cvec_reverse()
{
    cvector_t *vec1 = cvec_from_file("tests/files/complex_nums_3.txt");
    cvector_t *rev1 = cvector_circ_reverse(*vec1);
    assert(fequals(rev1->vec[0].real, 2) && fequals(rev1->vec[0].imaginary, 0));
    assert(fequals(rev1->vec[1].real, 1) && fequals(rev1->vec[1].imaginary, -2));
    assert(fequals(rev1->vec[2].real, 4) && fequals(rev1->vec[2].imaginary, 0));
    assert(fequals(rev1->vec[3].real, 1) && fequals(rev1->vec[3].imaginary, 1));
    assert(fequals(rev1->vec[4].real, 0) && fequals(rev1->vec[4].imaginary, 5));
    assert(fequals(rev1->vec[5].real, 3) && fequals(rev1->vec[5].imaginary, 1));
    cvector_t *vec2 = cvec_from_file("tests/files/complex_nums_4.txt");
    cvector_t *rev2 = cvector_circ_reverse(*vec2);
    assert(fequals(rev2->vec[0].real, 2) && fequals(rev2->vec[0].imaginary, 0));
    assert(fequals(rev2->vec[1].real, 1) && fequals(rev2->vec[1].imaginary, -2));
    assert(fequals(rev2->vec[2].real, 4) && fequals(rev2->vec[2].imaginary, 0));
    assert(fequals(rev2->vec[3].real, 1) && fequals(rev2->vec[3].imaginary, 1));
    assert(fequals(rev2->vec[4].real, 0) && fequals(rev2->vec[4].imaginary, 5));
    assert(fequals(rev2->vec[5].real, 3) && fequals(rev2->vec[5].imaginary, 1));
    assert(fequals(rev2->vec[6].real, 8) && fequals(rev2->vec[6].imaginary, -4));
    cvector_free(vec1);
    cvector_free(vec2);
    cvector_free(rev1);
    cvector_free(rev2);
    num_tests_passed++;
}

void test_cvec_shift()
{

}

void test_cvec_modulate()
{

}