#pragma once 
#include <iostream> 
using namespace std; 

class man 
{ 
public: 
	int M;
	man(int M = 0) :M(M)
	{}
	man operator= (const man& other)
	{
		man p = other;
		this->M = p.M;
		return p;
	}
	man operator[](int x)
	{
		M = x;
		man p = *this;
		p.M = this->M;
		return p;
	}
}; 


