#include "dataset_creation.hpp"
#include "file_procs.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char * argv[]) {
	if (argc < 4) {
		std::cout << "Usage:" << std::endl
				  << "  create_dataset <dataset_size> <nonzero_percentage> <filename>" << std::endl;
		return 1;
	}

	unsigned long int dataset_size = strtoul(argv[1], NULL, 0);
	unsigned int non_zero_percentage = strtoul(argv[2], NULL, 0);
	std::string filename (argv[3]);

	std::vector<unsigned long long int> dataset = createDataset(dataset_size, non_zero_percentage);

	if (dataset.empty()) {
		std::cout << "Dataset creation failed!" << std::endl;
		return 2;
	}

	if (saveToFile(dataset, filename) != 0) {
		std::cout << "Write to file failed!" << std::endl;
		return 3;
	}

	std::cout << "Dataset successfully saved to " << filename << std::endl;
	return 0;
}