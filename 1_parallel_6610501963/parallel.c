#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>
#include <inttypes.h>

#include <config.h>

int main() {

	omp_set_num_threads(num_threads);

	printf("Prime factorization of " "%" PRIu64 ":\n", number);

	uint64_t sqrt_n = (uint64_t)sqrt((double)number);
	#pragma omp parallel 
	{
		int thread_id = omp_get_thread_num();
		for (uint64_t i = 1+thread_id;i<=sqrt_n;i+=num_threads) {
			if (number % i == 0){
				printf("%" PRIu64 ", " "%" PRIu64 "\n", i , number/i);
			}
		}
	}

	return 0;
}

