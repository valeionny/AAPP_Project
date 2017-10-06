#include "parallel.hpp"
#include <cmath>
#include <vector>
#include <iostream>

unsigned long long int parallelSum(std::vector<unsigned long long int> addends) {
	
	unsigned long long int sum = 0;
	int n= addends.size();
	std::cout << n << "\n";
	
	while(n!=1){
	
		int i=0;
		for(i=0; i<n/2; i++){
		
			addends[i]=addends[2*i]+addends[2*i+1];	
			std::cout << "ciclo \n";
		}
		
		if(n%2!=0){
			
			addends[i]= addends[2*i];
		}
		
		n=(n+1)/2;

		
		for(unsigned long long int addend: addends){
			std::cout << addend <<" ";
		}
		std::cout <<"\n";
	}
	sum=addends[0];
	return sum;
}

