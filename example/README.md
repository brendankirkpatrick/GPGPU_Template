## Example Library Usage
This is an example file showing how to use the library. 
You will have to include the appropriate headers and link the library. 
An example CMake file is provided.

The example cli program takes in a space-separated list of values as well as a scaling factor.
The program then takes each of the inputted values and multiplies each one by the scaling factor, and outputs the results.

## Build
To build the program, run `cmake -S . -B build` to generate the cmake project and `cmake --build build` to build the program.

Within the CMakeLists.txt the appropriate GPU_RUNTIME linkage needs to be set (CUDA vs HIP), with one currently being commented out.
Choose whichever one the library is built for, with it being necessary for the respective HIP/CUDA buildkits to be installed.
The project also needs to include the appropriate headers and link the libhipDNN library (currently linked with relative path).
