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
	cout << "欢迎来到本银行" << endl;
	cout << "取号" << endl;
	srand((unsigned)time(NULL));
	Danny.id = rand() % 51;
	Danny.money = rand() % 100000;
	cout << "您的号码为  " << Danny.id << endl;
	srand((unsigned)time(NULL));
	int num = rand() % 11;
	cout << "您的前面还有  " << num << " 个人" << endl;

	while (num > 0)
	{
		_sleep(1000);
		num--;
		cout << "您的前面还有  " << num << " 个人" << endl;
	}

	deque<man> A;
	A.push_back(Danny);
	deque<man>::iterator B = A.begin();


	system("cls");
	cout << "欢迎您" << B->id << "号用户" << endl;
	cout << "1.存钱" << endl;
	cout << "2.取钱" << endl;
	int flag = 0;
	cin >> flag;
	if (flag == 1)
	{
		int money = 0;
		cout << "存多少钱" << endl;
		cin >> money;
		B->money += money;
		cout << "您的账户里还有" << B->money << endl;
	}
	else if (flag == 2)
	{
		int money = 0;
		cout << "取多少钱" << endl;
		cin >> money;
		if (B->money < money)
		{
			cout << "您没有这么多钱" << endl;
		}
		else
		{
			B->money -= money;
		}
		cout << "您的账户里还有" << B->money << endl;
	}
	else
	{
		cout << "输入错误" << endl;
	}

	return 0;
}