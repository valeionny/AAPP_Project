#include "file_procs.hpp"
#include <fstream>
#include <iostream>

int saveToFile(std::vector<unsigned long long int> vec, double nonzeropercentage, std::string filename) {
	std::ofstream target_file (filename);

	if (target_file.is_open()) {
		// write size of vector in first line
		target_file << vec.size() << ' ';

		// write nonzero percentage
		target_file << nonzeropercentage << '\n';

		// write numbers separated by a space
		for (unsigned long long int elem: vec) {
			target_file << elem << ' ';
		}
		target_file.close();

	} else {
		std::cout << "Unable to open file \"" << filename << "\"\n";
		return 1;
	}

	return 0;
}

std::vector<unsigned long long int> loadFromFile(std::string filename) {
	std::ifstream source_file (filename);
	std::vector<unsigned long long int> vec;

	if (source_file.is_open()) {
		// read vector size from first line
		unsigned int vec_size;
		source_file >> vec_size;
		vec.resize(vec_size);

		// discard nonzero percentage
		source_file.ignore(1000, '\n');

		// read numbers one by one
		for (unsigned int i=0; i < vec_size; i++) {
			source_file >> vec[i];
		}
		source_file.close();

	} else {
		std::cout << "Unable to open file \"" << filename << "\"\n";
	}

	return vec;
}

double getPercentageFromFile(std::string filename) {
	std::ifstream source_file (filename);
	double nonzeropercentage;

	if (source_file.is_open()) {		
		// discard vector size from first line
		source_file.ignore(1000, ' ');

		// read nonzero percentage
		source_file >> nonzeropercentage;

		source_file.close();

	} else {
		std::cout << "Unable to open file \"" << filename << "\"\n";
		nonzeropercentage = -1;
	}

	return nonzeropercentage;
}

