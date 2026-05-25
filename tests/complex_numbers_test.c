#include <assert.h> // for testing only
#include "../include/src/complex.h"
#include "../include/tests/complex_numbers_test.h"

const double EPSILON = 1e-6; // for floating point comparisons

// checks if two floating point numbers are very close in equality
// due to the usage of floating point numbers in complex numbers, this is necessary for testing
int fequals(double a, double b) 
{
    return fabs(a - b) < EPSILON;
}

// tests all files in src/complex_numbers
int main()
{
    printf("-------------------------------------------------------------\n");
    printf("Running complex_numbers_test.c\n");
    printf("-------------------------------------------------------------\n");
    test_normalize_angle_no_change();
    test_normalize_angle_negative_angle();
    test_normalize_angle_large_negative();
    test_normalize_angle_over_angle();
    test_normalize_angle_large_positive();
    test_normalize_angle_edge_cases();
    test_complex_num_init_error();
    test_complex_num_init_both_pos();
    test_complex_num_init_posneg();
    test_complex_num_init_negpos();
    test_complex_num_init_both_neg();
    test_complex_num_rev_error();
    test_complex_num_rev();
    test_complex_num_empty();
    test_complex_print_rect();
    printf("-------------------------------------------------------------\n");
    printf("All tests for complex_numbers_test.c have passed!\n");
    printf("-------------------------------------------------------------\n\n");
    return 0;
}

// tests the normalize_angle() function when the passed in angle is already normalized
void test_normalize_angle_no_change()
{
    double angle = 0.0;
    for(double test = 0.0; test <= 2 * M_PI; test = test + 0.1)
    {
        assert(fequals(angle, normalize_angle(angle)));
    }
    printf("Test 'test_normalize_angle_no_change' --> PASSED!\n");
}

// tests the normalize_angle() function when the passed in angle is a small negative value
void test_normalize_angle_negative_angle()
{
    double angle = M_PI * (-1.0 / 3.0);
    assert(fequals(angle + 2 * M_PI, normalize_angle(angle)));
    printf("Test 'test_normalize_angle_negative_angle' --> PASSED!\n");
}


// tests the normalize_angle() function when the passed in angle is a large negative value
void test_normalize_angle_large_negative()
{
    double angle = M_PI * (-1.0 / 3.0) * 50000.0;
    assert(fequals(normalize_angle(angle), (4.0 * M_PI) / 3.0));
    printf("Test 'test_normalize_angle_large_negative' --> PASSED!\n");
}

// tests the normalize_angle() function when the passed in angle is over 2 * PI (but still small)
void test_normalize_angle_over_angle()
{
    double angle = M_PI * (8.0 / 3.0);
    assert(fequals(normalize_angle(angle), M_PI * (2.0 / 3.0)));
    printf("Test 'test_normalize_angle_over_angle' --> PASSED!\n");
}

// tests the normalize_angle() function when the passed in angle is over 2 * PI (very large angle)
void test_normalize_angle_large_positive()
{
    double angle = M_PI * (8.0 / 3.0) * 50000;
    assert(fequals(normalize_angle(angle), (4.0 * M_PI) / 3.0));
    printf("Test 'test_normalize_angle_over_large_angle' --> PASSED!\n");
}

// tests the 2 * M_PI edge case of the normalize_angle() function (should normalize to 0 degrees)
void test_normalize_angle_edge_cases()
{
    double angle = 2 * M_PI;
    assert(fequals(normalize_angle(angle), 0.0));
    printf("Test 'test_normalize_angle_edge_cases' --> PASSED!\n");
}

// tests the complex_num_init() function when given error input
// cases:
// cn == NULL
void test_complex_num_init_error()
{
    complex_number_t *error = NULL;
    int ret = complex_num_init(error, 4, 3);
    assert(ret == 1);
    printf("Test 'test_complex_num_init_error' --> PASSED!\n");
}

// tests the complex_num_init() function when given real = +, imag = +
void test_complex_num_init_both_pos()
{
    complex_number_t cn;
    int ret = complex_num_init(&cn, 4, 3);
    assert(ret == 0);
    assert(fequals(cn.real, 4.0));
    assert(fequals(cn.imaginary, 3.0));
    assert(fequals(cn.modulus, 5.0));
    assert(fequals(cn.angle, 0.64350110879));
    printf("Test 'test_complex_num_init_both_pos' --> PASSED!\n");
}

// tests the complex_num_init() function when given real = +, imag = -
void test_complex_num_init_posneg()
{
    complex_number_t cn;
    int ret = complex_num_init(&cn, 4, -3);
    assert(ret == 0);
    assert(fequals(cn.real, 4.0));
    assert(fequals(cn.imaginary, -3.0));
    assert(fequals(cn.modulus, 5.0));
    assert(fequals(cn.angle, 5.63968419839));
    printf("Test 'test_complex_num_init_posneg' --> PASSED!\n");
}

// tests the complex_num_init() function when given real = -, imag = +
void test_complex_num_init_negpos()
{
    complex_number_t cn;
    int ret = complex_num_init(&cn, -4, 3);
    assert(ret == 0);
    assert(fequals(cn.real, -4.0));
    assert(fequals(cn.imaginary, 3.0));
    assert(fequals(cn.modulus, 5.0));
    assert(fequals(cn.angle, 2.4980915448));
    printf("Test 'test_complex_num_init_negpos' --> PASSED!\n");
}

// tests the complex_num_init() function when given real = -, imag = -
void test_complex_num_init_both_neg()
{
    complex_number_t cn;
    int ret = complex_num_init(&cn, -4, -3);
    assert(ret == 0);
    assert(fequals(cn.real, -4.0));
    assert(fequals(cn.imaginary, -3.0));
    assert(fequals(cn.modulus, 5.0));
    assert(fequals(cn.angle, 3.78509376238));
    printf("Test 'test_complex_num_init_both_neg' --> PASSED!\n");
}

// tests the complex_num_rev_init() function when given error input
// cases:
// cn == NULL
// modulus < 0 (modulus cannot be negative)
void test_complex_num_rev_error()
{
    complex_number_t *error = NULL;
    int ret1 = complex_num_rev_init(error, 5, 0.64350110879);
    assert(ret1 == 1);
    complex_number_t not_error;
    int ret2 = complex_num_rev_init(&not_error, -5, 0.64350110879);
    assert(ret2 == 1);
    printf("Test 'test_complex_num_rev_error' --> PASSED!\n");
}

// tests functionality of complex_num_rev_init()
// normalize_angle(), cos(), & sin() all work as intended, so only need to test for one example
void test_complex_num_rev()
{
    complex_number_t cn;
    int ret = complex_num_rev_init(&cn, 5, 0.64350110879);
    assert(ret == 0);
    assert(fequals(cn.real, 4));
    assert(fequals(cn.imaginary, 3));
    assert(fequals(cn.modulus, 5));
    assert(fequals(cn.angle, 0.64350110879));
    printf("Test 'test_complex_num_rev' --> PASSED!\n");
}

// tests functionality of complex_num_empty()
void test_complex_num_empty()
{
    complex_number_t cn;
    int ret = complex_num_empty(&cn);
    assert(ret == 0);
    assert(fequals(cn.real, 0));
    assert(fequals(cn.imaginary, 0));
    assert(fequals(cn.modulus, 0));
    assert(fequals(cn.angle, 0));
    printf("Test 'test_complex_num_empty' --> PASSED!\n");
}

// tests the functionality of the complex_print_rect() function
void test_complex_print_rect()
{
    complex_number_t cn;
    complex_num_init(&cn, 4, 3);
    // invalid input
    FILE *file1 = NULL;
    int ret1 = complex_print_rect(cn, file1);
    assert(ret1 == 1);
    // valid input
    FILE *file2 = fopen("tests/files/complex_num_rect.txt", "w+");
    complex_print_rect(cn, file2);
    fprintf(file2, "\n");
    fclose(file2);
    // read the file that was just written into, validate output
    FILE *file3 = fopen("tests/files/complex_num_rect.txt", "r");
    double real, imaginary;
    fscanf(file3, "%lf + j*(%lf)", &real, &imaginary);
    fclose(file3);
    assert(fequals(real, 4));
    assert(fequals(imaginary, 3));
    printf("Test 'test_complex_print_rect' --> PASSED!\n");
}

