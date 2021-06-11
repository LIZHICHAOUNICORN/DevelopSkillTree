#include <stdlib.h>
#include <time.h>

void initial_data(float *ip, int size) {

}


int main(int argc, char** argv) {
  int n_elem = 1024;
  size_t n_bytes = n_elem * sizeof(float);

  float *h_a = (float *)malloc(n_bytes);
  float *h_b = (float *)malloc(n_bytes);
  float *h_c = (float *)malloc(n_bytes);


}
