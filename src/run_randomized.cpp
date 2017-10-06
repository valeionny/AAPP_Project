#include "file_procs.hpp"
#include "randomized.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>

int main(int argc, char * argv[]) {
	if (argc < 2) {
		std::cout << "Usage:" << std::endl
				  << "  " << argv[0] << " <path_to_dataset> <k> <thread_num>" << std::endl;
		return 1;
	}

	std::string filename (argv[1]);

	unsigned int k;
	if (argc >= 3) {
		k = strtoul(argv[2], 0, 0);
	} else {
		k = 0;
	}

	if (argc >= 4) {
		unsigned int num_threads = strtoul(argv[3], 0, 0);
		#ifdef _OPENMP
			omp_set_num_threads(num_threads);
			std::cout << num_threads << " threads" << std::endl;
		#endif
	}

	std::vector<unsigned long long int> addends = loadFromFile(filename);
	if (addends.empty()) {
		std::cout << "Dataset loading failed!" << std::endl;
		return 2;
	}
	std::cout << "Loaded dataset " << filename << std::endl;

	unsigned long long int sum = randomizedSum(addends, k);
	std::cout << "Sum: " << sum << std::endl;

	std::cout << "Done!" << std::endl;
	return 0;
}