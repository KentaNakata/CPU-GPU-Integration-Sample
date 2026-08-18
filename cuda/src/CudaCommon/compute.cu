#include "cudacommon/compute.h"

#include <cuda_runtime.h>
#include <cstdio>

__global__ void kernel(int* result)
{
    printf("Hello from kernel()\n");
    *result = 9;
}

int cudacommon_compute()
{
    int* d_result = nullptr;
    int  h_result = 0;

    cudaError_t err;

    err = cudaMalloc(&d_result, sizeof(int));
    if (err != cudaSuccess) {
        printf("cudaMalloc: %s\n", cudaGetErrorString(err));
        return -1;
    }

    kernel<<<1, 1>>>(d_result);

    err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("kernel: %s\n", cudaGetErrorString(err));
        cudaFree(d_result);
        return -2;
    }

    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        printf("cudaDeviceSynchronize: %s\n", cudaGetErrorString(err));
        cudaFree(d_result);
        return -3;
    }

    err = cudaMemcpy(&h_result, d_result, sizeof(int), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        printf("cudaMemcpy: %s\n", cudaGetErrorString(err));
        cudaFree(d_result);
        return -4;
    }

    cudaFree(d_result);
    return h_result;
}
