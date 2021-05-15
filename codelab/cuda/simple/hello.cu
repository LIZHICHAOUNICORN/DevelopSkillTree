#include <iostream>

__global__ void hello_world_GPU() {
  printf("hello world from GPU\n");
}

int main(int argc, char** argv) {
    printf("Hello world CPU\n");

    // Run kernel function.
    hello_world_GPU<<<1, 10>>>();

    // exiplicitly will explicitly destroy and clean up
    // all resources associated with current device 
    // with the current process.
    cudaDeviceReset();
    return 0;
}
