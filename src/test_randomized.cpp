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
#include "time_benchmark.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <omp.h>

int main(int argc, char * argv[]) {
	
	if (argc < 3) {
		std::cout << "Usage:" << std::endl
				  << "  " << argv[0] << " <path_to_dataset> <output_file> <k> <threads> <repetitions = 100>" << std::endl;
		return 1;
	}

	std::string dataset_filename (argv[1]);

	std::string output_filename (argv[2]);
	
	unsigned int k = strtoul(argv[3],0,0);
	
	unsigned int threads;
	
	if (argc >= 5) {
		threads = strtoul(argv[4], 0, 0);
		#ifdef _OPENMP
			omp_set_num_threads(threads);
			std::cout << "Running with " << threads << " threads" << std::endl;
		#else
			std::cout << "OpenMP not found. Remember to compile with the -fopenmp flag!" << std::endl;
			std::cout << "Running with 1 thread." << std::endl;
		#endif
	} else {
		threads = 1;
	}

	unsigned long int repetitions;
	if (argc >= 6) {
		repetitions = strtoul(argv[5], 0, 0);
	} else {
		repetitions = 100;
	}

	std::vector<unsigned long long int> addends = loadFromFile(dataset_filename);
	
	if (addends.empty()) {
		std::cout << "Dataset loading failed!" << std::endl;
		return 2;
	}
	std::cout << "Loaded dataset " << dataset_filename << std::endl;

	std::cout << "Starting randomized sum with " << repetitions << " repetitions" << std::endl;

	// we use rand() to get different runs each repetition
	srand((unsigned long int) time(NULL));
	std::vector<unsigned long int> seeds;
	for (unsigned long int i=0; i < repetitions; i++) {
		seeds.push_back(rand());
	}

	// measure the time needed for the algorithm execution
	unsigned long long int start_time = GetTimeMs64();
	for (unsigned long int i=0; i < repetitions; i++) {
		randomizedSumWithSeed(addends, seeds[i], k);
	}
	unsigned long long int end_time = GetTimeMs64();

	unsigned long long int elapsed_time = end_time - start_time;
	std::cout << "Total elapsed time: " << elapsed_time << " ms" << std::endl;
	std::cout << "Time for a single execution: " << ((float) elapsed_time / repetitions) << " ms" << std::endl;


	std::ofstream text_file (output_filename);
	
	if (text_file.is_open()) {
		
		// write all the parameters we want to display in first line
		text_file << "Algorithm" << ";"<<"DatasetSize"<< ";" <<"NzPercentage"<< ";" << "K" << ";"<< "Threads" << ";"<< "Time[ms]" <<"\n";
		double percentage = getPercentageFromFile(dataset_filename);
		text_file << "Randomized"<<";";
		int size = loadFromFile(dataset_filename).size();
		text_file << size <<";";
		text_file << percentage <<";";
		text_file << k <<";";
		text_file << threads <<";";
		text_file << ((float) elapsed_time / repetitions) <<"\n";
		text_file.close();

	} else {
		std::cout << "Unable to open file \"" << output_filename  << "\"\n";
		return 1;
	}

	std::cout << "Done!" << std::endl;
	return 0;
}
