#pragma
#include <iostream>
#include <cstring>

using namespace std;

class Man
{
public:
	Man(int num);
	~Man();
	static int getum();
private:
	static int num;
};

Man::Man(int num)
{
	this->num = num;
}

Man::~Man()
{
}

int Man::getum()
{
	return num;
}