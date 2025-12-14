# Header files
set(HEADER_FILES
    common_hip.hpp
    )

# Source Files
set(SOURCE_FILES
   simple_nn.hip
    )

# Program entry (main fn)
set(PROGRAM_ENTRY
    )

# Set cache for GPU_RUNTIME type
set(GPU_RUNTIME "CUDA" CACHE STRING "Switches between HIP and CUDA")
set(GPU_RUNTIMES "HIP" "CUDA")
set_property(CACHE GPU_RUNTIME PROPERTY STRINGS ${GPU_RUNTIMES})
if(NOT "${GPU_RUNTIME}" IN_LIST GPU_RUNTIMES)
    set(ERROR_MESSAGE
        "GPU_RUNTIME is set to \"${GPU_RUNTIME}\".\nGPU_RUNTIME must be either HIP or CUDA."
    )
    message(FATAL_ERROR ${ERROR_MESSAGE})
endif()

# Verify that we can link to appropriate runtime
include(CheckLanguage)
check_language(${GPU_RUNTIME})
if(CMAKE_${GPU_RUNTIME}_COMPILER)
    enable_language(${GPU_RUNTIME})
    set(CMAKE_${GPU_RUNTIME}_STANDARD 20)
    set(CMAKE_${GPU_RUNTIME}_EXTENSIONS OFF)
    set(CMAKE_${GPU_RUNTIME}_STANDARD_REQUIRED ON)
else()
    set(ERROR_MESSAGE
        "GPU_RUNTIME is set to \"${GPU_RUNTIME}\".\nThe GPU_RUNTIME was unable to be found by CMake!"
    )
    message(FATAL_ERROR ${ERROR_MESSAGE})
endif()

# Set the directory where rocm libraries/includes can be found
if(WIN32)
    set(ROCM_ROOT
        "$ENV{HIP_PATH}"
        CACHE PATH
        "Root directory of the ROCm installation"
    )
else()
    set(ROCM_ROOT
        "/opt/rocm"
        CACHE PATH
        "Root directory of the ROCm installation"
    )
endif()
list(APPEND CMAKE_PREFIX_PATH "${ROCM_ROOT}")

add_library(${PROJECT_NAME}_lib ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_lib PRIVATE ${PROJECT_NAME}_settings)
set_target_properties(${PROJECT_NAME}_lib
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      OUTPUT_NAME ${PROJECT_NAME}
                      CUDA_SEPARABLE_COMPILATION ON # Enable separate compilation for CUDA files
                      CUDA_RESOLVE_DEVICE_SYMBOLS ON # Enable device linking to library target
                      #POSITION_INDEPENDENT_CODE ON
)
target_include_directories(${PROJECT_NAME}_lib PUBLIC
                           ${PROJECT_SOURCE_DIR}/src
                           ${PROJECT_SOURCE_DIR}/include
)
if(GPU_RUNTIME STREQUAL "CUDA")
    target_include_directories(${PROJECT_NAME}_lib SYSTEM PRIVATE "${ROCM_ROOT}/include")
    target_compile_definitions(${PROJECT_NAME}_lib PRIVATE __HIP_PLATFORM_NVIDIA__)

    # Set all source files to be compiled with CUDA
    file(GLOB_RECURSE HIP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.hip")
    foreach(hip_file ${HIP_SOURCES})
        set_source_files_properties(${hip_file} PROPERTIES LANGUAGE CUDA)
    endforeach()

elseif(GPU_RUNTIME STREQUAL "HIP")
    # When an ordinary C++ compiler is used (on the ROCm backend), it must be set up to link to the HIP runtime.
    find_package(HIP)
    target_compile_definitions(${PROJECT_NAME}_lib PRIVATE __HIP_PLATFORM_AMD__)
    target_link_libraries(${PROJECT_NAME}_lib PRIVATE hip::host)
endif()

if(PROGRAM_ENTRY)
    add_executable(${PROJECT_NAME} ${PROGRAM_ENTRY})
    set_target_properties(${PROJECT_NAME}_lib PROPERTIES OUTPUT_NAME dnn)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
endif()
