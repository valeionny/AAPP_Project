#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#define LENGTH 100
#define ULONG 18446744073709551615
using namespace std;

int main()
{
	vector<unsigned long long int> addends;
	unsigned long long int random;
	unsigned long long int sum=0;
	srand((unsigned long long int)time(NULL));
	
	unsigned long long int max_value = (unsigned long long int)ULONG/(unsigned long long int)LENGTH;
	
	for(int i=0; i<LENGTH; i++)
	{
		random=rand();
		//cout<< std::to_string(random)<< "\n";
		
		if(random<0.7*RAND_MAX)
			addends.push_back(0);
		else
			addends.push_back((max_value/RAND_MAX)*random);	
	}
	for(unsigned long long int addend: addends){
		cout<< std::to_string(addend)<<"  ";
		
	}
	
	for(unsigned long long int addend: addends){
		sum+=addend;
	}
	cout<< "\n\n"<< std::to_string(sum)<<"\n";
	//cout<< std::to_string(ULONG)<<"\n";
	printf("%llu", (unsigned long long int)ULONG);
	return 0;
} 


