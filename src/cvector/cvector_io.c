#include "../include/src/cvector.h"

// display the passed in vector in [] format
// complex number printing done as specified by format
int cvector_display(FILE *file, cvector_t v, int format)
{
    // handle invalid input
    if(file == NULL)
    {
        return 1;
    }
    // print vector in [] format
    fprintf(file, "Size: %d\n", v.size);
    fprintf(file, "Vector: [    ");
    for(int ele = 0; ele < v.size; ele++)
    {
        complex_write(file, v.vec[ele], format);
        fprintf(file, "    ");
    }
    fprintf(file, "]\n");
    return 0;
}

// writes the passed in vector into the specified file with each complex number listed in a new line
int cvector_write(FILE *file, cvector_t v, int format)
{
    // handle invalid input
    if(file == NULL)
    {
        return 1;
    }
    // write vector to the specified file
    for(int ele = 0; ele < v.size; ele++)
    {
        complex_write(file, v.vec[ele], format);
        fprintf(file, "\n");
    }
    return 0;
}

// reads the passed in file & obtains complex vector from it
// note: v should have already been initialized 
// note: v->size should already be defined (from a call to count_lines on *file)
int cvector_read(FILE *file, cvector_t *v, int format)
{
    // handle invalid input
    if(file == NULL || v == NULL)
    {
        return 1;
    }
    // read each complex number with complex_read() in the specified format
    for(int ele = 0; ele < v->size; ele++)
    {
        // attempt to read the complex number
        int ret = complex_read(file, &v->vec[ele], format);
        // check if reading failed (means incorrect format)
        if(ret != 0) 
        {
            return 1;
        }
    }
    return 0;
}

// plots the given cvector_t and writes it into the file given (can be standard output)
// PARAMETERS:
// @param height --> How high should the "max" element be represented in dots (must be >0)
// @param low --> Low cut-off index for plot (must be >= 0, < v.size, also <= high)
// @param high --> High cut-off index for plot (must be >= 0, < v.size, also >= low)
int cvector_plot(FILE *file, cvector_t v, int height, int low, int high)
{
    // handle invalid input
    if(file == NULL || height <= 0 || low < 0 || low >= v.size || low > high || high < 0 || high >= v.size)
    {
        return 1;
    }
    // print a line below the plot (length of vector * 3 + 6 spots for the vertical axis space)
    for(int line = 0; line < (high - low + 1) * 3 + 6; line++)
    {
        fprintf(file, "-");
    }
    fprintf(file, "\n");
    // parameters for plot
    double max_ele = cvector_max(v); // what the height represents
    double step = max_ele / height; // what each dot represents
    // start plotting
    for(int level = 0; level < height; level++)
    {
        // calculate the current height based on the maximum level & step
        double curr_height = max_ele - step * level;
        // for each element in vector, determine if it surpasses this level
        // if it does, print a dot for it. otherwise, print nothing for it
        for(int ele = low; ele <= high; ele++)
        {
            if(v.vec[ele].modulus >= curr_height)
            {
                fprintf(file, "*  ");
            }
            else
            {
                fprintf(file, "   ");
            }
        }
        // print representative value for this height
        fprintf(file, "|%.2lf", curr_height);
        fprintf(file, "\n");
    }
    // print a line below the plot (length of vector * 3 + 6 spots for the vertical axis space)
    for(int line = 0; line < (high - low + 1) * 3 + 6; line++)
    {
        fprintf(file, "-");
    }
    fprintf(file, "\n");
    // print indices (mod 100)
    for(int index = low; index <= high; index++)
    {
        fprintf(file, "%d ", index % 100);
        // add a space if it is a single-digit index
        if(index % 100 < 10)
        {
            fprintf(file, " ");
        }
    }
    fprintf(file, "\n");
    return 0;
}