# g++ must support c++17

# g++ -g  --std=c++17 05_read_write_mutex_benchmark.cc  -lpthread  -o 05_read_write_mutex_benchmark
# g++ -g  --std=c++17 05_producer_consumer.cc  -lpthread  -o 05_producer_consumer
# g++ -g  --std=c++17 05_thread_local.cc -lpthread  -o 05_thread_local
g++  -g  --std=c++17  05_thread_pool_template.h 05_thread_pool_template_test.cc  -lpthread  -o 05_thread_pool_template_test
