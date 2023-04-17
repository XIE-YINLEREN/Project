#pragma once
#include <iostream>
using namespace std;

template<class T>
class MyClass
{
public:
    T M;
    MyClass(T M = 0) :M(M) {}
    void show()
    {
        cout << M << endl;
    }

};

void fun1(MyClass<int>& other)
{
    other.show();
}

template<class T>
void fun2(MyClass<T>& other)
{
    other.show();
}

template<class T>
void fun3(T& other)
{
    other.show();
}


int main()
{
    MyClass<int> Danny;
    fun1(Danny);
    fun2(Danny);
    fun3<MyClass<int>>(Danny);
    return 0;
}
