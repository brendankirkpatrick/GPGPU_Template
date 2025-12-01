#include <iostream>
#include <span>

#include <hip/hip_runtime.h>

#include "common_hip.hpp"
#include "simple_nn.hpp"

/* Simple example code section*/

__global__ void scale(float* data, const float scalar, const size_t data_size)
{
    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx < data_size)
    {
        data[idx] *= scalar;
    }
}

__host__ int scale_by_constant(std::span<float> data, const float scalar)
{
    float* device_data{};

    // Note that we give the address of the pointer, not the pointer itself
    HIP_CHECK(hipMalloc(&device_data, data.size() * sizeof(float)));
    HIP_CHECK(hipMemcpy(device_data, data.data(), data.size() * sizeof(float), hipMemcpyHostToDevice));

    const int threadsPerBlock = 256;
    const int blocksPerGrid = (data.size() + threadsPerBlock - 1) / threadsPerBlock;

    scale<<<blocksPerGrid, threadsPerBlock>>>(device_data, scalar, data.size());

    // check after running device code for errors
    HIP_CHECK(hipGetLastError());

    HIP_CHECK(hipMemcpy(data.data(), device_data, data.size() * sizeof(float), hipMemcpyDeviceToHost));
    HIP_CHECK(hipFree(device_data));

    return 0;
}
