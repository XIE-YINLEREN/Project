#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

class man
{
public:
	man(int id = 0, int money = 0) :id(id), money(money) {};
	int money;
	int id;
};

int main()
{

	man Danny;
	cout << "��ӭ����������" << endl;
	cout << "ȡ��" << endl;
	srand((unsigned)time(NULL));
	Danny.id = rand() % 51;
	Danny.money = rand() % 100000;
	cout << "���ĺ���Ϊ  " << Danny.id << endl;
	srand((unsigned)time(NULL));
	int num = rand() % 11;
	cout << "����ǰ�滹��  " << num << " ����" << endl;

	while (num > 0)
	{
		_sleep(1000);
		num--;
		cout << "����ǰ�滹��  " << num << " ����" << endl;
	}

	deque<man> A;
	A.push_back(Danny);
	deque<man>::iterator B = A.begin();


	system("cls");
	cout << "��ӭ��" << B->id << "���û�" << endl;
	cout << "1.��Ǯ" << endl;
	cout << "2.ȡǮ" << endl;
	int flag = 0;
	cin >> flag;
	if (flag == 1)
	{
		int money = 0;
		cout << "�����Ǯ" << endl;
		cin >> money;
		B->money += money;
		cout << "�����˻��ﻹ��" << B->money << endl;
	}
	else if (flag == 2)
	{
		int money = 0;
		cout << "ȡ����Ǯ" << endl;
		cin >> money;
		if (B->money < money)
		{
			cout << "��û����ô��Ǯ" << endl;
		}
		else
		{
			B->money -= money;
		}
		cout << "�����˻��ﻹ��" << B->money << endl;
	}
	else
	{
		cout << "�������" << endl;
	}

	return 0;
}