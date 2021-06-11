#include <cuda_runtime.h>
#include <iostream>

#include "../common/common.h"

int main(int argc, char** argv) {

  printf("%s Starting .. \n", argv[0]);

  int device_count = 0;
  cudaGetDeviceCount(&device_count);

  printf("Detected %d CUDA Capable device(s)\n", device_count);

  int dev = 0;
  int driver_version = 0;
  int runtime_version = 0;
  CHECK(cudaSetDevice(dev));
  
  cudaDeviceProp device_prop;
  CHECK(cudaGetDeviceProperties(&device_prop, dev));
  printf("Device %d \"%s\"\n", dev, device_prop.name);

  cudaDriverGetVersion(&driver_version);
  cudaRuntimeGetVersion(&runtime_version);
  printf("CUDA Driver Version / Runtime Version %d, %d\n", driver_version, runtime_version);
  return 0;
}
