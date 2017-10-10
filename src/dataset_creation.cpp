#include "dataset_creation.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#define ULONG 18446744073709551615ull

unsigned long long int generateNumber(unsigned long long int max_value) {
	// create a 64 bits number bit by bit
	unsigned long long int sum = 0;
	for(int j=0; j < (int)(log2(max_value)); j++)
	{
		sum = (sum << 1) + (rand() % 2);
	}
	return sum;
}

std::vector<unsigned long long int> createDataset(unsigned long int tot_num, double non_zero_percentage) {

	std::vector<unsigned long long int> vec;

	if (non_zero_percentage > 100) {
		std::cout << "The non-zero percentage provided is too high! (" << non_zero_percentage << ")\n";
		return vec;
	}

	vec.resize(tot_num);
	unsigned long int non_zero = ( non_zero_percentage / 100) * tot_num;
	// we want to make sure that the sum doesn't overflow
	unsigned long long int max_value = ULONG / non_zero;
	
	srand((unsigned long long int)time(NULL));
	
	if (tot_num < 1000)
	{
		for(unsigned long int i=0; i < tot_num; i++)
		{
			if (i < non_zero)
				vec[i] = generateNumber(max_value);
			else 
				vec[i] = 0;
		}
		
		std::random_shuffle(vec.begin(), vec.end());
	}
	
	else
	{
		// probabilistic choice between zero and non-zero
		int rand_threshold = RAND_MAX * ( non_zero_percentage / 100);
		for(int i=0; i < tot_num; i++)
		{	
			if(rand() < rand_threshold)
				// max_value/10 to really be sure that there won't be any overflows
				vec[i] = generateNumber(max_value / 10);
			else
				vec[i] = 0;
		}
	}

	return vec;
}
