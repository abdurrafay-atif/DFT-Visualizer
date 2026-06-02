#include "../include/app/app.h"

// THIS IS A FILE FOR FUNCTIONS WHICH ARE HELPER FUNCTIONS FOR THE FUNCTIONS IN APP_FUNCS.C

// constant representing the # of commands in the help_strings array of strings
const int num_commands = 21;

// help
char *help_strings[] = 
{
    "help --> Lists all possible commands\n", 
    "exit --> Stops the program\n", 
    "reset --> Resets state of program to initial arguments\n", 
    "save --> Adds the current vector to the list of vectors\n", 
    "num_vectors --> Prints the # of vectors saved\n", 
    "import [input file] --> Adds the specified vector to the list of vectors (fails if exceeding limit)\n", 
    "export [output file] [index] --> Exports the specified vector to the given file\n",
    "set [index] --> Sets the display vector to the vector at the specified index\n",
    "display --> outputs the complex vector\n",
    "list --> outputs all vectors in the vector list\n",
    "plot [height] [low] [high] --> prints the plot of the vector\n",
    "dft [zero-pad] --> applies the DFT with a zero-pad to the vector (0 for standard DFT)\n",
    "idft --> applies the Inverse DFT to the vector\n",
    "conj --> applies the conjugate function to the vector\n",
    "scale [Re{scaling_factor}] [Im{scaling_factor}] --> Scales the complex number by the specified factor\n",
    "add [index] --> Adds the current vector with the one at the specified index\n",
    "product [index] --> Applies element-by-element product with the one at the specified index\n",
    "convolution [index] --> Applies convolution of the vector with the one at the specified index\n",
    "circ_reverse --> Applies the circular reversal function to the vector\n",
    "circ_shift [shift] --> Applies the specified shift to the vector\n",
    "fourier_modulate [index] --> Applies fourier modulation to the vector\n",
};

// ensures that all input arguments follow the proper format
// also set the struct "arg_info" with the appropriate information
int validate_input_args(struct visualizer_info *info, char *argv[])
{
    // extract & validate the input file
    char *input_file = argv[1];
    if(access(input_file, F_OK))
    {
        printf("%s does not exist. please add it to your directory and try again.\n", input_file);
        return INPUT_FILE_NO_EXIST;
    }
    // extract output file (will be created if doesn't exist yet)
    char *output_file = argv[2];
    // extract & validate complex number format
    int complex_num_format = atoi(argv[3]);
    if(complex_num_format == 0)
    {
        printf("Complex Num Formats: 1 (RECT), 2 (POLAR), 3 (EXP) (Default: RECT)\n");
        printf("Note: Inserting '0' will lead to an error.\n");
        return FILE_TYPE_NON_INT;
    }
    // set struct fields
    info->input_file = input_file;
    info->output_file = output_file;
    info->complex_num_format = complex_num_format;
    return CORRECT_ARGS;
}

// returns the # of lines that are in the file 
// this is mainly used for counting length of a vector from file contents
int count_lines(FILE *file)
{
    // handle invalid input
    if(file == NULL)
    {
        return -1;
    }
    int count = 0;
    // loop to count # of complex numbers
    while(1)
    {
        int ret = fgetc(file);
        // break out of loop if at the end of file
        if(ret == EOF)
        {
            break;
        }
        // count # of new lines (same as # of complex numbers in file if formatted correctly)
        if(ret == '\n')
        {
            count++;
        }
    }
    return count;
}

// sets the specified vector based on the file given in vector form
// doesn't check for existence of file but does check that vector is properly set
cvector_t *cvector_set(char *filename, int format)
{
    // open input file
    FILE *input = fopen(filename, "r");
    // check if file exists
    if(input == NULL)
    {
        return NULL;
    }
    // obtain # of complex numbers via the count_lines() helper function
    int size = count_lines(input);
    // initialize the vector 
    cvector_t *vec = cvector_init_empty(size);
    // obtain vector from file now that size is known
    rewind(input);
    int ret = cvector_read(input, vec, format);
    // validate read
    if(ret != 0)
    {
        printf("please ensure your input file is in the correct format.\n");
        printf("each complex number must be listed in its own line.\n");
        printf("RECT: a + j*(b)\n");
        printf("POLAR: |a|∠b\n");
        printf("EXP: a*e^(j*(b))\n");
        return NULL;
    }
    fclose(input);
    return vec;
}

// prints all the help strings to the output file
int print_help(FILE *file)
{
    // validate input
    if(file == NULL)
    {
        return 1;
    }
    // loop through all the strings in the array of character points in app.h
    for(int command = 0; command < num_commands; command++)
    {
        fprintf(file, "%s", help_strings[command]);
    }
    return 0;
}

// removes the \n added by fgets()
void remove_new_line(char *output, char *input, int len)
{
    // if the end of the string has \n, change it to null terminator
    // this will make the string end here (duplicate \0)
    if(input[len] == '\n')
    {
        input[len] = '\0';
    }
    // copy to the output
    output = strncpy(output, input, len - 1);
}

// prints string until space occurs to the specified file
void print_string_before_space(FILE *file, char *str) 
{
    int c = 0;
    // print the string until a space bar is hit (or ARGSIZE limit is exceeded or at end of string)
    while(str[c] != '\0' && c < ARGSIZE && str[c] != ' ')
    {
        fprintf(file, "%c", str[c]);
        c++;
    }
}

// free()'s all material allocated during the program
void cleanup(struct visualizer_info info, FILE *output)
{
    // free the display vector
    cvector_free(info.vec);
    // free the vectors in the vector list
    for(int index = 0; index < info.num_vectors; index++)
    {
        cvector_free(info.vec_etc[index]);
    }
    // close the output file if it is not stdout
    if(output != stdout)
    {
        fclose(output);
    }
}