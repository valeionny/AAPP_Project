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

#include "dataset_creation.hpp"
#include "dataset_creation.cpp"
#include "file_procs.hpp"
#include "file_procs.cpp"
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
	double non_zero_percentage = strtod(argv[2], NULL);
	std::string filename (argv[3]);

	std::vector<unsigned long long int> dataset = createDataset(dataset_size, non_zero_percentage);

	if (dataset.empty()) {
		std::cout << "Dataset creation failed!" << std::endl;
		return 2;
	}

	if (saveToFile(dataset, non_zero_percentage, filename) != 0) {
		std::cout << "Write to file failed!" << std::endl;
		return 3;
	}

	std::cout << "Dataset successfully saved to " << filename << std::endl;
	return 0;
}
