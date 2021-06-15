#include "../common/common.h"
#include <cuda_runtime.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int idev = 0;
    cudaDeviceProp dev_prop;
    CHECK(cudaGetDeviceProperties(&dev_prop, idev));

    printf("Device %d: %s \n", idev, dev_prop.name);
    printf("Number of multiprocessors: %d \n", dev_prop.multiProcessorCount);
    printf("Total amount of shapred memory per block: %4.2f kb \n", dev_prop.sharedMemPerBlock / 1024.0);
    printf("Total amount of const memory: %4.2f kb\n", dev_prop.totalConstMem/1024.0);
    printf("Total number of registers available per block: %d\n", dev_prop.regsPerBlock);
    printf("Warp size: %d\n", dev_prop.warpSize);
    printf("Maximum number of threads per block: %d\n", dev_prop.maxThreadsPerBlock);
    printf("Maximum number of threads per multiprocess: %d\n", dev_prop.maxThreadsPerMultiProcessor);
    printf("Maximum number of warps per multiprocessor: %d\n", dev_prop.maxThreadsPerMultiProcessor/32);

    return EXIT_SUCCESS;

}
