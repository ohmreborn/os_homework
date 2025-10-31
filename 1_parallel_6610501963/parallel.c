#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <omp.h>

#include <config.h>

// Padded structure to prevent false sharing
// Each element occupies a full cache line (64 bytes)
typedef struct {
	bool value;
	char padding[63];  // 1 + 63 = 64 bytes (typical cache line size)
} padded_bool;

void find_factor_pairs(uint64_t number, uint64_t sqrt_n, int thread_size, padded_bool *is_factor) {
	omp_set_num_threads(thread_size);
#pragma omp parallel 
	{
		int thread_id = omp_get_thread_num();
		for (uint64_t i = 1+thread_id; i <= sqrt_n; i+=thread_size) {
			is_factor[i-1].value = (number % i == 0);
		}
	}
}

double bench_mark(uint64_t number, uint64_t sqrt_n, int thread_size, padded_bool *is_factor){
	clock_t start, end;
	start = clock();
	find_factor_pairs(number, sqrt_n, thread_size, is_factor);
	end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	return cpu_time_used;
}

void show(padded_bool *is_factor, uint64_t sqrt_n, uint64_t number){
	for (uint64_t i=0;i<sqrt_n;i++){
		if (is_factor[i].value){
			printf("%" PRIu64 ", " "%" PRIu64 "\n", i+1, number/(i+1) );
		}
	}
}

int main() {
	double *result = (double *)malloc(sizeof(double) * num_benchmark);
	FILE *fptr = fopen("result.csv", "w");
	for (int i=0;i<thread_test_size;i++){
		fprintf(fptr, "%d,", num_threads[i]);
	}
	fprintf(fptr, "\n");

	for (int test_num_i=0; test_num_i<number_test_size; test_num_i++){
		fprintf(fptr, "%" PRIu64 ",", numbers[test_num_i]);
		for (int test_thread_i=0; test_thread_i<thread_test_size; test_thread_i++){
			uint64_t number = numbers[test_num_i];
			int thread_size = num_threads[test_thread_i];

			uint64_t sqrt_n = (uint64_t)sqrt((double)number);
			size_t alloc_size = sizeof(padded_bool) * sqrt_n;
			padded_bool *is_factor = (padded_bool *)malloc(alloc_size);
			printf("Prime factorization of %" PRIu64 " with num_threads %d: ", number, thread_size);
			double average = 0;
			double SD = 0;
			for (int i=0;i<num_benchmark;i++){
				result[i] = bench_mark(number, sqrt_n, thread_size, is_factor);
				average += result[i];
				//show(is_factor, sqrt_n, number);
				memset(is_factor, 0, alloc_size); 
			}
			average /= (double)num_benchmark;
			for (int i=0;i<num_benchmark;i++){
				SD += (average - result[i]) * (average - result[i]);
			}
			SD = sqrt(SD);
			printf("%f ± %f \n", average, SD);
			fprintf(fptr, "%f,", average);
			free(is_factor);
		}
		fprintf(fptr, "\n");
	}	

	free(result);
	fclose(fptr);

	return 0;
}
