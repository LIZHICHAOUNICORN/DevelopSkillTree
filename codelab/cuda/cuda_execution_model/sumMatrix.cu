#include "../common/common.h"
#include <stdio.h>
#include <cuda_runtime.h>

void initialData(float* ip, const int size) {
    for (int i = 0; i < size; ++i) {
        ip[i] = (float)(rand() & 0xFF) / 10.0f;
    }
}

void sumMatrixOnHost(float *A, float *B, float *C, const int nx, const int ny) {
    float *ia = A;
    float *ib = B;
    float *ic = C;
    for(int iy = 0; iy < ny; ++iy) {
        for(int ix = 0; ix < nx; ++ix) {
            ic[ix] = ia[ix] + ib[ix];
        }
        ia += nx;
        ib += nx;
        ic += nx;
    }
    return;
}

void checkResult(float *host_ref, float *gpu_ref, const int N) {
    double epsilon = 1.0E-8;
    for(int i = 0; i < N; ++i) {
        if(abs(host_ref[i] - gpu_ref[i] > epsilon)) {
            printf("host %f gpu %f", host_ref[i], gpu_ref[i]);
            printf("Arrays do not match.\n");
        }
    }
}

__global__ void sumMatrixOnGPU2D(float *A, float *B, float *C, int nx, int ny) {
    unsigned int ix = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int iy = blockIdx.y * blockDim.y + threadIdx.y;
    unsigned int idx = iy * nx + ix;

    if (ix < nx && iy < ny) {
        C[idx] = A[idx] + B[idx];
    }

}


int main(int argc, char* argv[]) {
    int dev = 0;
    cudaDeviceProp device_prop;
    CHECK(cudaGetDeviceProperties(&device_prop, dev));
    CHECK(cudaSetDevice(dev));

    int nx = 1 << 14;
    int ny = 1 << 14;

    int nxy = nx * ny;
    int nBytes = nxy * sizeof(float);

    float *h_A, *h_B, *host_ref, *gpu_ref;
    h_A = (float*)malloc(nBytes);
    h_B = (float*)malloc(nBytes);
    host_ref = (float *)malloc(nBytes);
    gpu_ref = (float *)malloc(nBytes);
    
    float istart = seconds();
    initialData(h_A, nxy);
    initialData(h_B, nxy);
    float ielaps = seconds() - istart;

    memset(host_ref, 0, nBytes);
    memset(gpu_ref, 0, nBytes);
    istart = seconds();
    sumMatrixOnHost(h_A, h_B, host_ref, nx, ny);
    ielaps = seconds() - istart;

    float *d_MatA, *d_MatB, *d_MatC;
    CHECK(cudaMalloc((void **)&d_MatA, nBytes));
    CHECK(cudaMalloc((void **)&d_MatB, nBytes));
    CHECK(cudaMalloc((void **)&d_MatC, nBytes));

    CHECK(cudaMemcpy(d_MatA, h_A, nBytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_MatB, h_B, nBytes, cudaMemcpyHostToDevice));

    int dimx = 32;
    int dimy = 32;
    if (argc > 2) {
      dimx = atoi(argv[1]);
      dimy = atoi(argv[0]);
    }
    dim3 block(dimx, dimy);
    dim3 grid((nx+block.x - 1/block.x), (ny + block.y - 1)/block.y);

    CHECK(cudaDeviceSynchronize());
    istart = seconds();
    sumMatrixOnGPU2D<<<grid, block>>>(d_MatA, d_MatB, d_MatC, nx, ny);
    CHECK(cudaDeviceSynchronize());
    printf("sumMatrixOnGPU2D <<<(%d, %d), (%d, %d)>>> elapsed %f ms\n", grid.x, grid.y, block.x, block.y, ielaps);
    CHECK(cudaGetLastError());
   
    CHECK(cudaMemcpy(gpu_ref, d_MatC, nBytes, cudaMemcpyDeviceToHost));
    checkResult(host_ref, gpu_ref, nxy);

    CHECK(cudaFree(d_MatA));
    CHECK(cudaFree(d_MatB));
    CHECK(cudaFree(d_MatC));

    free(h_A);
    free(h_B);
    free(host_ref);
    free(gpu_ref);

    CHECK(cudaDeviceReset());
    return EXIT_SUCCESS;
}
