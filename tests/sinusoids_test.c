#include <assert.h> // for testing only
#include "../include/src/sinusoids.h"
#include "../include/tests/sinusoids_test.h"

const double EPSILON = 1e-6; // for floating point comparisons

// checks if two floating point numbers are very close in equality
// due to the usage of floating point numbers in complex numbers, this is necessary for testing
int fequals(double a, double b) 
{
    return fabs(a - b) < EPSILON;
}

// tests all files associated with the sinusoid_t struct
int main()
{
    printf("-------------------------------------------------------------\n");
    printf("Running sinusoids_test.c\n");
    printf("-------------------------------------------------------------\n");
    test_construct_sinusoid_error();
    test_construct_sinusoid_empty();
    test_construct_sinusoid_no_phase();
    test_construct_sinusoid_with_phase();
    test_read_sinusoid();
    printf("-------------------------------------------------------------\n");
    printf("All tests in sinusoids_test.c have passed!\n");
    printf("-------------------------------------------------------------\n\n");
    return 0;
}

// tests that the construct_sinusoid() method returns 1 upon error
void test_construct_sinusoid_error()
{
    sinusoid_t *error1 = construct_sinusoid(-1, 0, 0, 1);
    assert(error1 == NULL);
    sinusoid_t *error2 = construct_sinusoid(-2, 0, 0, 1);
    assert(error2 == NULL);
    sinusoid_t *error3 = construct_sinusoid(5, 0, 0, 0);
    assert(error3 == NULL);
    sinusoid_t *error4 = construct_sinusoid(5, 0, 0, -1);
    assert(error4 == NULL);
    printf("Test 'test_construct_sinusoid_error' --> PASSED!\n");
}

// tests the construct_sinusoid() method on empty parameters (ang_freq = 0, phase = 0)
void test_construct_sinusoid_empty()
{
    sinusoid_t *empty = construct_sinusoid(0, 0, 0, 4);
    assert(fequals(empty->amplitude, 0));
    assert(fequals(empty->ang_freq, 0));
    assert(fequals(empty->phase, 0));
    assert(fequals(empty->num_samples, 4));
    for(int ele = 0; ele < empty->num_samples; ele++)
    {
        assert(fequals(empty->samples[ele].real, 0));
        assert(fequals(empty->samples[ele].imaginary, 0));
        assert(fequals(empty->samples[ele].modulus, 0));
        assert(fequals(empty->samples[ele].angle, 0));
    }
    sinusoid_free(empty);
    printf("Test 'test_construct_sinusoid_empty' --> PASSED!\n");
}

// tests the construct_sinusoid() method on a complex sinusoid with no phase component
void test_construct_sinusoid_no_phase()
{
    double ang_freq = (2.0 * M_PI * 2.0) / 6.0;
    sinusoid_t *empty = construct_sinusoid(1, ang_freq, 0, 6);
    assert(fequals(empty->amplitude, 1));
    assert(fequals(empty->ang_freq, ang_freq));
    assert(fequals(empty->phase, 0));
    assert(fequals(empty->num_samples, 6));
    for(int ele = 0; ele < empty->num_samples; ele++)
    {
        assert(fequals(empty->samples[ele].modulus, 1));
        assert(fequals(empty->samples[ele].angle, normalize_angle(ang_freq * ele)));
    }
    sinusoid_free(empty);
    printf("Test 'test_construct_sinusoid_no_phase' --> PASSED!\n");
}

// tests the construct_sinusoid() method on a complex sinusoid with a phase component
// also tests the construct_sinusoid() method with a larger amplitude & different # of samples
void test_construct_sinusoid_with_phase()
{
    double ang_freq = (2.0 * M_PI * 2.0) / 6.0;
    double phase = (M_PI * 2.0) / 3.0;
    sinusoid_t *empty = construct_sinusoid(5, ang_freq, phase, 9);
    assert(fequals(empty->amplitude, 5));
    assert(fequals(empty->ang_freq, ang_freq));
    assert(fequals(empty->phase, phase));
    assert(fequals(empty->num_samples, 9));
    for(int ele = 0; ele < empty->num_samples; ele++)
    {
        assert(fequals(empty->samples[ele].modulus, 5));
        assert(fequals(empty->samples[ele].angle, normalize_angle(ang_freq * ele + phase)));
    }
    sinusoid_free(empty);
    printf("Test 'test_construct_sinusoid_with_phase' --> PASSED!\n");
}

// tests the read_sinusoid() method
void test_read_sinusoid()
{
    double amplitude = 4, ang_freq = 4.4, phase = 3.9;
    FILE *file = fopen("tests/files/complex_sinusoid.txt", "r");
    assert(file != NULL);
    sinusoid_t *sin = read_sinusoid(file, 6);
    assert(sin != NULL);
    assert(fequals(sin->amplitude, amplitude));
    assert(fequals(sin->ang_freq, ang_freq));
    assert(fequals(sin->phase, phase));
    assert(fequals(sin->num_samples, 6));
    for(int ele = 0; ele < sin->num_samples; ele++)
    {
        assert(fequals(sin->samples[ele].modulus, amplitude));
        assert(fequals(sin->samples[ele].angle, normalize_angle(ang_freq * ele + phase)));
    }
    sinusoid_free(sin);
    fclose(file);
    printf("Test 'test_read_sinusoid' --> PASSED!\n");
}