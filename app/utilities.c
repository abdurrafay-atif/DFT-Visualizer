#include "../include/app/app.h"

// THIS IS A FILE FOR FUNCTIONS WHICH ARE HELPER FUNCTIONS FOR THE FUNCTIONS IN APP_FUNCS.C

// returns the # of lines that are in the file 
// this is mainly used for counting length of a vector from file contents
int count_lines(FILE *file)
{
    // handle invalid input
    if(file == NULL)
    {
        return 1;
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