#include <stdint.h>

int number_test_size = 3;
uint64_t numbers[3] = {
	(uint64_t)1<<10,
	(uint64_t)1<<20,
	(uint64_t)1<<30,
};
int thread_test_size = 4;
int num_threads[4] = {1, 2, 4, 8};
int num_benchmark = 1000;
