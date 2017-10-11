#include "file_procs.hpp"
#include "file_procs.cpp"
#include "serial.hpp"
#include "serial.cpp"
#include "time_benchmark.hpp"
#include "time_benchmark.cpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char * argv[]) {
	if (argc < 3) {
		std::cout << "Usage:" << std::endl
				  << "  " << argv[0] << " <path_to_dataset> <output_file> <repetitions = 100>" << std::endl;
		return 1;
	}

	std::string dataset_filename (argv[1]);

	std::string output_filename (argv[2]);

	unsigned long int repetitions;
	if (argc >= 4) {
		repetitions = strtoul(argv[3], 0, 0);
	} else {
		repetitions = 100;
	}

	std::vector<unsigned long long int> addends = loadFromFile(dataset_filename);
	if (addends.empty()) {
		std::cout << "Dataset loading failed!" << std::endl;
		return 2;
	}
	std::cout << "Loaded dataset " << dataset_filename << std::endl;

	std::cout << "Starting serial sum with " << repetitions << " repetitions" << std::endl;
	unsigned long long int start_time = GetTimeMs64();
	for (unsigned long int i=0; i < repetitions; i++){
		serialSum(addends);
	}
	unsigned long long int end_time = GetTimeMs64();
	unsigned long long int elapsed_time = end_time - start_time;
	std::cout << "Total elapsed time: " << elapsed_time << " ms" << std::endl;
	std::cout << "Time for a single execution: " << ((float) elapsed_time / repetitions) << " ms" << std::endl;


	std::ofstream text_file (output_filename);

	if (text_file.is_open()) {
		
		// write all the parameters we want to display in first line
		text_file << "Algorithm" << ";" <<"NzPercentage"<< ";" << "K" << ";"<< "Threads" << ";"<< "Time[ms]" <<"\n";
		double percentage = getPercentageFromFile(dataset_filename);
	    text_file << "Serial"<<";";
	    text_file << percentage <<";";
	    text_file << "NO" <<";";
	    text_file << "1" <<";";
	    text_file << elapsed_time <<"\n";
		text_file.close();

	} else {
		std::cout << "Unable to open file \"" << output_filename  << "\"\n";
		return 1;
	}

	std::cout << "Done!" << std::endl;
	return 0;
}
