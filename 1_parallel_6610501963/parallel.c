#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>

int main() {

	uint64_t n;
	printf("Enter a number to factorization: ");
	scanf("%llu", &n);
	if (n == 0) {
		printf("cannot factorization 0\n");
		return 1;
	}

	int num_threads;
	printf("Enter a num threads: ");
	scanf("%d", &num_threads);
	if (num_threads < 1){
		printf("num_threads cannot be lesser than 1\n");
		return 1;
	}else{
		omp_set_num_threads(num_threads);
	}

	printf("Prime factorization of %llu:\n", n);

	uint64_t sqrt_n = (uint64_t)sqrt((double)n);
	#pragma omp parallel 
	{
		for (uint64_t i = 2; i <= sqrt_n; i++ ) {
			while (n % i == 0) {
				#pragma omp critical
				{
					n /= i;
					printf("%llu ",i);
				}
			}
		}
	}

	if (n > 2) {
		printf("%llu", n);
	}

	printf("\n");
	return 0;
}

