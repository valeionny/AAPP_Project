#include "randomized.hpp"
#include "parallel.hpp"
#include "parallel.cpp"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <climits>
#include <omp.h>
#include <trng/lcg64.hpp>
#include <trng/uniform01_dist.hpp>

/**
 * Flip a coin until a head is found, then return the number of tails
 */
unsigned long int flipCoinsUntilHeads(trng::lcg64 &r) {
	trng::uniform01_dist<> u;    // uniform distribution from 0 to 1
	unsigned long int tails = 0;
	while (((unsigned int) (u(r) * 100)) % 2 == 0) {
		tails++;
	}
	return tails;
}

unsigned long int produceAnEstimate(std::vector<unsigned long long int> const &addends, unsigned long int seed) {
	unsigned long int max_tails = 0;
	unsigned int n = addends.size();
	#pragma omp parallel
	{
		// random engine
		trng::lcg64 r;    // build a new prng engine to avoid splitting the main one
		r.seed(seed);
		#ifdef _OPENMP
			int size = omp_get_num_threads();    // total number of threads
			int rank = omp_get_thread_num();     // number of current thread
		#else
			std::cout << "OpenMP not found. Remember to compile with the -fopenmp flag!" << std::endl;
			int size = 1;
			int rank = 1;
		#endif
		r.split(size, rank);        // choose sub-stream no. rank out of size streams

		#pragma omp for
		for (unsigned int i=0; i < n; i++) {
			if (addends[i] != 0){
				unsigned long int new_tails = flipCoinsUntilHeads(r);

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
				// without gcc
				#else
				{
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

unsigned long long int randomizedSumWithSeed(std::vector<unsigned long long int> &addends, unsigned long int seed, unsigned int k, unsigned int a, unsigned int d) {

	// Initialization of the random number generator
	// used to seed different estimations and memory marking steps
	trng::lcg64 r;             // prng engine
	trng::uniform01_dist<> u;  // uniform distribution from 0 to 1
	r.seed(seed);

	// Estimation

	// run produce-an-estimate k times
	std::vector<unsigned long int> estimates (k);
	for (unsigned int i=0; i < k; i++) {
		unsigned long int seed = u(r) * ULONG_MAX;
		estimates[i] = produceAnEstimate(addends, seed);
	}

	// apply formula to find m'
	unsigned long int sum_of_estimates = 0;
	for (unsigned long int e: estimates) {
		sum_of_estimates += e;
	}
	double E = log(2) * ((double) sum_of_estimates / k);
	unsigned long int m = exp(2) * exp(E) + d;

	#ifdef DEBUG 
		// Alternative estimate (using approximate fit) 
		unsigned long int mm = pow(2.0, (double) sum_of_estimates / k -1 + 0.6667) + d;

		unsigned long int actual = 0;
		for (unsigned long long int addend: addends) {
			if (addend != 0) {
				actual++;
			}
		}
		std::cout << "Estimate: " << m << std::endl;
		std::cout << "Alternative: " << mm << std::endl;
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
		// divide prng streams
		#ifdef _OPENMP
			int size = omp_get_num_threads();    // total number of threads
			int rank = omp_get_thread_num();     // number of current thread
		#else
			std::cout << "OpenMP not found. Remember to compile with the -fopenmp flag!" << std::endl;
			int size = 1;
			int rank = 1;
		#endif
		r.split(size, rank);        // choose sub-stream no. rank out of size streams

		#pragma omp for
		for (unsigned int i=0; i < n; i++) {
			if (addends[i] != 0) {
				// keep trying to write on new vector
				bool done = false;
				while (!done) {
					unsigned long int index = ((unsigned long int) (u(r) * red_size)) % red_size;
					// gcc version
					#ifdef __GNUC__
						if (reduced_vector[index] == 0) {
							if (__sync_bool_compare_and_swap(&reduced_vector[index], 0, addends[i])) {
								done = true;
							}
						}
					// without gcc
					#else
						#pragma omp critical(reduced_vector)
						{
							if (reduced_vector[index] == 0) {
								reduced_vector[index] = addends[i];
								done = true;
							}
						}
					#endif
				}
			}
		}
	}

	// parallel sum
	unsigned long long int sum = parallelSum(reduced_vector);

	return sum;
}

unsigned long long int randomizedSum(std::vector<unsigned long long int> &addends, unsigned int k, unsigned int a, unsigned int d) {
	// wrapper to call randomizedSum without a seed
	return randomizedSumWithSeed(addends, (unsigned long int) time(NULL), k, a, d);
}
