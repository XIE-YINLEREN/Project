#include "main.h"

void Separation(string str,string C)
{
	string A, B; 

	int it = str.find(C);
	A.append(str.begin(), str.begin() + it);
	B.append(str.begin() + it + C.length(), str.end());

	cout << A << endl;
	cout << B << endl;
}

void Combind(string A, string B)
{
	string C = A + "&&" + B;
	cout << C;
}