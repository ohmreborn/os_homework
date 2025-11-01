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

void bench_mark(uint64_t number, int thread_size, std::vector<double> &result_serial, std::vector<double> &result_parallel, int i){
	clock_t start, end;

	start = clock();
	uint64_t sqrt_n = (uint64_t)sqrt((double)number);
	std::vector<uint64_t> factor;
	end = clock();
	result_serial[i] = ((double) (end - start)) / CLOCKS_PER_SEC;

	start = clock();
	find_factor_pairs(number, sqrt_n, thread_size, factor);
	end = clock();
	result_parallel[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
}

void show(std::vector<uint64_t> &factor, uint64_t number){
	for (uint64_t num: factor){
		std::cout << num << " " << number/num << '\n';
	}
	std::cout << '\n';
}

int main() {
	std::vector<double> result_serial(num_benchmark,0);
	std::vector<double> result_parallel(num_benchmark,0);
	std::ofstream serial("result_serial.csv"); 
	if (!serial.is_open()) {
		std::cout << "Error: cannot open file.\n"; 
		return 1; // Indicate an error
	}
	std::ofstream parallel("result_parallel.csv"); 
	for (int i=0;i<thread_test_size;i++){
		serial << num_threads[i] << ",";
		parallel << num_threads[i] << ",";
	}
	serial << '\n';
	parallel << '\n';

	for (int test_num_i=0; test_num_i<number_test_size; test_num_i++){
		serial << numbers[test_num_i] << ',';
		parallel << numbers[test_num_i] << ',';
		for (int test_thread_i=0; test_thread_i<thread_test_size; test_thread_i++){
			uint64_t number = numbers[test_num_i];
			int thread_size = num_threads[test_thread_i];

			std::cout << "Prime factorization of " << number << " with num_threads: " << thread_size << '\n';
			double average_serial = 0;
			double SD_serial = 0;
			double average_parallel = 0;
			double SD_parallel = 0;
			for (int i=0;i<num_benchmark;i++){
				bench_mark(number, thread_size, result_serial, result_parallel, i);
				average_serial += result_serial[i];
				average_parallel += result_parallel[i];
				// show(factor, number);
			}
			average_serial /= (double)num_benchmark;
			average_parallel /= (double)num_benchmark;
			for (int i=0;i<num_benchmark;i++){
				SD_serial += (average_serial - result_serial[i]) * (average_serial - result_serial[i]);
				SD_parallel += (average_parallel - result_parallel[i]) * (average_parallel - result_parallel[i]);
			}
			SD_serial = sqrt(SD_serial) / (double)num_benchmark;
			SD_parallel = sqrt(SD_parallel) / (double)num_benchmark;
			std::cout << "Serial: " << average_serial << "±" << SD_serial << '\n';
			std::cout << "Parallel: " << average_parallel << "±" << SD_parallel << '\n';
			serial << average_serial << ',';
			parallel << average_parallel << ',';
		}
		serial << '\n';
		parallel << '\n';
	}	

	serial.close();
	parallel.close();

	return 0;
}
