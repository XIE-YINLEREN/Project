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
	cout << "1.���ѧ����Ϣ" << endl;
	cout << "2.ɾ��ѧ����Ϣ" << endl;
	cout << "3.�޸�ѧ����Ϣ" << endl;
	cout << "4.��ӡѧ����Ϣ" << endl;
	cout << "5.�˳�ѧ��ϵͳ" << endl;
}
void fun1(list<student>& X)
{
	int age = 0, id = 0;
	cout << "����" << endl;
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
	cout << "Ҫɾ��ѧ����ID��" << endl;
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
	cout << "Ҫ�޸�ѧ����ID��" << endl;
	cin >> id;
	cout << "�޸�ѧ��������" << endl;
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
	cout << "����  " << "ID  " << endl;
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