// MIT License
//
// Copyright (c) 2017 Pietro Ferretti, Valentina Ionata
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "file_procs.hpp"
#include "randomized.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <omp.h>

int main(int argc, char * argv[]) {

	if (argc < 2) {
		// print usage and exit
		std::cout << "Usage:" << std::endl
				  << "  " << argv[0] << " <path_to_dataset> [<num_threads=1> [<k=10>]]" << std::endl;
		return 1;
	}

	// get dataset path
	std::string filename (argv[1]);

	// set num threads
	if (argc >= 3) {
		#ifdef _OPENMP
			unsigned int num_threads = strtoul(argv[2], 0, 0);
			omp_set_num_threads(num_threads);
			std::cout << "Running with " << num_threads << " threads" << std::endl;
		#else
			std::cout << "OpenMP not found. Remember to compile with the -fopenmp flag!" << std::endl;
			std::cout << "Running with 1 thread." << std::endl;
		#endif
	}

	// set parameter k for the estimation step
	unsigned int k;
	if (argc >= 4) {
		k = strtoul(argv[2], 0, 0);
	} else {
		k = 0;
	}

	// load dataset into a vector
	std::vector<unsigned long long int> addends = loadFromFile(filename);
	if (addends.empty()) {
		std::cout << "Dataset loading failed!" << std::endl;
		return 2;
	}
	std::cout << "Loaded dataset " << filename << std::endl;

	// do the sum
	unsigned long long int sum;
	if (k != 0) {
		sum = randomizedSum(addends, k);
	} else {
		sum = randomizedSum(addends);
	}
	std::cout << "Sum: " << sum << std::endl;

	std::cout << "Done!" << std::endl;
	return 0;
}