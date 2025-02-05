#include "../common/common.h"
#include <stdio.h>
#include <cuda_runtime.h>


__global__ void warmingup(float *c) {
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  float ia, ib;
  ia = ib = 0.0f;
  if ((tid / warpSize) % 2 == 0) {
    ia = 100.0f;
  } else {
    ib = 200.0f;
  }
  c[tid] = ia + ib;
}

__global__ void mathKernel1(float *c) {
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  float ia, ib;
  ia = ib = 0.0f;
  if (tid % 2 == 0) {
    ia = 100.0f;
  } else {
    ib = 200.0f;
  }
  c[tid] = ia + ib;

}

__global__ void mathKernel2(float *c) {
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  float ia, ib;
  ia = ib = 0.0f;
  if ((tid/warpSize) % 2 == 0) {
    ia = 100.0f;
  } else {
    ib = 200.0f;
  }
  c[tid] = ia + ib;

}

__global__ void mathKernel3(float *c) {
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  float ia, ib;
  ia = ib = 0.0f;
  bool ipred = (tid % 2 == 0);

  if (ipred) {
    ia = 100.0f;
  }
  if (!ipred) {
    ib = 200.0f;
  }
 
  c[tid] = ia + ib;
}


__global__ void mathKernel4(float *c) {
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  float ia, ib;
  ia = ib = 0.0f;
  int itid = tid >> 5;

  if (itid & 0x01 == 0) {
    ia = 100.0f;
  } else {
    ib = 200.0f;
  }
  c[tid] = ia + ib;
}


int main(int argc, char **argv) {
  int dev = 0;
  cudaDeviceProp deviceProp;
  CHECK(cudaGetDeviceProperties(&deviceProp, dev));
  printf("%s using Device %d: %s\n", argv[0], dev, deviceProp.name);

  int size = 65536;
  int blocksize = 64;

  if (argc > 1) blocksize = atoi(argv[1]);
  if (argc > 2) size = atoi(argv[2]);

  printf("Data size %d\n", size);

  dim3 block(blocksize, 1);
  dim3 grid ((size + block.x - 1)/ block.x, 1);
  printf("Excecution Configure (block %d grid %d)\n", block.x, grid.x);

  float *d_C;
  size_t nBytes = size * sizeof(float);
  CHECK(cudaMalloc((float **)&d_C, nBytes));

  double istart, ielaps;
  CHECK(cudaDeviceSynchronize());
  istart = seconds();
  warmingup<<<grid, block>>>(d_C);
  CHECK(cudaDeviceSynchronize());
  ielaps = seconds() - istart;
  printf("warmup  <<<%4d %4d>>> elapsed %f sec\n", grid.x, block.x, ielaps);
  CHECK(cudaGetLastError());

  istart = seconds();
  mathKernel1<<<grid, block>>>(d_C);
  CHECK(cudaDeviceSynchronize());
  ielaps = seconds() - istart;
  printf("mathKernel1 <<<%4d %4d>>> elapsed %f sec\n", grid.x, block.x, ielaps);
  CHECK(cudaGetLastError());


  istart = seconds();
  mathKernel2<<<grid, block>>>(d_C);
  CHECK(cudaDeviceSynchronize());
  ielaps = seconds() - istart;
  printf("mathKernel2 <<<%4d %4d>>> elapsed %f sec\n", grid.x, block.x, ielaps);
  CHECK(cudaGetLastError());

  istart = seconds();
  mathKernel3<<<grid, block>>>(d_C);
  CHECK(cudaDeviceSynchronize());
  ielaps = seconds() - istart;
  printf("mathKernel3 <<<%4d %4d>>> elapsed %f sec\n", grid.x, block.x, ielaps);
  CHECK(cudaGetLastError());

  istart = seconds();
  mathKernel4<<<grid, block>>>(d_C);
  CHECK(cudaDeviceSynchronize());
  ielaps = seconds() - istart;
  printf("mathKernel4 <<<%4d %4d>>> elapsed %f sec\n", grid.x, block.x, ielaps);
  CHECK(cudaGetLastError());

  CHECK(cudaFree(d_C));
  CHECK(cudaDeviceReset());

  return EXIT_SUCCESS;
}
