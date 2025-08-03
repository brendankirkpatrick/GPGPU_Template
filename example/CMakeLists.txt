# Requires at least Version 3.21 for HIP language support
cmake_minimum_required(VERSION 3.21)
project(example_dnn
		VERSION 1.0.0
		LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)

# Generate our executable with a target=project-name
add_executable(${PROJECT_NAME} main.cpp)

# Include header files used by the library
include_directories("../include")
# Link project to our DNN library if not installed system-wide
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../build/libhipGPGPU.a)

# Find the HIP package on your system and link to its runtime
#find_package(HIP REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE hip::host)

# Find the CUDA package on your system and link to its runtime
find_package(CUDAToolkit REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CUDA::cudart)
