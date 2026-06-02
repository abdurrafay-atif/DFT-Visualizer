This application is a C terminal-based program where the user can input a complex vector and manipulate the vector using various signal processing tools. These tools are described in detail below:

# Complex Numbers
## Defining
* All complex numbers consist of four fields: Real, Imaginary, Modulus, Angle (either integer or double).
    * Real --> The real part of the complex number.
    * Imaginary --> The imaginary part of the complex number (the part multiplied by j).
    * Modulus --> The distance between (Real, Imaginary) and the origin.
    * Angle --> The angle the complex number makes with the origin in radians.
        * Angle is always defined between 0 (inclusive) & 2 * PI (exclusive). If somehow a value is given outside these bounds, it is normalized to within the bounds.
* All 4 parts are necessary for performing complex number arithmetic with ease.
* Complex Numbers can be defined using either the rectangular form (Real, Imaginary) or Polar Form (Modulus, Angle).

## I/O
* Complex Numbers take 3 Forms:
    * Rectangular Form (1 in CMD Args) --> Real + j*(Imaginary).
    * Polar Form (2 in CMD Args) --> |Modulus|∠Angle.
    * Exponential Form (3 in CMD Args) --> Modulus* e^(j*(Angle)) [note: there should NOT be a space between * & e, it is just there due to README.md formatting].
* Complex Numbers must be in the above forms for the program to work.
* It is recommended while using this program to stick to only one form during any one session, rather than constantly switch between forms.

## Arithmetic
* The following arithmetic operations on complex numbers are supported by this application (all may not necessarily be used in the main program).
    * Scaling (By Real Number).
    * Addition.
    * Subtraction.
    * Product.
    * Quotient.
    * Power.
    * Inverse. (|Modulus|^-1)
    * Conjugate. (Real + j*(Imaginary) --> Real - j*(Imaginary))

# Sinusoids
* Complex sinusoids are complex vectors which take the form A*cos(w * n + p) for some amount of samples
    * A = Amplitude.
    * w = Angular Frequency.
    * n = Sample.
    * p = Phase.
* The main purpose of this is to form the Fourier Sinusoid, which comes in the form e^(j * w * n).
* The Fourier Sinusoid is used in the DFT, Inverse DFT, & Fourier Modulation of complex vectors.

# Complex Vectors
## Defining
* Complex Vectors can be defined either as empty, or based on an already existing array of complex numbers.

## I/O
* Complex Vectors must be in the following format for I/O operations to work on them:
```
CN1
CN2
CN3
...
CNX

```
* CN1-X must be formatted based on the convention of complex numbers you desire (RECT, POLAR, EXP).
* There MUST be a new line at the end, or the last complex number will not register.

## Operations / Transformations
NOTE: To learn more about certain operations, it may be worthwhile to do some research online on them.
* Operations Included:
    * Conjugate
    * Addition
    * Element by Element Product
    * Circular Convolution 
* Calculations Included:
    * Max Element
    * Sum of Elements
    * Dot Product
* Transformations Included
    * Circular Reversal
    * Circular Shift
    * Fourier Modulation

# Discrete Fourier Transform (DFT)
* Some portion of the above tools are used to compute the DFT, DFT with zero-pad, & the Inverse DFT.
* The algorithm used is not necessarily the most efficient, but is enough for educational purposes, and the source code can always be modified to use the efficient version if one wishes to do such.
* The basic idea of the DFT is that it takes a time-domain signal and extracts its frequency contents. This allows one to obtain the frequencies of a transmitted signal, which has incredible applications in many technological areas of study. 

# Main Program
## Setting Up the Application:
* git clone https://github.com/abdurrafay-atif/DFT-Visualizer
* cd DFT-Visualizer
* make app
* ./dft-visualizer [input_file] [output_file] [complex num format] (explained below)
## Functionality
### Command Line Arguments
* The program requires all 3 of the following arguments in the correct order:
    * Input File --> This is the file where the input vector is obtained. You can check that your vector got successfully extracted from the input file by typing the 'display' command in the interactive program
        * The input file MUST be in the project directory. It is reccomended to place all files under the 'files' folder so you know where to find them.
        * The input file must also have the correct format, and the format for complex numbers must match with your choice of complex num format in the third argument.
    * Output File --> This is the file where all program output will redirect to. If you type 'stdout' it will lead to the output being displayed to the terminal.
        * The output file is created during the program, or overwritten if it already exists (again, it is recommended to place all files in the 'files' folder)
    * Complex Number Format --> Either RECT (1, or any non-0 number != 2, 3), POLAR (2), EXPONENTIAL (3)
        * DO NOT input 0 here, this will lead to program error (due to the way the atoi() function works)
### Setup to Main Program
* The program consists of a struct which holds all program information
    * Input File
    * Output File
    * Complex Number Format
    * Command Echo'ing 
    * Display Vector
    * Vector List (for performing operations)
        * Note that there is a cap to the amount of vectors that can be saved. You can alter this by changing the value of MAX_VECTORS in the file 'app.h'
    * Number of Saved Vectors (use 'num_vectors' to display this... it is the length of the above list)
### Loop
* Like most command line loops (such as in a standard terminal), there is a series of commands you can type with correct arguments which will lead to changes in state of the program. These commands are described in detail below.
## Commands
### Basic Commands
* help --> Lists all the commands available
* exit --> Exits the program (note after exit, all allocated material is released)
### Vector Imports / Exports
* reset --> Sets the current vector back to its state at the start of the program
    * This is useful if you want to test out various operations on a specific vector without needing to restart the program.
    * This is possible as the initial input file is saved during the program.
    * Note that if you change the input file while the program is running, this command won't work as intended, so please perform any specific changes to your vector in different files.
* save
    * Saves the current stored vector to the vector list (this fails if already at vector limit)
* import [input file]
    * Imports the vector stored in the given file to the vector list (again, fails if already at vector limit)
    * The vector is simply appended to the end of the vector list
* export [output file] [index]
    * Writes the contents of the vector at the given index of the list to the given output file
    * To determine the index for the vector desired, use the 'list' command
* set [index]
    * Sets the current vector to the vector at the specified index in the list.
    * Note that the index must be within bounds (this is true for any command requiring an index to the list). Please check which indices are filled out using the 'list' command
### Visual Tools
* display
    * Writes out the current vector (in [] form) & its size.
* list
    * Writes out all saved vectors (in [] form) & their sizes + their indexes in the list
    * This is useful for when you want to use these vectors to perform various operations
* plot [height] [low] [high]
    * This generates a plot of the modulus portion of all complex number components of the current vector
    * Example of a plot can be seen below (this is based on the 'input.txt' given under the 'files' folder):
```
./dft_visualizer files/input.txt stdout 1
DFT_VISUALIZER> plot 10 0 13
------------------------------------------------
                              *           |42.01
                              *           |37.81
                              *           |33.61
                              *  *  *     |29.41
                              *  *  *     |25.21
            *           *     *  *  *     |21.01
            *           *  *  *  *  *     |16.80
            *           *  *  *  *  *  *  |12.60
      *     *           *  *  *  *  *  *  |8.40
*  *  *  *  *     *  *  *  *  *  *  *  *  |4.20
------------------------------------------------
0  1  2  3  4  5  6  7  8  9  10 11 12 13 
DFT_VISUALIZER> dft 0
DFT succeeded.
DFT_VISUALIZER> plot 10 0 13
------------------------------------------------
                                 *        |114.71
                                 *        |103.24
         *                       *     *  |91.77
         *  *                 *  *     *  |80.30
         *  *           *  *  *  *  *  *  |68.83
*        *  *  *     *  *  *  *  *  *  *  |57.36
*        *  *  *  *  *  *  *  *  *  *  *  |45.88
*  *     *  *  *  *  *  *  *  *  *  *  *  |34.41
*  *     *  *  *  *  *  *  *  *  *  *  *  |22.94
*  *  *  *  *  *  *  *  *  *  *  *  *  *  |11.47
------------------------------------------------
0  1  2  3  4  5  6  7  8  9  10 11 12 13  
DFT_VISUALIZER> exit
```
### Operations (DFT, Arithmetic, Transformations)
* dft [zero-pad]
    * Performs the DFT on the current vector.
    * MUST include a zero-pad (do 0 for the standard DFT)
* idft
    * Performs the Inverse DFT on the current vector
* conj
    * Applys the conjugate operation to the vector (takes the negative of each imaginary component)
* scale [Re{scaling factor}] [Im{scaling factor}]
    * Performs a scale of the current vector by complex number 'Real + j*(Imaginary)'
    * Must include BOTH parts of scaling factor (set Im{scaling factor} to 0 to simply scale by real part)
* add [index]
    * Performs addition of the current vector & the vector at the specified index (if valid)
    * Note that both vectors must be of the same length
* product [index]
    * Performs product of current vector & the vector at the specified index (if valid)
    * Note that both vectors must be of the same length
* convolution [index]
    * Performs circular convolution operation on current vector & the vector at the specified index (if valid)
    * Both vectors do not necessarily need to be of the same length
* circ_reverse
    * Performs the circular reversal operation on the current vector 
* circ_shift [shift]
    * Performs the circular shift operation on the current vector by the specified shift.
* fourier_modulate [index]
    * Performs the fourier modulation operation on the current vector with the fourier sinsuoid at the index specified (note that if an out-of-bounds index is given, it simply defaults to its modulo)

# Handling Errors
If you are using this program and you notice an error, do the following:
* Take a screenshot of what the error is as proof of existence.
* Try to fix the error.
* Run 'make test' to make sure your fix did not affect the output (only necessary if you edit files under the 'src' directory).
* Make a pull request with the screenshot given.

# Adding Features
* If you desire for a feature to be added, let me know and I can add it (if you have a function which you want to implement, place it under src/other with the necessary header files and make a pull request).
* If I accept your pull request, I will place the function where necessary in the program alongside whatever feature you want to implement (usually a command you desire).
* Note that I may not insert just any feature, as some features may require a lot of work for little gain, may be unnecessary, or may not fit with the goal of the program.
