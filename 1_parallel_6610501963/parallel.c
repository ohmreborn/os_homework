#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <omp.h>

#include <config.h>

void find_factor_pairs(uint64_t number, uint64_t sqrt_n, bool *is_factor) {
	#pragma omp parallel for schedule(static)
	for (uint64_t i = 1; i <= sqrt_n; i++) {
		if (number % i == 0){
			is_factor[i - 1] = true;
		}
	}
}

void bench_mark(uint64_t number, uint64_t sqrt_n, bool *is_factor){
	clock_t start, end;
	start = clock();
	find_factor_pairs(number, sqrt_n, is_factor);
	end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("CPU time used: %f seconds\n", cpu_time_used);
}

void show(bool *is_factor, uint64_t sqrt_n, uint64_t number){
	for (uint64_t i=0;i<sqrt_n;i++){
		if (is_factor[i]){
			printf("%" PRIu64 ", " "%" PRIu64 "\n", i+1, number/(i+1) );
		}
	}
}

int main() {
	for (int test_num_i=0; test_num_i<number_test_size; test_num_i++){
		for (int test_thread_i=0; test_thread_i<thread_test_size; test_thread_i++){
			uint64_t number = numbers[test_num_i];
			int thread_size = num_threads[test_thread_i];

			uint64_t sqrt_n = (uint64_t)sqrt((double)number);
			if (sqrt_n % thread_size != 0){
				printf("Error for bench_mark number " "%"PRIu64 " with num_threads %d ", number, thread_size);
				printf("please specify a square root of number that Divisible %d", thread_size);
				return 1;
			}
			size_t alloc_size = sizeof(bool) * sqrt_n;
			bool *is_factor = (bool *)malloc(alloc_size);
			printf("Prime factorization of %" PRIu64 "with num_threads %d" ":\n", number, thread_size);
			for (int i=0;i<num_benchmark;i++){
				bench_mark(number, sqrt_n, is_factor);
//				show(is_factor, sqrt_n, number);
				memset(is_factor, false, alloc_size); 
			}
			free(is_factor);
		}
		printf("\n");
	}	

	return 0;
}

