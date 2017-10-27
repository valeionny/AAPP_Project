#ifndef randomized_h
#define randomized_h

#include <vector>

unsigned long long int randomizedSum(std::vector<unsigned long long int> &addends, unsigned int k=10, unsigned int a=4, unsigned int d=1);
unsigned long long int randomizedSumWithSeed(std::vector<unsigned long long int> &addends, unsigned long int seed, unsigned int k=10, unsigned int a=4, unsigned int d=1);

#endif