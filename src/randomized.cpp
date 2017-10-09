#include "randomized.hpp"
#include "parallel.hpp"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <atomic>

// temporaneo mentre scriviamo la somma parallela
#include "serial.cpp"

//TODO! usa una libreria migliore per random

/**
 * Flip a coin until a head is found, then return the number of tails
 */
unsigned long int flipCoinsUntilHeads() {
	unsigned long int tails = 0;
	while (rand() % 2 == 0) {
		tails++;
	}
	return tails;
}

unsigned long int produceAnEstimate(std::vector<unsigned long long int> const &addends) {

	unsigned long int max_tails = 0;
	unsigned int n = addends.size();
	#pragma omp parallel
	{
		#pragma omp for
		for (unsigned int i=0; i < n; i++) {
			if (addends[i] != 0){
				unsigned long int new_tails = flipCoinsUntilHeads();

				// gcc version
				#ifdef __GNUC__
				{
					// keep trying to write on max_tails if the new result is higher
					while (1) {
						unsigned long int curr_tails = max_tails;
						if (new_tails > curr_tails) {
							if (__sync_bool_compare_and_swap(&max_tails, curr_tails, new_tails)) {
								break;    // swap successful
							};
						} else {
							break;
						}
					}
				}
				// not gcc/windows version -> "http://en.cppreference.com/w/cpp/atomic/atomic_compare_exchange"
				#else
				{
					//FIXME: replace con compare_and_swap
					// (actually it seems like the performance is comparable)
					#pragma omp critical (max_tails)
					{
						if (new_tails > max_tails) {
							max_tails = new_tails;
						}
					}
				}
				#endif
			}
		}
	}
	return max_tails;
}

unsigned long long int randomizedSum(std::vector<unsigned long long int> &addends, unsigned int k, unsigned int a, unsigned int d) {

	// Estimation
	srand((unsigned int) time(NULL));

	// run produce-an-estimate k times
	std::vector<unsigned long int> estimates (k);
	for (unsigned int i=0; i < k; i++) {
		estimates[i] = produceAnEstimate(addends);
	}

	// apply formula to find m'
	unsigned long int sum_of_estimates = 0;
	for (unsigned long int e: estimates) {
		sum_of_estimates += e;
	}
	double E = log(2) * ((double) sum_of_estimates / k);
	unsigned long int m = exp(2) * exp(E) + d;

	/* Alternative (using approximate fit)
	m = pow(2.0, (double) sum_of_estimates / k -1 + 0.6667) + d;
	*/

	#ifdef DEBUG 
		unsigned long int actual = 0;
		for (unsigned long long int addend: addends) {
			if (addend != 0) {
				actual++;
			}
		}
		std::cout << "Estimate: " << m << std::endl;
		std::cout << "Actual: " << actual << std::endl;
	#endif

	// Addition

	// initialize space
	unsigned long int red_size = m * a;
	std::vector<unsigned long long int> reduced_vector (red_size, 0);

	// memory marking
	unsigned int n = addends.size();
	#pragma omp parallel
	{
		#pragma omp for
		for (unsigned int i=0; i < n; i++) {
			if (addends[i] != 0) {
				// keep trying to write on new vector
				bool done = false;
				while (!done) {
					unsigned int index = rand() % red_size;
					//TODO compare and swap?
					#pragma omp critical(reduced_vector)
					{
						if (reduced_vector[index] == 0) {
							reduced_vector[index] = addends[i];
							done = true;
						}
					}
				}
			}
		}
	}

	// parallel sum
	unsigned long long int sum = parallelSum(reduced_vector);

	return sum;
}
