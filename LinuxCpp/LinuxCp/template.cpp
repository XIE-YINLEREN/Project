#pragma
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>


using namespace std;



class MyClass
{
public:
	MyClass(int a = 0)
	{
		this->a = a;
	}
	int a;
};


template <class T1, class T2>
void swap(T1& a, T2& b)
{
	T1 c;
	c = b;
	a = b;
	b = c;
}

int main()
{
	int A = 10;
	int B = 20;
	swap(A, B);
	cout << "A =" << A << endl;
	cout << "B =" << B << endl;

	MyClass C(5);
	MyClass D(10);
	swap(C, D);
	cout << "C =" << C.a << endl;
	cout << "D =" << D.a << endl;

	return  0;
}

