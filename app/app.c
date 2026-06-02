#include "../include/app/app.h"

// THIS IS AN INTERACTIVE DFT / IDFT VISUALIZER
// READ THE README.MD FILE FOR INFORMATION ON HOW TO USE
int main(int argc, char *argv[])
{
    // ensure that the user inputted all necessary arguments for the program
    if(argc != 4)
    {
        printf("Usage: ./bin/app [input file] [output file] [complex num format]\n");
        printf("Note: Type 'stdout' in [output field] to display program on terminal\n");
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
    // echo = 1 means the command line will also output (if being transmitted to another file)
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
        // if input is empty, skip
        if(len == 1)
        {
            continue;
        }
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
            if(info.num_vectors >= MAX_VECTORS)
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
            // check that vector limit hasn't been succeeded
            if(info.num_vectors >= MAX_VECTORS)
            {
                fprintf(output, "sorry, cannot exceed %d saved vectors.\n", MAX_VECTORS);
            }
            else
            {
                // extract input file from input
                char input_file[ARGSIZE];
                int ret = sscanf(buf, "%*s %s", input_file);
                // check that sscanf() extracted correct inputs
                if(ret != 1)
                {
                    fprintf(output, "failed to extract input file from user.\n");
                }
                else
                {
                    info.vec_etc[info.num_vectors] = cvector_set(input_file, info.complex_num_format);
                    if(info.vec_etc[info.num_vectors] != NULL)
                    {
                        fprintf(output, "successfully imported vector to index %d.\n", info.num_vectors);
                        info.num_vectors++;
                    }
                    else
                    {
                        fprintf(output, "failed to import vector to index %d.n", info.num_vectors);
                        fprintf(output, "please check that your input file exists and is in the correct format.\n");
                    }
                }
            }
        }
        else if(strncmp(buf, "export", 6) == 0)
        {
            char output_file[ARGSIZE];
            int index;
            int ret = sscanf(buf, "%*s %s %d", output_file, &index);
            if(ret != 2 || index < 0 || index >= info.num_vectors)
            {
                fprintf(output, "failed to extract arguments or user put incorrect / invalid arguments.\n");
                fprintf(output, "index must be within the bounds of the list of vectors.\n");
                fprintf(output, "enter 'list' to determine indices of vectors you have saved.\n");
            }
            else
            {
                FILE *export = fopen(output_file, "w+");
                cvector_write(export, *info.vec_etc[index], info.complex_num_format);
                fclose(export);
                fprintf(output, "vector at index %d successfully exported to file '%s'\n", index, output_file);
            }
        }
        else if(strncmp(buf, "set", 3) == 0)
        {
            // extract index from command line
            int index;
            int ret = sscanf(buf, "%*s %d", &index);
            // if ret != 1 or index out of bounds, something went wrong
            if(ret != 1 || index < 0 || index >= info.num_vectors)
            {
                fprintf(output, "input does not provide [index] or index is out-of-bounds.\n");
            }
            else // perform set
            {
                cvector_t *old = info.vec;
                info.vec = cvector_init(info.vec_etc[index]->vec, info.vec_etc[index]->size);
                cvector_free(old);
                fprintf(output, "vector successfully set to vector at index %d\n", index);
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
            int ret = sscanf(buf, "%*s %d %d %d", &height, &low, &high);
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
                    fprintf(output, "height must be a positive value.\n");
                    fprintf(output, "low & high must be within bounds of the vector.\n");
                    fprintf(output, "bounds of vector are 0 (inclusive) & vector size (exclusive).\n");
                }
            }
        }
        else if(strncmp(buf, "dft", 3) == 0) // must include zero-pad (even for standard DFT)
        {
            // extract the old vector
            cvector_t *old = info.vec;
            // obtain zero-pad (if it is given)
            int pad;
            int ret = sscanf(buf, "%*s %d ", &pad);
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
                fprintf(output, "IDFT failed.\n");
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
            if(ret != 2)
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
            if(ret != 1 || index < 0 || index >= info.num_vectors)
            {
                fprintf(output, "this command requires one integer entry [index of vector in list] as an argument.\n");
                fprintf(output, "index must be within the bounds of the list of vectors.\n");
                fprintf(output, "enter 'list' to determine indices of vectors you have saved.\n");
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
            if(ret != 1 || index < 0 || index >= info.num_vectors)
            {
                fprintf(output, "this command requires one integer entry [index of vector in list] as an argument.\n");
                fprintf(output, "index must be within the bounds of the list of vectors.\n");
                fprintf(output, "enter 'list' to determine indices of vectors you have saved.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_element_product(*info.vec, *info.vec_etc[index]);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to perform element by element product of the two vectors.\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "element by element product succeeded.\n");
                    cvector_free(old);
                }
            }
        }
        else if(strncmp(buf, "convolution", 11) == 0)
        {
            // obtain index argument
            int index;
            int ret = sscanf(buf, "%*s %d", &index);
            if(ret != 1 || index < 0 || index >= info.num_vectors)
            {
                fprintf(output, "this command requires one integer entry [index of vector in list] as an argument.\n");
                fprintf(output, "index must be within the bounds of the list of vectors.\n");
                fprintf(output, "enter 'list' to determine indices of vectors you have saved.\n");
            }
            else
            {
                // perform operation
                cvector_t *old = info.vec;
                info.vec = cvector_circ_convolve(*info.vec, *info.vec_etc[index]);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, "failed to perform circular convolution of the two vectors.\n");
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "circular convolution succeeded.\n");
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
        else if(strncmp(buf, "circ_shift", 10) == 0)
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
                    fprintf(output, "failed to perform circular shift by %d.\n", shift);
                    info.vec = old;
                }
                else
                {
                    fprintf(output, "circular shift by %d succeeded.\n", shift);
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
                info.vec = cvector_fourier_modulate(*info.vec, index);
                // check that operation worked (in case input file was corrupted)
                if(info.vec == NULL)
                {
                    fprintf(output, 
                        "failed to perform fourier modulation with fourier sinusoid at index %d.\n", 
                        index % info.vec->size);
                    info.vec = old;
                }
                else
                {
                    fprintf(output, 
                        "fourier modulation with fourier sinusoid at index %d succeeded.\n", 
                        index % info.vec->size);
                    cvector_free(old);
                }
            }
        }
        // argument does not exist
        else
        {
            print_string_before_space(output, buf);
            fprintf(output, ": command not found.\n");
        }
        // force output 
        fflush(output);
        // replace all input with spaces (to prevent prior inputs from interfering with current inputs)
        for(int c = 0; c < len; c++)
        {
            in[c] = ' ';
            buf[c] = ' ';
        }
    }
    cleanup(info, output);
    return 0; // no errors during program
}