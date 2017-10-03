#include "randomized.hpp"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

/**
 * Flip a coin until a head is found, then return the number of tails
 */
unsigned long int flipCoinsUntilHeads() {
	unsigned long int tails = 0;
	// use the highest bits for better randomness
	while (rand() / (RAND_MAX / 2 + 1) == 0) {
		tails++;
	}
	return tails;
}

//TODO: e' giusto passare un vettore come parametro? (performance?)
unsigned long int produceAnEstimate(std::vector<unsigned long long int> addends) {
	//TODO: parallelizzare
	// dividi vettore per x processori
	// ogni processore
	//    per ogni numero non-zero esegui flipCoinsUntilHeads
	// max_tails shared tra thread
	//TODO: compare_and_swap
	unsigned long int max_tails = 0;
	for (unsigned long long int addend : addends) {
		if (addend != 0){
			unsigned long int new_tails = flipCoinsUntilHeads();
			if (new_tails > max_tails) {
				max_tails = new_tails;
			}
		}
	}
	return max_tails;
}

unsigned long long int randomizedSum(std::vector<unsigned long long int> addends, unsigned int k, unsigned int a, unsigned int d) {

	// Estimation
	srand((unsigned int) time(NULL));

	std::vector<unsigned long int> estimates;
	estimates.resize(k);
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

	// ifdef DEBUG
	unsigned long int actual = 0;
	for (unsigned long long int addend: addends) {
		if (addend != 0) {
			actual++;
		}
	}
	std::cout << "size " << addends.size() << std::endl;
	std::cout << "Estimate: " << m << std::endl;
	std::cout << "Actual: " << actual << std::endl;
	// endif

	// Addition
	unsigned long long int sum = 0;
	return sum;
}