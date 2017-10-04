#include "file_procs.hpp"
#include "file_procs.cpp"
#include "parallel.hpp"
#include "parallel.cpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char * argv[]) {
	if (argc < 2) {
		std::cout << "Usage:" << std::endl
				  << "  run_serial <path_to_dataset>" << std::endl;
		return 1;
	}

	std::string filename (argv[1]);

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
