#include "../include/app/app.h"

// THIS IS AN INTERACTIVE DFT / IFFT VISUALIZER
// ARGUMENTS:
// 1. ./bin/app
// 2. [input file] 
// 3. [file type] (1 for input vector, 2 for sum of cosines, any other number defaults to 1)
// 4. [output file] ("stdout" --> standard output)
// 5. [complex num format] (if not included, defaults to RECT) (this is optional if [file type] = 2)

// COMMANDS INCLUDED:
// help --> Lists all possible commands
// exit --> Stops the program
// set [file type] [input file] --> Sets the current vector to the one in the given file with the specified type
// out [output file] --> Sets the output file
// format [format] --> Sets the format (0, 1, 2, any other number defaults to RECT)
// print --> prints the complex vector
// plot --> prints the plot of the vector
// dft --> applies the DFT to the vector
// dft [zero-pad] --> applies the DFT with a zero-pad to the vector
// idft --> applies the IDFT to the vector
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

// FILE TYPE 1
// Each Line Consists of Complex Number (Add New Line to Each)
// RECT: a + j*(b); a = real, b = imaginary
// POLAR: |a|∠b; a = modulus, b = angle (in radians)
// EXP: a*e^(j*(b)); a = modulus, b = angle (in radians)

// FILE TYPE 2
// Each Line Consists of Sinusoid (Cosine Form) (Add New Line to Each)
// FORMAT: A*cos((w)*n + p), A = Amplitude, w = Angular Frequency, p = Phase
int main()
{
    return 0;
}