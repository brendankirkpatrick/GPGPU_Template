#ifndef COMMON_EXAMPLE_UTILS_HPP
#define COMMON_EXAMPLE_UTILS_HPP

#include <iostream>

#include <hip/hip_runtime.h>

#define HIP_CHECK(condition)                                                                                   \
    {                                                                                                          \
        const hipError_t error = condition;                                                                    \
        if(error != hipSuccess)                                                                                \
        {                                                                                                      \
            std::cerr << "An error encountered: \"" << hipGetErrorString(error) << "\" at " << __FILE__ << ':' \
                      << __LINE__ << std::endl;                                                                \
            std::exit(-1);                                                                                     \
        }                                                                                                      \
    }

#endif// COMMON_EXAMPLE_UTILS_HPP
