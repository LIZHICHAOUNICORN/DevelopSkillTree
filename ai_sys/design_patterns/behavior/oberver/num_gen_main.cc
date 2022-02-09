#include "digit_observer.h"
#include "graph_observer.h"
#include "random_num_gen.h"

int main(int argc, char* argv[]) {
  practice::NumGen* num_gen = new practice::RandomNumGen();
  practice::NumGenObServer* g_ob = new practice::GraphObserver();
  practice::NumGenObServer* d_ob = new practice::DigitObserver();

  num_gen->AddObserver(g_ob);
  num_gen->AddObserver(d_ob);
  num_gen->Exec();

  delete num_gen;
  delete g_ob;
  delete d_ob;

  return 0;
}
