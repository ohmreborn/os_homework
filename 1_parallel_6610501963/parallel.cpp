#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>
#include <vector>

#include <omp.h>

#include <config.h>

void find_factor_pairs(uint64_t number, uint64_t sqrt_n, int thread_size, std::vector<uint64_t> &factor) {
	omp_set_num_threads(thread_size);
	#pragma omp parallel
	{
		std::vector<uint64_t> local_factor;
		int thread_id = omp_get_thread_num();
		#pragma omp for nowait
		for (uint64_t i = 1+thread_id; i <= sqrt_n; i+=thread_size) {
			if (number % i == 0){
				local_factor.push_back(i);
			}
		}
		#pragma omp critical
		{
			factor.insert(factor.end(), local_factor.begin(),local_factor.end());
		}
	}
}

double bench_mark(uint64_t number, uint64_t sqrt_n, int thread_size, std::vector<uint64_t> &factor){
	clock_t start, end;
	start = clock();
	find_factor_pairs(number, sqrt_n, thread_size, factor);
	end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	return cpu_time_used;
}

void show(std::vector<uint64_t> &factor, uint64_t number){
	for (uint64_t num: factor){
		std::cout << num << " " << number/num << '\n';
	}
	std::cout << '\n';
}

int main() {
	std::vector<uint64_t> factor;
	std::vector<double> result(num_benchmark,0);
	std::ofstream output("result.csv"); 
	if (!output.is_open()) {
		std::cout << "Error: cannot open file.\n"; 
		return 1; // Indicate an error
	}
	for (int i=0;i<thread_test_size;i++){
		output << num_threads[i] << ",";
	}
	output << '\n';

	for (int test_num_i=0; test_num_i<number_test_size; test_num_i++){
		output << numbers[test_num_i] << ',';
		for (int test_thread_i=0; test_thread_i<thread_test_size; test_thread_i++){
			uint64_t number = numbers[test_num_i];
			int thread_size = num_threads[test_thread_i];

			uint64_t sqrt_n = (uint64_t)sqrt((double)number);
			std::cout << "Prime factorization of " << number << " with num_threads: " << thread_size << '\n';
			double average = 0;
			double SD = 0;
			for (int i=0;i<num_benchmark;i++){
				result[i] = bench_mark(number, sqrt_n, thread_size, factor);
				average += result[i];
				// show(factor, number);
				factor.clear();
			}
			average /= (double)num_benchmark;
			for (int i=0;i<num_benchmark;i++){
				SD += (average - result[i]) * (average - result[i]);
			}
			SD = sqrt(SD) / (double)num_benchmark;
			std::cout << average << "±" << SD << '\n';
			output << average << ',';
		}
		output << '\n';
	}	

	output.close();

	return 0;
}
