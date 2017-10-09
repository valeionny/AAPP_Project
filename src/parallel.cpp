#include "parallel.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <omp.h>

unsigned long long int parallelSum(std::vector<unsigned long long int> &addends) {
	
	unsigned long long int sum = 0;
	int n= addends.size();
	std::cout << n << "\n";
	int j=0;
	//all the logarithmic sum
	while(n!=1){
	 
		unsigned int i=0;
		//eaxh step of the sum put the new numbers in esponential position to avoid thread overlapping in writing variables 
		#pragma omp parallel for 
		for(i=0; i<n/2; i++){
			
			addends[(1<<j+1)*i]=addends[(1<<j+1)*i]+addends[(1<<j+1)*i+(1<<j)];	
		}
		
		n=(n+1)/2;
		j++;
	
	}
	//the result is finally put in the first element of the vector		
	sum=addends[0];
	return sum;
}

