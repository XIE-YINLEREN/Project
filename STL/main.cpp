#include "main.h"

void Vector_Binary_Fun()
{
	vector<int> Vec;
	Vector_To_Binary(Vec, 10);
	int i = 0;
	for (auto it = Vec.begin(); it != Vec.end(); it++, i++)
	{
		cout << *it << "  " << i << endl;
	}
}

void Vector_Delete_Fun()
{
	vector<int> Vec;
	for (int i = 0; i < 10; i++)
	{
		Vec.push_back(i);
	}
	Vector_Delete(Vec, 6);

	for (auto it = Vec.begin(); it != Vec.end(); it++)
	{
		cout << *it << "  " << endl;
	}
}

void Vector_Rand_Input()
{
	vector<int> Vec;
	int flag;
	cout << "输入5个数" << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> flag;
		Vec.push_back(flag);
	}
	Vector_Sort(Vec);
}

void String_Separation_Input()
{
	string str;
	getline(cin, str);//cin >> str;
	string C;
	cout << "要从什么分离" << endl;
	getline(cin, C);
	Separation(str, C);
}
int main()
{
	//Vector_Binary_Fun();//二进制1的个数
	//Vector_Delete_Fun();//删除一个元素 
	//Vector_Rand_Input();//随机输入后排序
	//String_Separation_Input();//分离string
	//Combind("123", "234");合并
	//Map_Insert();
	//Map_Find();
}