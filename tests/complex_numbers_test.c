#include <assert.h> // for testing only
#include "../include/src/complex.h"
#include "../include/tests/complex_numbers_test.h"

// keep track of # of tests (to show the tests are passing when new ones are added)
int num_tests_passed;

// tests all files in src/complex_numbers
int main()
{
    num_tests_passed = 0;
    test_define_rect_to_polar_both_positive();
    test_define_rect_to_polar_imaginary_negative();
    test_define_rect_to_polar_real_negative();
    test_define_rect_to_polar_both_negative();
    test_define_polar_to_rect();
    test_define_polar_to_rect_neg_mod();
    test_define_polar_to_rect_neg_angle();
    test_define_polar_to_rect_over_angle();
    test_complex_scale();
    test_complex_add();
    test_complex_sub();
    test_complex_prod();
    test_complex_pow();
    test_complex_div();
    test_complex_conj();
    printf("All %d tests were successful!\n", num_tests_passed);
    return 0;
}

void test_define_rect_to_polar_both_positive()
{
    complex_number_t c1;
    int ret = complex_num_init(&c1, 4, 3);
    assert(ret == 0);
    assert(c1.real == 4.0);
    assert(c1.imaginary == 3.0);
    assert(c1.modulus == sqrt(pow(4, 2) + pow(3, 2)));
    assert(c1.angle == atan2(3, 4));
    num_tests_passed++;
}

void test_define_rect_to_polar_imaginary_negative()
{
    complex_number_t c1;
    int ret = complex_num_init(&c1, 4, -3);
    assert(ret == 0);
    assert(c1.real == 4.0);
    assert(c1.imaginary == -3.0);
    assert(c1.modulus == sqrt(pow(4, 2) + pow(-3, 2)));
    assert(c1.angle == (atan2(-3, 4) + 2 * M_PI));
    num_tests_passed++;
}

void test_define_rect_to_polar_real_negative()
{
    complex_number_t c1;
    int ret = complex_num_init(&c1, -4, 3);
    assert(ret == 0);
    assert(c1.real == -4.0);
    assert(c1.imaginary == 3.0);
    assert(c1.modulus == sqrt(pow(-4, 2) + pow(3, 2)));
    assert(c1.angle == atan2(3, -4));
    num_tests_passed++;
}

void test_define_rect_to_polar_both_negative()
{
    complex_number_t c1;
    int ret = complex_num_init(&c1, -4, -3);
    assert(ret == 0);
    assert(c1.real == -4.0);
    assert(c1.imaginary == -3.0);
    assert(c1.modulus == sqrt(pow(-4, 2) + pow(-3, 2)));
    assert(c1.angle == (atan2(-3, -4) + 2 * M_PI));
    num_tests_passed++;
}

void test_define_polar_to_rect()
{
    complex_number_t c1;
    int ret = complex_num_rev_init(&c1, 4, 2.3);
    assert(ret == 0);
    assert(c1.modulus == 4.0);
    assert(c1.angle == 2.3);
    assert(c1.real = 4 * cos(2.3));
    assert(c1.imaginary == 4 * sin(2.3));
    num_tests_passed++;
}

void test_define_polar_to_rect_neg_mod()
{
    complex_number_t c1;
    int ret = complex_num_rev_init(&c1, -4, 2.3);
    assert(ret == 1);
    num_tests_passed++;
}

void test_define_polar_to_rect_neg_angle()
{
    complex_number_t c1;
    int ret = complex_num_rev_init(&c1, 4, -8.3);
    assert(ret == 0);
    assert(c1.modulus == 4.0);
    assert(c1.angle == (-8.3 + 4 * M_PI));
    assert(c1.real = 4 * cos((-8.3 + 4 * M_PI)));
    assert(c1.imaginary == 4 * sin((-8.3 + 4 * M_PI)));
    num_tests_passed++;
}

void test_define_polar_to_rect_over_angle()
{
    complex_number_t c1;
    int ret = complex_num_rev_init(&c1, 4, 13.3);
    assert(ret == 0);
    assert(c1.modulus == 4.0);
    assert(c1.angle == (13.3 - 4*M_PI));
    assert(c1.real = 4 * cos((13.3 - 4*M_PI)));
    assert(c1.imaginary == 4 * sin((13.3 - 4*M_PI)));
    num_tests_passed++;
}

void test_complex_scale()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    int ret1 = complex_scale(&c1, c1, 4);
    assert(ret1 == 0);
    assert(c1.real == 4*4);
    assert(c1.imaginary = 3*4);
    assert(c1.modulus == (sqrt(pow(4, 2) + pow(3, 2)) * 4));
    assert(c1.angle == atan2(3, 4));
    num_tests_passed++;
}

void test_complex_add()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    complex_number_t c2;
    complex_num_init(&c2, 7, 12);
    complex_number_t sum;
    int ret1 = complex_add(&sum, c1, c2);
    assert(ret1 == 0);
    assert(sum.real == 4 + 7);
    assert(sum.imaginary == 3 + 12);
    assert(sum.modulus = (sqrt(pow(4 + 7, 2) + pow(3 + 12, 2))));
    assert(sum.angle == atan2(3 + 12, 4 + 7));
    num_tests_passed++;
}

void test_complex_sub()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    complex_number_t c2;
    complex_num_init(&c2, 7, 12);
    complex_number_t sub;
    int ret1 = complex_subtract(&sub, c1, c2);
    assert(ret1 == 0);
    assert(sub.real == 4 - 7);
    assert(sub.imaginary == 3 - 12);
    assert(sub.modulus = (sqrt(pow(4 - 7, 2) + pow(3 - 12, 2))));
    assert(sub.angle == (atan2(3 - 12, 4 - 7) + 2 * M_PI));
    num_tests_passed++;
}

void test_complex_prod()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    complex_number_t c2;
    complex_num_init(&c2, 7, 12);
    complex_number_t prod;
    int ret1 = complex_multiply(&prod, c1, c2);
    assert(ret1 == 0);
    assert(prod.real == (c1.modulus * c2.modulus) * cos(c1.angle + c2.angle));
    assert(prod.imaginary == (c1.modulus * c2.modulus) * sin(c1.angle + c2.angle));
    assert(prod.modulus = (c1.modulus * c2.modulus));
    assert(prod.angle == (c1.angle + c2.angle));
    num_tests_passed++;
}

void test_complex_pow()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    complex_number_t power;
    int ret1 = complex_pow(&power, c1, 4);
    assert(ret1 == 0);
    assert(power.real == (pow(c1.modulus, 4) * cos(c1.angle * 4)));
    assert(power.imaginary == (pow(c1.modulus, 4) * sin(c1.angle * 4)));
    assert(power.modulus == pow(c1.modulus, 4));
    assert(power.angle == (c1.angle * 4));
    num_tests_passed++;
}

void test_complex_div()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    complex_number_t c2;
    complex_num_init(&c2, 7, 12);
    complex_number_t quot;
    int ret1 = complex_divide(&quot, c1, c2);
    assert(ret1 == 0);
    assert(quot.real == (c1.modulus / c2.modulus) * cos(c1.angle - c2.angle + 2 * M_PI));
    assert(quot.imaginary == (c1.modulus / c2.modulus) * sin(c1.angle - c2.angle + 2 * M_PI));
    assert(quot.modulus = (c1.modulus / c2.modulus));
    assert(quot.angle == ((c1.angle - c2.angle) + 2 * M_PI));
    num_tests_passed++;
}

void test_complex_conj()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    complex_number_t conj;
    int ret1 = complex_conjugate(&conj, c1);
    assert(ret1 == 0);
    assert(conj.real == c1.real);
    assert(conj.imaginary == -c1.imaginary);
    assert(conj.modulus == c1.modulus);
    assert(conj.angle == (-c1.angle + 2 * M_PI));
    num_tests_passed++;
}
