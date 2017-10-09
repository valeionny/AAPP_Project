#include "serial.hpp"
#include <vector>

unsigned long long int serialSum(std::vector<unsigned long long int> &addends) {
	unsigned long long int sum = 0;
	for(unsigned long long int addend: addends){
		sum += addend;
	}
	return sum;
}
