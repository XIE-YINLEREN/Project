#include <iostream>
#include <cstring>
#include <string>
#include <fstream>


using namespace std;


class MyClass :public exception
{
public:
	const char* what() const throw() //不可以抛异常
	{
		cout << "Hello" << endl;
		return "OK";
	}
};


int main()
{
	try
	{
		MyClass A;
		throw A;
	}
	catch (const std::exception& E)
	{
		cout << E.what() << endl;
	}
	return  0;
}

