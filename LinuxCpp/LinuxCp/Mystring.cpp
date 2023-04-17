#pragma once
#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
public:
	MyString(char* _str);
	MyString(const MyString& other);
	~MyString();
	int GetLen();
	void SetStr(char* _str);
private:
	char* str;
	int   len;
};


MyString::MyString(char* _str = "")
{
	len = strlen(_str);
	str = new char[len + 1];
	strcpy(str, _str);
}

MyString::MyString(const MyString& other)
{
	len = other.len;
	if (this == &other)
	{
		return;
	} 
	else
	{
		if (str != nullptr)
		{
			delete str;
		}
		str = new char[len + 1];
		strcpy(str, other.str);
	}
}


int MyString::GetLen()
{
	return len;
}

void MyString::SetStr(char* _str)
{
	delete[] str;
	len = strlen(_str);
	str = new char[len + 1];
	strcpy(str, _str);
}


MyString:: ~MyString()
{
	delete[] str;
}
