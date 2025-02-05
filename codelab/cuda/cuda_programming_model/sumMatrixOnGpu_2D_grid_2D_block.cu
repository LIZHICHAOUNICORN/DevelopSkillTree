#include <stdio.h>
#include <cuda_runtime.h>
#include "../common/common.h"


void initialData(float *ip, const int size) {
  int i;
  for(i = 0; i < size; ++i) {
    ip[i] = (float)(rand() & 0xFF) / 10.0f;
  }
  return;
}

void sumMatrixOnHost(float *A, float* B, float *C, const int nx, const int ny) {
  float *ia = A;
  float *ib = B;
  float *ic = C;
  for (int iy = 0; iy < ny; iy ++) {
    for (int ix = 0; ix < nx; ++ix) {
      ic[ix] = ia[ix] + ib[ix];
    }

    ia += nx;
    ib += nx;
    ic += nx;
  }
  return;
}

void checkResult(float *hostRef, float *gpuRef, const int N) {
  double epsilon = 1.0E-8;
  bool match = true;
  for (int i = 0; i < N; ++i) {
    if (abs(hostRef[i] - gpuRef[i]) > epsilon) {
      match = false;
      printf("host %f gpu %f\n", hostRef[i], gpuRef[i]);
      break;
    }
  }
  if (match) {
    printf("Arrays match. \n\n");
  } else {
    printf("Arrays do not match. \n\n");
  }
  
}

__global__ void sumMatrixOnGPU2D(float *MatA, float *MatB, float *MatC, int nx, int ny) {
  unsigned int ix = threadIdx.x + blockIdx.x * blockDim.x;
  unsigned int iy = threadIdx.y + blockIdx.y * blockIdx.y;
  unsigned int idx = iy * nx + ix;
  if (ix < nx && iy < ny) {
    MatC[idx] = MatA[idx] + MatB[idx];
  }
}


int main(int argc, char **argv) {
  printf("%s starting", argv[0]);

  int dev = 0;
  cudaDeviceProp deviceProp;
  CHECK(cudaGetDeviceProperties(&deviceProp, dev));
  printf("Using Device %d: %s \n", dev, deviceProp.name);
  CHECK(cudaSetDevice(dev));
  
  int nx = 1 << 14;
  int ny = 1 << 14;
  int nxy = nx * ny; // 2^14 * 2^14 = 2^28, not overflow
  int nBytes = nxy * sizeof(float);
  printf("Matrix size nx %d, ny %d\n", nx, ny);

  float *h_A, *h_B, *hostRef, *gpuRef;
  h_A = (float *)malloc(nBytes);
  h_B = (float *)malloc(nBytes);

  hostRef = (float *)malloc(nBytes);
  gpuRef = (float *)malloc(nBytes);

  double iStart = seconds();
  initialData(h_A, nxy);
  initialData(h_B, nxy);
  double iElaps = seconds() - iStart;
  printf("initialize matrix elapsed %f sec\n", iElaps);

  memset(hostRef, 0, nBytes);
  memset(gpuRef, 0, nBytes);

  iStart = seconds();
  sumMatrixOnHost(h_A, h_B, hostRef, nx, ny);
  iElaps = seconds() - iStart;
  printf("sumMatrixOnHost elapsed %f sec\n", iElaps);
  
  float *d_MatA, *d_MatB, *d_MatC;
  CHECK(cudaMalloc((void **)&d_MatA, nBytes));
  CHECK(cudaMalloc((void **)&d_MatB, nBytes));
  CHECK(cudaMalloc((void **)&d_MatC, nBytes));

  CHECK(cudaMemcpy(d_MatA, h_A, nBytes, cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(d_MatB, h_B, nBytes, cudaMemcpyHostToDevice));
  
  int dimx = 32;
  int dimy = 32;
  dim3 block(dimx, dimy);
  dim3 grid((nx + block.x -1)/block.x, (ny + block.y -1)/ block.y);
  
  iStart = seconds();
  sumMatrixOnGPU2D<<<grid, block>>>(d_MatA, d_MatB, d_MatC, nx, ny);
  CHECK(cudaDeviceSynchronize());
  iElaps = seconds() -iStart;
  printf("SumMatrixOnGPU1D <<<(%d, %d),(%d, %d)>>> elapsd %f sec\n", grid.x, grid.y, block.x, block.y, iElaps);

  CHECK(cudaGetLastError());
  CHECK(cudaMemcpy(gpuRef, d_MatC, nBytes, cudaMemcpyDeviceToHost));

  checkResult(hostRef, gpuRef, nxy);

  CHECK(cudaFree(d_MatA));
  CHECK(cudaFree(d_MatB));
  CHECK(cudaFree(d_MatC));

  free(h_A);
  free(h_B);
  free(hostRef);
  free(gpuRef);
  CHECK(cudaDeviceReset());
  return 0;

}
