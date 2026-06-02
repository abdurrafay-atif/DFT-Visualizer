#include "../include/app/app.h"

// THIS IS AN INTERACTIVE DFT / IDFT VISUALIZER
// ARGUMENTS:
// 1. ./dft_visualizer
// 2. [input file] 
// 3. [output file] ("stdout" --> standard output)
// 4. [complex num format] (if not included, defaults to RECT) 

// COMMANDS INCLUDED:
// help --> Lists all possible commands
// exit --> Stops the program
// reset --> Resets vector to one from input file
// save --> Adds the current vector to the list of vectors 
// num_vectors --> Prints the # of vectors in the visualizer_info struct
// import [input file] --> Adds the specified vector to the list of vectors (fails if exceeding limit)
// export [output file] [index] --> Exports the specified vector to the given file 
// display --> prints the complex vector (calls the cvector_display() function)
// list --> prints all vectors in the vector list 
// plot [height] [low] [high] --> prints the plot of the vector
// dft [zero-pad] --> applies the DFT with a zero-pad to the vector (0 for standard DFT)
// idft --> applies the Inverse DFT to the vector
// conj --> applies the conjugate function to the vector
// scale [Re{scaling_factor}] [Im{scaling_factor}] --> Scales the complex number by the specified factor
// add [index] --> Adds the current vector with the one at the specified index
// product [index] --> Applies element-by-element product with the one at the specified index
// convolution [index] --> Applies convolution of the vector with the one at the specified index
// circ_reverse --> Applies the circular reversal function to the vector
// circ_shift [shift] --> Applies the specified shift to the vector
// fourier_modulate [index] --> Applies fourier modulation to the vector

// NOTES:
// It is reccommended to place input / output files in the "app/files" folder (though not required)
// Complex Number Formats: 1 (RECT) --> DEFAULT, 2 (POLAR), 3 (EXPONENTIAL)
// NOTE about Formats: Do not enter '0', this will return an error. Any other integer is fine
// MUST set Complex Number Format accordingly before setting input / output files
// COMPLEX FORMAT is saved, so ensure all complex number files are in the format you desire
// It is reccommended you choose one format & stick with it to avoid trouble

// FILE FORMAT
// Each Line Consists of Complex Number (Add New Line to Each)
// RECT: a + j*(b); a = real, b = imaginary
// POLAR: |a|∠b; a = modulus, b = angle (in radians)
// EXP: a*e^(j*(b)); a = modulus, b = angle (in radians)
int main(int argc, char *argv[])
{
    // ensure that the user inputted all necessary arguments for the program
    if(argc != 4)
    {
        printf("Usage: ./bin/app [input file] [output file] [complex num format]\n");
        printf("Complex Num Formats: 1 (RECT), 2 (POLAR), 3 (EXP) (Default: RECT)\n");
        return INCORRECT_NUM_ARGS;
    }
    // form struct consisting of information from command line arguments & current vectors
    struct visualizer_info info;
    // validate input arguments with a helper function
    int valid_args = validate_input_args(&info, argv);
    if(valid_args != CORRECT_ARGS)
    {
        return valid_args;
    }
    // set vector & validate success of setting vector
    info.vec = cvector_set(info.input_file, info.complex_num_format);
    if(info.vec == NULL)
    { // unsuccessful
        return FILE_VEC_INCORRECT;
    }
    info.num_vectors = 0;
    // open output file (if "stdout" then it is just standard output)
    FILE *output;
    if(strncmp(info.output_file, "stdout", 6) == 0)
    {
        info.echo = 0;
        output = stdout;
    }
    else
    {
        info.echo = 1;
        output = fopen(info.output_file, "w+");
    }
    // input line & buffer for input
    char in[BUFSIZE];
    char buf[BUFSIZE];
    // loop
    while(1)
    {
        // print command line
        fprintf(output, "DFT_VISUALIZER> ");
        // obtain input & its length
        fgets(in, BUFSIZE, stdin);
        int len = strlen(in);
        remove_new_line(buf, in, len);
        // echo user input to file if needed
        if(info.echo)
        {
            fprintf(output, "%s\n", buf);
        }
        // determine what the first arg is
        if(strncmp(buf, "help", 4) == 0)
        {
            print_help(output);
        }
        else if(strncmp(buf, "exit", 4) == 0)
        {
            break;
        }
        else if(strncmp(buf, "reset", 5) == 0)
        {
            cvector_t *old = info.vec;
            info.vec = cvector_set(info.input_file, info.complex_num_format);
            // check that cvector_set worked (in case input file was corrupted)
            if(info.vec == NULL)
            {
                fprintf(output, "failed to reset vector.\n");
                info.vec = old;
            }
            else
            {
                fprintf(output, "successfully reset vector.\n");
                cvector_free(old);
            }
        }
        else if(strncmp(buf, "save", 4) == 0)
        {
            // check that saving is possible
            if(info.num_vectors > MAX_VECTORS)
            {
                fprintf(output, "sorry, cannot exceed %d saved vectors.\n", MAX_VECTORS);
            }
            else
            {
                info.vec_etc[info.num_vectors] = cvector_init(info.vec->vec, info.vec->size);
                fprintf(output, "successfully saved current vector at index %d.\n", info.num_vectors);
                info.num_vectors++;
            }
        }
        else if(strncmp(buf, "num_vectors", 11) == 0)
        {
            fprintf(output, "Number of Vectors Saved: %d\n", info.num_vectors);
        }
        else if(strncmp(buf, "import", 6) == 0)
        {
            // extract input file from input
            char *input_file;
            int ret = sscanf(buf, "%*s %s", input_file);
            if(ret == 1)
            {
                fprintf(output, "failed to extract input file from user.\n");
            }
            else
            {
                int fail = cvector_set(input_file, info.complex_num_format);
                if(!fail)
                {
                    fprintf(output, "successfully saved current vector at index %d.\n", info.num_vectors);
                    info.num_vectors++;
                }
            }
        }
        else if(strncmp(buf, "export", 6) == 0)
        {
            char *output_file;
            int index;
            int ret = sscanf(buf, "%*s %s %d", output_file, &index);
            if(ret == 2 || index <= 0 || index >= info.num_vectors)
            {
                fprintf(output, "failed to extract arguments or user put incorrect / invalid arguments.\n");
                fprintf(output, "index must be within the bounds of the list of vectors.\n");
                fprintf(output, "enter 'num_vectors' to determine how many vectors you have saved.\n");
            }
            else
            {
                cvector_write(output, *info.vec_etc[index], info.complex_num_format);
                fprintf(output, "vector at index %d successfully exported to file '%s'\n", index, output_file);
            }
        }
        else if(strncmp(buf, "display", 7) == 0)
        {
            cvector_display(output, *info.vec, info.complex_num_format);
        }
        else if(strncmp(buf, "list", 4) == 0)
        {
            fprintf(output, "--------------\n");
            fprintf(output, "SAVED VECTORS\n");
            fprintf(output, "--------------\n");
            for(int index = 0; index < info.num_vectors; index++)
            {
                fprintf(output, "--------------\n");
                fprintf(output, "Index %d\n", index);
                fprintf(output, "--------------\n");
                cvector_display(output, *info.vec_etc[index], info.complex_num_format);
            }
            fprintf(output, "--------------\n");
        }
        else if(strncmp(buf, "plot", 4) == 0)
        {
            // extract args for the "plot" command
            int height, low, high;
            int ret = sscanf(buf, "%*s %d %d %d ", &height, &low, &high);
            // check that sscanf() extracted the input correctly (and input entered correctly)
            if(ret != 3)
            {
                fprintf(output, "vector plotting failed.\n");
            }
            else
            {
                int plot_fail = cvector_plot(output, *info.vec, height, low, high);
                // if the plot failed send message to user
                if(plot_fail)
                {
                    fprintf(output, "plot failed due to invalid arguments, please try again.\n");
                }
            }
        }
        else if(strncmp(buf, "dft", 3) == 0) // must include zero-pad (even for standard DFT)
        {
            // extract the old vector
            cvector_t *old = info.vec;
            // obtain zero-pad (if it is given)
            int pad;
            int ret = sscanf(buf, "%*s %d\n", &pad);
            // if ret != 1, something went wrong
            if(ret != 1)
            {
                fprintf(output, "need an integer for zero-pad (insert 0 for standard DFT)\n");
            }
            else
            {
                // determine which function to use
                info.vec = dft_zero_pad(*info.vec, pad);
                // check that dft() worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "DFT failed.\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "DFT succeeded.\n");
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "idft", 4) == 0)
        {
            cvector_t *old = info.vec;
            info.vec = idft(*info.vec);
            // check that operation worked (in case input file was corrupted)
            if(info.vec == NULL)
            {
                fprintf(output, "IDFT Failed.\n");
                info.vec = old;
            }
            else
            {
                fprintf(output, "IDFT succeeded.\n");
                cvector_free(old);
            }
        }
        else if(strncmp(buf, "conj", 4) == 0)
        {
            cvector_t *old = info.vec;
            info.vec = cvector_conj(*info.vec);
            // check that operation worked (in case input file was corrupted)
            if(info.vec == NULL)
            {
                fprintf(output, "failed to take conjugate of vector.\n");
                info.vec = old;
            }
            else
            {
                fprintf(output, "vector conjugate succeeded.\n");
                cvector_free(old);
            }
        }
        else if(strncmp(buf, "scale", 5) == 0)
        {
            // extract real & imaginary components from command line arguments
            double real, imaginary;
            int ret = sscanf(buf, "%*s %lf %lf", &real, &imaginary);
            if(ret != 1)
            {
                fprintf(output, 
                    "this command requires two double entries [real & imaginary parts of scale] as arguments.\n");
            }
            else
            {
                // form complex number
                complex_number_t cn;
                complex_num_init(&cn, real, imaginary);
                // form vector
                cvector_t *old = info.vec;
                info.vec = cvector_scale(*info.vec, cn);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to scale vector.\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "vector scale succeeded.\n");
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "add", 3) == 0)
        {
            // obtain index argument
            int index;
            int ret = sscanf(buf, "%*s %d", &index);
            if(ret != 1)
            {
                fprintf(output, "this command requires one double entry [index of vector in list] as an argument.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_add(*info.vec, *info.vec_etc[index]);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to add the two vectors.\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "vector addition succeeded.\n");
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "product", 7) == 0)
        {
            // obtain index argument
            int index;
            int ret = sscanf(buf, "%*s %d", &index);
            if(ret != 1)
            {
                fprintf(output, "this command requires one double entry [index of vector in list] as an argument.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_element_product(*info.vec, *info.vec_etc[index]);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to perform element by element product of the two vectors\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "element by element product succeeded\n");
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "convolution", 11) == 0)
        {
            // obtain index argument
            int index;
            int ret = sscanf(buf, "%*s %d", &index);
            if(ret != 1)
            {
                fprintf(output, "this command requires one double entry [index of vector in list] as an argument.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_circ_convolve(*info.vec, *info.vec_etc[index]);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to perform circular convolution of the two vectors\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "circular convolution succeeded\n");
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "circ_reverse", 12) == 0)
        {
            cvector_t *old = info.vec;
            info.vec = cvector_circ_reverse(*info.vec);
            // check that operation worked (in case input file was corrupted)
            if(info.vec == NULL)
            {
                fprintf(output, "failed to perform circular reversal of vector.\n");
                info.vec = old;
            }
            else
            {
                fprintf(output, "circular reversal succeeded.\n");
                cvector_free(old);
            }
        }
        else if(strncmp(buf, "circ_shift", 11) == 0)
        {
            // obtain index argument
            int shift;
            int ret = sscanf(buf, "%*s %d", &shift);
            if(ret != 1)
            {
                fprintf(output, "this command requires one integer entry [shift] as an argument.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_circ_shift(*info.vec, shift);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to perform circular shift by %d\n", shift);
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "circular shift by %d succeeded\n", shift);
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "fourier_modulate", 16) == 0)
        {
            // obtain index argument
            int index;
            int ret = sscanf(buf, "%*s %d", &index);
            if(ret != 1)
            {
                fprintf(output, "this command requires one integer entry [fourier index] as an argument.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_circ_shift(*info.vec, index);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, 
                        "failed to perform fourier modulation with fourier sinusoid at index %d\n", 
                        index % info.vec->size);
                    info.vec = old;
                }
                else
                {
                    fprintf(output, 
                        "fourier modulation with fourier sinusoid at index %d succeeded\n", 
                        index % info.vec->size);
                    cvector_free(old);
                }
            }
        }
        else
        {
            print_string_before_space(output, buf);
            fprintf(output, ": command not found.\n");
        }
        // force output 
        fflush(output);
    }
    // cleanup
    cleanup(info, output);
    return 0; // no errors during program
}