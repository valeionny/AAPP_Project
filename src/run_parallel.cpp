#include "file_procs.hpp"
#include "file_procs.cpp"
#include "parallel.hpp"
#include "parallel.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>

int main(int argc, char * argv[]) {
	if (argc < 2) {
		std::cout << "Usage:" << std::endl
				  << "  " << argv[0] << " <path_to_dataset> [<num_threads>]" << std::endl;
		return 1;
	}

	std::string filename (argv[1]);

	if (argc >= 3) {
		unsigned int num_threads = strtoul(argv[2], 0, 0);
		#ifdef _OPENMP
			omp_set_num_threads(num_threads);
			std::cout << "Running with " << num_threads << " threads" << std::endl;
		#else
			std::cout << "OpenMP not found. Remember to compile with the -fopenmp flag!" << std::endl;
			std::cout << "Running with 1 thread." << std::endl;
		#endif
	}

	std::vector<unsigned long long int> addends = loadFromFile(filename);
	if (addends.empty()) {
		std::cout << "Dataset loading failed!" << std::endl;
		return 2;
	}
	std::cout << "Loaded dataset " << filename << std::endl;
	unsigned long long int sum = parallelSum(addends);
	std::cout << "Sum: " << sum << std::endl;

	std::cout << "Done!" << std::endl;
	return 0;
}
