#include "parallel.hpp"
#include <cmath>
#include <vector>
#include <iostream>

unsigned long long int parallelSum(std::vector<unsigned long long int> addends) {
	
	unsigned long long int sum = 0;
	int n= addends.size();
		std::cout << n << "\n";
	
	for(int h=1; h<= (int)log2(n)+1; h++){
		//numero di elementi del sottoarray dispari
		if((n/(1<<h-1))%2!=0)
		{
			for(int i=1; i<=(n/(1<<h)) + (n/(1<<h-1))%2; i++){
				
				unsigned long long int x=addends[2*i-2];
				unsigned long long int y=addends[2*i-1];
				unsigned long long int z= x+y;
				addends[i-1]=z;	
					std::cout << "dispari\n";
			}
			addends[n/(1<<h)+(n/(1<<h-1))%2]= addends[n/(1<<h-1) + (n/(1<<h-2))%2];
		}
		//numero di elementi del sottoarray pari
		else
		{	
			for(int i=1; i<=n/(1<<h) + n%(1<<h); i++){
				
				unsigned long long int x=addends[2*i-2];
				unsigned long long int y=addends[2*i-1];
				unsigned long long int z= x+y;
					std::cout  << x <<"\n"<< y<<"\n" <<z <<"\n";
				addends[i-1]=z;	
					std::cout << "pari\n";
			}
		}
		
		for(unsigned long long int addend: addends){
			std::cout << addend <<" ";
		}
		std::cout <<"\n";
	}
	sum=addends[0];
	return sum;
}

