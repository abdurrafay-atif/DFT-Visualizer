#include <assert.h> // for testing only
#include "../include/src/sinusoids.h"
#include "../include/tests/sinusoids_test.h"

// keep track of # of tests (to show the tests are passing when new ones are added)
int num_tests_passed;
const double EPSILON = 1e-9; // for floating point comparisons

// checks if two floating point numbers are very close in equality
int fequals(double a, double b) 
{
    return fabs(a - b) < EPSILON;
}

int main()
{
    printf("Running sinusoids_test.c ...\n");
    num_tests_passed = 0;
    test_construct_sinusoid_errors();
    test_construct_sinusoid_no_phase();
    test_construct_sinusoid_inc_phase();
    test_sinusoid_addition();
    printf("All %d tests were successful!\n", num_tests_passed);
    return 0;
}

void test_construct_sinusoid_errors()
{
    sinusoid_t *s1 = construct_sinusoid(-1, 0, 0, 1);
    sinusoid_t *s2 = construct_sinusoid(5, 0, 0, 0);
    assert(s1 == NULL && s2 == NULL);
    num_tests_passed++;
}

void test_construct_sinusoid_no_phase()
{
    sinusoid_t *s1 = construct_sinusoid(1, (M_PI / 3) * 2, 0, 6);
    assert(s1 != NULL);
    assert(s1->amplitude == 1);
    assert(s1->ang_freq == (M_PI / 3) * 2);
    assert(s1->phase == 0);
    assert(s1->num_samples == 6);
    assert(s1->samples[0].real == 1 && s1->samples[0].imaginary == 0);
    assert(fequals(s1->samples[1].real, -0.5) && fequals(s1->samples[1].imaginary, sqrt(3) / 2));
    assert(fequals(s1->samples[2].real, -0.5) && fequals(s1->samples[2].imaginary, -sqrt(3) / 2));
    assert(s1->samples[3].real == 1 && s1->samples[3].imaginary == 0);
    assert(fequals(s1->samples[4].real, -0.5) && fequals(s1->samples[4].imaginary, sqrt(3) / 2));
    assert(fequals(s1->samples[5].real, -0.5) && fequals(s1->samples[5].imaginary, -sqrt(3) / 2));
    sinusoid_free(s1);
    num_tests_passed++;
}

void test_construct_sinusoid_inc_phase()
{
    sinusoid_t *s1 = construct_sinusoid(5, (M_PI / 3) * 2, (M_PI / 3) * 1, 6);
    assert(s1 != NULL);
    assert(s1->amplitude == 5);
    assert(s1->ang_freq == (M_PI / 3) * 2);
    assert(s1->phase == (M_PI / 3) * 1);
    assert(s1->num_samples == 6);
    for(int sample = 0; sample < 6; sample++)
    {
        assert(s1->samples[sample].modulus == 5);
        assert(s1->samples[sample].angle = normalize_angle((M_PI / 3) * 2 * sample + (M_PI / 3)));
    }
    sinusoid_free(s1);
    num_tests_passed++;
}

void test_sinusoid_addition()
{
    sinusoid_t *s1 = construct_sinusoid(5, (M_PI / 3) * 2, (M_PI / 3) * 1, 6);
    sinusoid_t *s2 = construct_sinusoid(3, (M_PI / 3) * 2, (M_PI / 3) * 3, 6);
    sinusoid_t *sum = add_sinusoids(*s1, *s2);
    assert(fequals(sum->amplitude, 4.35889894352));
    assert(fequals(sum->phase, 1.6857572473));
    sinusoid_free(s1);
    sinusoid_free(s2);
    sinusoid_free(sum);
    num_tests_passed++;
}