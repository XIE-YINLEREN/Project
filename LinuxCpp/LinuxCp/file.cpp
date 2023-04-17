#include <iostream>
#include <fstream>
using namespace std;

class MyClass
{
public:
	MyClass(int num, int age)
	{
		this->age = age;
		this->num = num;
	}
	int num;
	int age;
};

int main()
{
	MyClass A(1, 3);
	ofstream B("abc", ios::out | ios::binary);
	if (!B.is_open())
	{
		cout << "123123" << endl;
		return 0;
	}
	B.write((char*)&A.age, sizeof(A.age));
	B.write((char*)&A.num, sizeof(A.num));
	B.close();

	ifstream C("abc", ios::in | ios::binary);
	if (!C.is_open())
	{
		cout << "123123" << endl;
		return 0;
	}
	int buf1 = 0, buf2 = 0;
	C.read((char*)&buf1, sizeof(A.age));
	C.read((char*)&buf2, sizeof(A.num));

	cout << buf1 << "   " << buf2 << endl;
	C.close();
	return 0;
}