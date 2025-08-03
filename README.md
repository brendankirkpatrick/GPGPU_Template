# GPGPU Template
Simple template for exploring general purpose GPU programming (GPGPU).
The template supports creating static libraries and executables.
It also includes an example project setup demonstrating how to link to the generated library (HIP or CUDA).

## Requirements
To compile/use the library you need to have [HIP installed](https://rocm.docs.amd.com/projects/HIP/en/latest/install/install.html). The installation depends on your version of OS/Linux version. HIP is also capable of cross compiling to CUDA, but requires the CUDA toolkit to also be installed.

## Building/Testing
The project uses CMake as a build system. 
To create the cmake config, you can run cmake and select your runtime (HIP/CUDA):
```bash
cmake -S . -B build -DGPU_RUNTIME=CUDA
```
To build the project and run any tests, you can use the *run script* `run.sh`.

The template is based off of my [generic CMake template](https://github.com/brendankirkpatrick/CMake_Template) that also provides other features like warnings/address sanitization.
These features may or may not work when used in conjunction with HIP.

## Future Ideas
* Dockerize build process
* Instead of compiling for each GPU individually, it would be cool to dynamically load the required libraries at runtime based on GPU detection.
* Add Python bindings.

