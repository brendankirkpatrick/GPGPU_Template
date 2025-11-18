# Header files
set(HEADER_FILES
    )

# Source files
set(SOURCE_FILES
    test_kernel.cpp
    )

# Fetch Content to include Catch2 testing
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

# Links to GPU runtime
enable_language(${GPU_RUNTIME})
set(CMAKE_${GPU_RUNTIME}_STANDARD 20)
set(CMAKE_${GPU_RUNTIME}_EXTENSIONS OFF)
set(CMAKE_${GPU_RUNTIME}_STANDARD_REQUIRED ON)

add_executable(UNIT_TEST ${SOURCE_FILES} ${HEADER_FILES})

# Unit test output bin in build directory
set_target_properties(UNIT_TEST PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(UNIT_TEST PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(
    UNIT_TEST
    INTERFACE ${PROJECT_NAME}_settings
    PRIVATE Catch2::Catch2WithMain
    ${PROJECT_NAME}_lib
)
