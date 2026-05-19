#include <assert.h> // for testing only
#include "../include/complex_numbers/complex.h"
#include "../include/complex_numbers/complex_tests.h"

// tests the complex_define.c file
// takes in parameter for 
int main()
{
    test_define_rect_to_polar_both_positive();
    test_define_rect_to_polar_imaginary_negative();
    test_define_rect_to_polar_real_negative();
    test_define_rect_to_polar_both_negative();
    printf("All tests successful!\n");
    return 0;
}

void test_define_rect_to_polar_both_positive()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, 3);
    assert(c1.real == 4.0);
    assert(c1.imaginary == 3.0);
    assert(c1.modulus == sqrt(pow(4, 2) + pow(3, 2)));
    assert(c1.angle == atan2(3, 4));
}

void test_define_rect_to_polar_imaginary_negative()
{
    complex_number_t c1;
    complex_num_init(&c1, 4, -3);
    assert(c1.real == 4.0);
    assert(c1.imaginary == -3.0);
    assert(c1.modulus == sqrt(pow(4, 2) + pow(-3, 2)));
    assert(c1.angle == (atan2(-3, 4) + 2 * M_PI));
}

void test_define_rect_to_polar_real_negative()
{
    complex_number_t c1;
    complex_num_init(&c1, -4, 3);
    assert(c1.real == -4.0);
    assert(c1.imaginary == 3.0);
    assert(c1.modulus == sqrt(pow(-4, 2) + pow(3, 2)));
    assert(c1.angle == atan2(3, -4));
}

void test_define_rect_to_polar_both_negative()
{
    complex_number_t c1;
    complex_num_init(&c1, -4, -3);
    assert(c1.real == -4.0);
    assert(c1.imaginary == -3.0);
    assert(c1.modulus == sqrt(pow(-4, 2) + pow(-3, 2)));
    assert(c1.angle == (atan2(-3, -4) + 2 * M_PI));
}
