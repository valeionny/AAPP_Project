// MIT License
//
// Copyright (c) 2017 Valentina Ionata, Pietro Ferretti
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "parallel.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <omp.h>

unsigned long long int parallelSum(std::vector<unsigned long long int> &addends) {

	unsigned long long int sum = 0;
	unsigned long int n= addends.size();

	int j=0;
	//all the logarithmic sum
	while(n!=1){

		unsigned long int i=0;
		//each step of the sum put the new numbers in esponential position to avoid thread overlapping in writing variables 
		#pragma omp parallel for 
		for(i=0; i<n/2; i++){

			addends[(1<<(j+1))*i]=addends[(1<<(j+1))*i]+addends[(1<<(j+1))*i+(1<<j)];
		}

		n=(n+1)/2;
		j++;

	}
	//the result is finally put in the first element of the vector
	sum=addends[0];
	return sum;
}

