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

double bench_mark(uint64_t number, uint64_t sqrt_n, bool *is_factor){
	double start = omp_get_wtime();
	find_factor_pairs(number, sqrt_n, is_factor);
	double end = omp_get_wtime();
//	printf("Total time: %.4f s\n", end - start);
	return end - start;

}

void show(bool *is_factor, uint64_t sqrt_n, uint64_t number){
	for (uint64_t i=0;i<sqrt_n;i++){
		if (is_factor[i]){
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
			size_t alloc_size = sizeof(bool) * sqrt_n;
			bool *is_factor = (bool *)malloc(alloc_size);
			printf("Prime factorization of %" PRIu64 "with num_threads %d" ": ", number, thread_size);
			double average = 0;
			double SD = 0;
			for (int i=0;i<num_benchmark;i++){
				result[i] = bench_mark(number, sqrt_n, is_factor);
				average += result[i];
//				show(is_factor, sqrt_n, number);
				memset(is_factor, false, alloc_size); 
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
		printf("\n");
		fprintf(fptr, "\n");
	}	

	free(result);
	fclose(fptr);
	return 0;
}

