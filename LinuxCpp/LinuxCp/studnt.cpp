#pragma once
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class student
{
public:
	student(int age = 0, int id = 0) :age(age), id(id) {};
	int age;
	int id;
};
void fun()
{
	cout << "1.添加学生信息" << endl;
	cout << "2.删除学生信息" << endl;
	cout << "3.修改学生信息" << endl;
	cout << "4.打印学生信息" << endl;
	cout << "5.退出学生系统" << endl;
}
void fun1(list<student>& X)
{
	int age = 0, id = 0;
	cout << "年龄" << endl;
	cin >> age;
	cout << "ID" << endl;
	cin >> id;
	student C;
	C.age = age;
	C.id = id;
	X.push_back(C);
}
void fun2(list<student>& X)
{
	int id;
	cout << "要删除学生的ID是" << endl;
	cin >> id;
	for (list<student>::iterator A = X.begin(); A != X.end(); A++)
	{
		if (A->id == id)
		{
			X.erase(A);
			return;
		}
	}
}

void fun3(list<student>& A)
{
	int id, age;
	cout << "要修改学生的ID是" << endl;
	cin >> id;
	cout << "修改学生的年龄" << endl;
	cin >> age;
	for (list<student>::iterator X = A.begin(); X != A.end(); X++)
	{
		if (X->id == id)
		{
			X->age = age;
			return;
		}
	}
}

void fun4(list<student> A)
{
	list<student>::iterator X = A.begin();
	cout << "年龄  " << "ID  " << endl;
	for (int i = 0; i < A.size(); i++)
	{
		cout << X->age << "    " << X->id << endl;
		X++;
	}
}


int main()
{
	list<student> A;


	int flag = 0;
	while (true)
	{
		system("cls");
		fun();
		cin >> flag;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			fun1(A);
			break;
		}
		case 2:
		{
			system("cls");
			fun2(A);
			break;
		}
		case 3:
		{
			system("cls");
			fun3(A);
			break;
		}
		case 4:
		{
			system("cls");
			fun4(A);
			flag = getchar();
			flag = getchar();
			break;
		}
		case 5:
		{
			exit(-1);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}