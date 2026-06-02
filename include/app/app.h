#ifndef APP_H
#define APP_H

#include "unistd.h"
#include "strings.h"
#include "src/dft.h"

// limits
#define MAX_VECTORS             20
#define BUFSIZE                 2048
#define ARGSIZE                 2048

// error codes for arguments
#define CORRECT_ARGS            0
#define INCORRECT_NUM_ARGS      1
#define INPUT_FILE_NO_EXIST     2
#define FILE_TYPE_NON_INT       3
#define OUTPUT_FILE_NO_EXIST    4

// other error codes
#define FILE_VEC_INCORRECT      5

// struct consisting of information needed for the main program
struct visualizer_info
{
    // information from command line arguments
    char *input_file;
    char *output_file;
    int complex_num_format;
    int echo; // on if output not stdout
    // vector info
    cvector_t *vec; // input vector 
    cvector_t *vec_etc[MAX_VECTORS]; // other vectors (for computations)
    int num_vectors;
};

// utilities.c
int validate_input_args(struct visualizer_info *info, char *argv[]);
int count_lines(FILE *file);
cvector_t *cvector_set(char *filename, int complex_num_format); 
int print_help(FILE *file);
void remove_new_line(char *output, char *input, int len); // removes the \n added by fgets()
void print_string_before_space(FILE *file, char *str); // prints string until space occurs
void cleanup(struct visualizer_info info, FILE *output);

#endif