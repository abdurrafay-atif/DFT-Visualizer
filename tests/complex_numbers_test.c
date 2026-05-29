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
    test_complex_write_read_rect();
    test_complex_write_read_pol();
    test_complex_write_read_exp();
    test_complex_write_read();
    test_complex_scale();
    test_complex_add();
    test_complex_sub();
    test_complex_prod();
    test_complex_pow();
    test_complex_inv();
    test_complex_div();
    test_complex_conj();
    printf("-------------------------------------------------------------\n");
    printf("All tests in complex_numbers_test.c have passed!\n");
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

// tests the functionality of the complex_write_rect() & complex_read_rect() functions
void test_complex_write_read_rect()
{
    complex_number_t cn;
    complex_num_init(&cn, 4, 3);
    // invalid input
    FILE *file1 = NULL;
    int ret1 = complex_write_rect(file1, cn);
    assert(ret1 == 1);
    // valid input
    FILE *file2 = fopen("tests/files/complex_num_rect.txt", "w+");
    complex_write_rect(file2, cn);
    fprintf(file2, "\n");
    fclose(file2);
    // read the file that was just written into, validate output
    FILE *file3 = fopen("tests/files/complex_num_rect.txt", "r");
    complex_read_rect(file3, &cn);
    fclose(file3);
    assert(fequals(cn.real, 4));
    assert(fequals(cn.imaginary, 3));
    printf("Test 'test_complex_write_read_rect' --> PASSED!\n");
}

// tests the functionality of the complex_write_polar() function
void test_complex_write_read_pol()
{
    complex_number_t cn;
    complex_num_init(&cn, 4, 3);
    // invalid input
    FILE *file1 = NULL;
    int ret1 = complex_write_polar(file1, cn);
    assert(ret1 == 1);
    // valid input
    FILE *file2 = fopen("tests/files/complex_num_pol.txt", "w+");
    complex_write_polar(file2, cn);
    fprintf(file2, "\n");
    fclose(file2);
    // read the file that was just written into, validate output
    FILE *file3 = fopen("tests/files/complex_num_pol.txt", "r");
    complex_read_polar(file3, &cn);
    fclose(file3);
    assert(fequals(cn.modulus, 5.00));
    assert(fequals(cn.angle, 0.64));
    printf("Test 'test_complex_write_read_pol' --> PASSED!\n");
}

// tests the functionality of the complex_write_exp() function
void test_complex_write_read_exp()
{
    complex_number_t cn;
    complex_num_init(&cn, 4, 3);
    // invalid input
    FILE *file1 = NULL;
    int ret1 = complex_write_exp(file1, cn);
    assert(ret1 == 1);
    // valid input
    FILE *file2 = fopen("tests/files/complex_num_exp.txt", "w+");
    complex_write_exp(file2, cn);
    fprintf(file2, "\n");
    fclose(file2);
    // read the file that was just written into, validate output
    FILE *file3 = fopen("tests/files/complex_num_exp.txt", "r");
    double modulus, angle;
    fscanf(file3, "%lf*e^(j*(%lf))", &modulus, &angle);
    fclose(file3);
    assert(fequals(modulus, 5.00));
    assert(fequals(angle, 0.64));
    printf("Test 'test_complex_write_read_exp' --> PASSED!\n");
}

// tests the functionality of the complex_write() function
void test_complex_write_read()
{
    complex_number_t cn;
    complex_num_init(&cn, 4, 3);
    // write to the file
    FILE *file1 = fopen("tests/files/complex_num_all_forms.txt", "w+");
    int ret = complex_write_rect(file1, cn);
    assert(ret == 0);
    complex_write(file1, cn, RECT);
    fprintf(file1, "\n");
    complex_write(file1, cn, POLAR);
    fprintf(file1, "\n");
    complex_write(file1, cn, EXP);
    fprintf(file1, "\n");
    fclose(file1);
    // read the file
    FILE *file2 = fopen("tests/files/complex_num_all_forms.txt", "r");
    complex_read(file2, &cn, RECT);
    assert(fequals(cn.real, 4));
    assert(fequals(cn.imaginary, 3));
    complex_read(file2, &cn, POLAR);
    assert(fequals(cn.modulus, 5));
    assert(fequals(cn.angle, 0.643501));
    complex_read(file2, &cn, EXP);
    assert(fequals(cn.modulus, 5));
    assert(fequals(cn.angle, 0.643501));
    fclose(file2);
    printf("Test 'test_complex_write_read' --> PASSED!\n");
}

// tests the complex_scale() function
void test_complex_scale()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    int ret1 = complex_scale(NULL, cn1, 3);
    assert(ret1 == 1);
    int ret2 = complex_scale(&cn1, cn1, 4);
    assert(ret2 == 0);
    assert(fequals(cn1.real, 4*4));
    assert(fequals(cn1.imaginary, 3*4));
    assert(fequals(cn1.modulus, 5*4));
    assert(fequals(cn1.angle, atan2(3, 4)));
    printf("Test 'test_complex_scale' --> PASSED!\n");
}

// tests the complex_add() function
void test_complex_add()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_number_t cn2;
    complex_num_init(&cn2, 7, 6);
    int ret1 = complex_add(NULL, cn1, cn2);
    assert(ret1 == 1);
    complex_number_t res;
    int ret2 = complex_add(&res, cn1, cn2);
    assert(ret2 == 0);
    assert(fequals(res.real, 11));
    assert(fequals(res.imaginary, 9));
    assert(fequals(res.modulus, 14.2126704036));
    assert(fequals(res.angle, 0.68572951091));
    printf("Test 'test_complex_add' --> PASSED!\n");
}

// tests the complex_sub() function
void test_complex_sub()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_number_t cn2;
    complex_num_init(&cn2, 7, 6);
    complex_number_t res;
    complex_sub(&res, cn1, cn2);
    assert(fequals(res.real, -3));
    assert(fequals(res.imaginary, -3));
    assert(fequals(res.modulus, 4.24264068712));
    assert(fequals(res.angle, 3.92699081699));
    printf("Test 'test_complex_sub' --> PASSED!\n");
}

// tests the complex_prod() function
void test_complex_prod()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_number_t cn2;
    complex_num_init(&cn2, 7, 6);
    complex_number_t res;
    complex_prod(&res, cn1, cn2);
    assert(fequals(res.real, 10.0000000001));
    assert(fequals(res.imaginary, 44.9999999999));
    assert(fequals(res.modulus, 46.0977222865));
    assert(fequals(res.angle, 1.35212738092));
    printf("Test 'test_complex_prod' --> PASSED!\n");
}

// tests the complex_pow() function
void test_complex_pow()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_pow(&cn1, cn1, 4);
    assert(fequals(cn1.real, pow(5, 4) * cos(atan2(3, 4) * 4)));
    assert(fequals(cn1.imaginary, pow(5, 4) * sin(atan2(3, 4) * 4)));
    assert(fequals(cn1.modulus, pow(5, 4)));
    assert(fequals(cn1.angle, atan2(3, 4) * 4));
    printf("Test 'test_complex_pow' --> PASSED!\n");
}

// tests the complex_inv() function
void test_complex_inv()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_inv(&cn1, cn1);
    assert(fequals(cn1.real, pow(5, -1) * cos(atan2(3, 4) * -1)));
    assert(fequals(cn1.imaginary, pow(5, -1) * sin(atan2(3, 4) * -1)));
    assert(fequals(cn1.modulus, pow(5, -1)));
    assert(fequals(cn1.angle, atan2(3, 4) * -1 + 2 * M_PI));
    printf("Test 'test_complex_inv' --> PASSED!\n");
}

// tests the complex_div() function
void test_complex_div()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_number_t cn2;
    complex_num_init(&cn2, 7, 6);
    complex_number_t res;
    complex_div(&res, cn1, cn2);
    assert(fequals(res.real, 0.541176470588));
    assert(fequals(res.imaginary, -0.0352941176471));
    assert(fequals(res.modulus, 0.542326144547));
    assert(fequals(res.angle, 6.21806014385));
    printf("Test 'test_complex_div' --> PASSED!\n");
}

// tests the complex_conj() function
void test_complex_conj()
{
    complex_number_t cn1;
    complex_num_init(&cn1, 4, 3);
    complex_conj(&cn1, cn1);
    assert(fequals(cn1.real, 4));
    assert(fequals(cn1.imaginary, -3));
    assert(fequals(cn1.modulus, 5));
    assert(fequals(cn1.angle, atan2(3, 4) * -1 + 2 * M_PI));
    printf("Test 'test_complex_conj' --> PASSED!\n");
}