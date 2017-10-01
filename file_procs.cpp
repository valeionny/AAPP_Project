#include <fstream>
#include <iostream>
#include "file_procs.hpp"

int saveToFile(std::vector<unsigned long long int> vec, std::string filename) {
	std::ofstream target_file (filename);

	if (target_file.is_open()) {
		// write size of vector in first line
		target_file << vec.size() << '\n';

		// write numbers separated by a space
		for (unsigned long long int elem: vec) {
			target_file << elem << ' ';
		}
		target_file.close();

	} else {
		std::cout << "Unable to open file \"" << filename << "\"";
		return 1;
	}

	return 0;
}

std::vector<unsigned long long int> loadFromFile(std::string filename) {
	std::ifstream source_file (filename);
	unsigned int vec_size;
	std::vector<unsigned long long int> vec;
	unsigned long long int curr_num;

	if (source_file.is_open()) {
		// read vector size from first line
		source_file >> vec_size;
		vec.resize(vec_size);

		// read numbers one by one
		for (unsigned int i=0; i < vec_size; i++) {
			source_file >> curr_num;
			vec.push_back(curr_num);
		}
		source_file.close();

	} else {
		std::cout << "Unable to open file \"" << filename << "\"";
	}

	return vec;
}
