#include "../include/app/app.h"

// THIS IS AN INTERACTIVE DFT / IDFT VISUALIZER
// ARGUMENTS:
// 1. ./bin/app
// 2. [input file] 
// 3. [file type] (1 for input vector, 2 for sum of cosines, any other number defaults to 1)
// 4. [output file] ("stdout" --> standard output)
// 5. [complex num format] (if not included, defaults to RECT) 

// COMMANDS INCLUDED:
// help --> Lists all possible commands
// exit --> Stops the program
// reset --> Resets state of program to initial arguments
// import [file type] [input file] --> Sets the current vector to the one in the given file with the specified type
// export [output file] --> Exports the current vector to the given file 
// out [output file] --> Sets the output file for commands ran during the program
// format [format] --> Sets the format (0, 1, 2, any other number defaults to RECT)
// display --> prints the complex vector (calls the cvector_display() function)
// plot [height] [low] [high] --> prints the plot of the vector
// dft --> applies the DFT to the vector
// dft [zero-pad] --> applies the DFT with a zero-pad to the vector
// idft --> applies the Inverse DFT to the vector
// conj --> applies the conjugate function to the vector
// scale [Re{scaling_factor}] [Im{scaling_factor}] --> Scales the complex number by the specified factor
// add [file type] [input file] --> Adds the current vector with the one in the specified file
// product [file type] [input file] --> Applies element-by-element product with the one in the specified file
// convolution [file type] [input file] --> Applies convolution of the vector with the one in the specified file
// circ_reverse --> Applies the circular reversal function to the vector
// circ_shift [shift] --> Applies the specified shift to the vector
// fourier_modulate [index] --> Applies fourier modulation to the vector

// NOTES:
// Input Files must always start with /app/files/...
// Output Files also must always start with /app/files/...
// File Types: 1 (default), 2
// Complex Number Formats: 0 (RECT) --> DEFAULT, 1 (POLAR), 2 (EXPONENTIAL)
// MUST set Complex Number Format accordingly before setting input / output files
// FORMAT is saved, so ensure all complex number files are in the format you desire

// FILE TYPE 1
// Each Line Consists of Complex Number (Add New Line to Each)
// RECT: a + j*(b); a = real, b = imaginary
// POLAR: |a|∠b; a = modulus, b = angle (in radians)
// EXP: a*e^(j*(b)); a = modulus, b = angle (in radians)

// FILE TYPE 2
// Top Line Should Be: Number of Samples: %d (newline right after)
// Each Line Consists of Sinusoid (Cosine Form) (Add New Line to Each)
// FORMAT: A*cos((w)*n + p), A = Amplitude, w = Angular Frequency, p = Phase
int main()
{
    
    return 0;
}