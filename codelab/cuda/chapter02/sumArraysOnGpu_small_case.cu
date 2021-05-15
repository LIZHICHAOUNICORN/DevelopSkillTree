#include "../common/common.h"
#include <cuda_runtime.h>
#include <stdio.h>

void checkResult(float *host_ref, float *gpu_ref, const int N) {
  double epsilon = 1.0E-8;
  bool match = 1;
  for (int i = 0; i < N; ++i) {
    if(abs(host_ref[i] - gpu_ref[i]) > epsilon) {
      match = 0;
      printf("arrays do not match!\n");
      printf("host %5.2f gpu %5.2f at current: %d\n", host_ref[i], gpu_ref[i], i);
      break;
    }
  }
  if (match) printf("Arrays match!\n");
  return;
}

void InitialData(float* ip, int size) {
  time_t t;
  srand((unsigned) time(&t));
  for (int i = 0; i < size; i++) {
    ip[i] = (float)(rand() & 0xFF) / 10.0f;
  }
  return;
}

void SumArraysOnHost(float *a, float *b, float *c, const int N) {
  for (int idx = 0; idx < N; ++idx) {
    c[idx] = a[idx] + b[idx];
  }
}

__global__ void SumArraysOnGpu(float* a, float *b, float *c, const int N){
  int i = threadIdx.x;
  if (i < N) c[i] = a[i] + b[i];
}

int main(int argc, char **argv) {
  printf("%s Starting ..\n", argv[0]);
  
  int dev = 0;
  CHECK(cudaSetDevice(dev));

  int n_elem = 1 << 5;
  printf("Vector size %d \n", n_elem);
  size_t n_bytes = n_elem * sizeof(float);

  float* h_a = (float*)malloc(n_bytes);
  float* h_b = (float*)malloc(n_bytes);
  float* host_ref = (float*)malloc(n_bytes);
  float* gpu_ref = (float*)malloc(n_bytes);

  InitialData(h_a, n_elem);
  InitialData(h_b, n_elem);

  memset(host_ref, 0, n_bytes);
  memset(gpu_ref, 0, n_bytes);

  float *d_a, *d_b, *d_c;
  CHECK(cudaMalloc((float**)&d_a, n_bytes));
  CHECK(cudaMalloc((float**)&d_b, n_bytes));
  CHECK(cudaMalloc((float**)&d_c, n_bytes));

  CHECK(cudaMemcpy(d_a, h_a, n_bytes, cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(d_b, h_b, n_bytes, cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(d_c, gpu_ref, n_bytes, cudaMemcpyHostToDevice));
  
  dim3 block(n_elem);
  dim3 grid(1);
  SumArraysOnGpu<<<grid, block>>>(d_a, d_b, d_c, n_elem);
  printf("Execution configure <<<%d, %d>>>\n", grid.x, block.x);
  CHECK(cudaMemcpy(gpu_ref, d_c, n_bytes, cudaMemcpyDeviceToHost));
  SumArraysOnHost(h_a, h_b, host_ref, n_elem);

  checkResult(host_ref, gpu_ref, n_elem);
  CHECK(cudaFree(d_a));
  CHECK(cudaFree(d_b));
  CHECK(cudaFree(d_c));

  free(h_a);
  free(h_b);
  free(host_ref);
  free(gpu_ref);

  CHECK(cudaDeviceReset());
  return 0;

}
