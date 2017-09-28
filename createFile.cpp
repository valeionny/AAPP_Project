#include <iostream>
#include <string>         
#include <bitset> 
#include <vector>
#include <ctime>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#define ULONG 18446744073709551615

int main(int argc, char *argv[])
{
	std::vector<unsigned long long int> addends;

	unsigned long long int random;
	
	srand((unsigned long long int)time(NULL));
	//argv[1] contiene il tot dei numeri, argv[2] la percentuale in numeri compresi tra[0,100], vedere come compilare
	//non_zero è il numero di non zeri
	int non_zero = (int)(/*atoi(argv[1])*/50*/*atoi(argv[2])*/10/100);
	
	for(int i=0;i</*atoi(argv[1])*/50;i++){
		if(i<non_zero){
			//
			unsigned long long int sum;
			for(int j=0; j<(int)(log2(pow(2,63)/non_zero));j++)
			{
				sum+=(pow(2,j)*(rand()%2));
			}
			addends.push_back(sum);
		}
		else addends.push_back(0);
	}
	std::random_shuffle(addends.begin(),addends.end());
	
	for(unsigned long long int n : addends) {
		std::cout<< std::to_string(n)<<"\n";
	}
	
	//stampare su file 
	return 0;
}
