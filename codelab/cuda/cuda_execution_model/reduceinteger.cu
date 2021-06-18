#include "../common/common.h"
#include <cuda_runtime.h>
#include <stdio.h>

__global__ void reduceNeighbored(int *g_idata, int *g_odata, unsigned int n) {
  unsigned int tid = threadIdx.x;
  unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;

  int *idata = g_idata + blockIdx.x * blockDim.x;
  if (idx >= n) return;

  for (int stride = 1; stride < blockDim.x; stride *= 2) {
    if ((tid % (2 * stride)) == 0) {
      idata[tid] += idata[tid + stride];
    }
    __syncthreads();
  }
  if (tid == 0) g_odata[blockIdx.x] = idata[0];
}

int main(int argc, char **argv) {
  int dev = 0;
  cudaDeviceProp device_prop;
  CHECK(cudaGetDeviceProperties(&device_prop, dev));
  printf("%s starting reduction at ", argv[0]);
  printf(" device %d: %s", dev, device_prop.name);
  CHECK(cudaSetDevice(dev));

  bool result = false;
  int size = 1 << 24;
  printf(" with array size %d", size);

  int blocksize = 1024;
  if (argc > 1) {
    blocksize = atoi(argv[1]);
  }
  dim3 block(blocksize, 1);
  dim3 grid((size + block.x -1)/ block.x, 1);
  printf("grid %d block %d \n", grid.x, block.x);
  
  size_t bytes = size * sizeof(int);
  int* h_idata = (int *)malloc(bytes);
  int* h_odata = (int *)malloc(grid.x * sizeof(int));
  int *tmp = (int *)malloc(bytes);

  for (int i = 0; i < size; ++i) {
    h_idata[i] = (int) (rand() & 0xFF);
  }

  memcpy(tmp, h_idata, bytes);

  double istart, ielaps;
  int gpu_sum = 0;
  int *d_idata = NULL;
  int *d_odata = NULL;

  CHECK(cudaMalloc((void **)&d_idata, bytes));
  CHECK(cudaMalloc((void **)&d_odata, grid.x * sizeof(int)));

  istart = seconds();
  int cpu_sum = 0;
  // int cpu_sum = recursiveReduce(tmp, size);
  ielaps = seconds() - istart;
  printf("cpu reduce elapsed %f sec cpu_sum %d\n", ielaps, cpu_sum);

  CHECK(cudaMemcpy(d_idata, h_idata, bytes, cudaMemcpyHostToDevice));
  CHECK(cudaDeviceSynchronize());
  istart = seconds();
  reduceNeighbored<<<grid, block>>>(d_idata, d_odata, size);
  CHECK(cudaDeviceSynchronize());
  ielaps = seconds() - istart;
  CHECK(cudaMemcpy(h_odata, d_odata, grid.x * sizeof(int), cudaMemcpyDeviceToHost));
  return EXIT_SUCCESS;

}
