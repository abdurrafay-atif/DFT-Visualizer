This application is a C terminal-based program where the user can input a complex vector and manipulate the vector using various signal processing tools. These tools are described in detail below:

# Complex Numbers
## Defining
* All complex numbers consist of four fields: Real, Imaginary, Modulus, Angle (either integer or double)
* * Real --> The real part of the complex number 
* * Imaginary --> The imaginary part of the complex number (the part multiplied by j)
* * Modulus --> The distance between (Real, Imaginary) and the origin
* * Angle --> The angle the complex number makes with the origin in radians
* * * Angle is always defined between 0 (inclusive) & 2 * PI (exclusive). If somehow a value is given outside these bounds, it is normalized to within the bounds
* All 4 parts are necessary for performing complex number arithmetic with ease
* Complex Numbers can be defined using either the rectangular form (Real, Imaginary) or Polar Form (Modulus, Angle)

## I/O
* Complex Numbers take 3 Forms:
* * Rectangular Form (1 in CMD Args) --> Real + j*(Imaginary)
* * Polar Form (2 in CMD Args) --> |Modulus|∠Angle
* * Exponential Form (3 in CMD Args) --> Modulus* e^(j*(Angle)) [note: there should NOT be a space between * & e, it is just there due to README.md formatting]
* Complex Numbers must be in the above forms for the program to work.
* It is recommended while using this program to stick to only one form during any one session, rather than constantly switch between forms.

## Arithmetic
* The following arithmetic operations on complex numbers are supported by this application (all may not necessarily be used in the main program)
* * Scaling (By Real Number)
* * Addition 
* * Subtraction
* * Product
* * Quotient
* * Power
* * Inverse
* * Conjugate

Setting Up the Application:
git clone https://github.com/abdurrafay-atif/DFT-Visualizer
cd DFT-Visualizer
make app
./dft-visualizer [args] (explained above)