#ifndef file_procs_h
#define file_procs_h

#include <vector>
#include <string>

int saveToFile(std::vector<unsigned long long int> vec, double nonzeropercentage, std::string filename);

std::vector<unsigned long long int> loadFromFile(std::string filename);

double getPercentageFromFile(std::string filename);

#endif