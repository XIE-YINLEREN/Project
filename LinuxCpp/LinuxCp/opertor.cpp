#include <iostream>
#include <cstring>

using namespace std;

class MyClass
{
public:
	MyClass(int num);
	int Get();
	friend class MyDemo;
	MyClass operator>(MyClass& other);
private:
	int num;
};

class MyDemo
{
public:
	int sum;
	MyDemo(int num, int sum);
	int Get();
	void ShowOther(MyClass& X);
	void operator++(int X);
private:
	int num;
};

MyDemo::MyDemo(int num = 0, int sum = 0)
{
	this->num = num;
}

int MyDemo::Get()
{
	return this->num;
}

void MyDemo::ShowOther(MyClass& X)
{
	cout << X.num << endl;
}

void MyDemo::operator++(int X)
{
	X++;
	sum = X;
}

MyClass::MyClass(int num = 0)
{
	this->num = num;
}

int MyClass::Get()
{
	return num;
}

MyClass MyClass::operator>(MyClass& other)
{
	MyClass test;
	if (this->num > other.num)
	{
		return *this;
	}
	else
	{
		return other;
	}
}

//MyClass A(10);
//MyClass B(2);
//MyDemo  H(10, 10);
//
//MyClass C = A > B;
//H.ShowOther(B);
//cout << C.Get() << endl;
//
//H.operator++(5);
//cout << H.sum << endl;
//H++;
//cout << H.sum << endl;
//H++;
//cout << H.sum << endl;