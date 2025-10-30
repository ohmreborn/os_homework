#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

#include <config.h>

int main() {

	omp_set_num_threads(num_threads);

	printf("Prime factorization of %llu:\n", number);

	uint64_t sqrt_n = (uint64_t)sqrt((double)number);
	bool *count_n = (bool *)malloc(sizeof(bool) * (sqrt_n+1));
	#pragma omp parallel 
	{
		int thread_id = omp_get_thread_num();
		for (uint64_t i = 1+thread_id;i<=sqrt_n;i+=num_threads) {
			if (number % i == 0){
				count_n[i] = true;
			}
		}
	}

	for (uint64_t i=1;i <= sqrt_n;i++){
		if (count_n[i]){
			printf("%llu, %llu\n", i, number/i);
		}
	}

	return 0;
}

