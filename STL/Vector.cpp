#include "main.h"

////对a中的从a.begin()（包括它）到a.end()（不包括它）的元素进行从小到大排列
//sort(a.begin(), a.end());
////对a中的从a.begin()（包括它）到a.end()（不包括它）的元素倒置，但不排列，如a中元素为1,3,2,4,倒置后为4,2,3,1
//reverse(a.begin(), a.end());
////把a中的从a.begin()（包括它）到a.end()（不包括它）的元素复制到b中，从b.begin()+1的位置（包括它）开始复制，覆盖掉原有元素
//copy(a.begin(), a.end(), b.begin() + 1);
////在a中的从a.begin()（包括它）到a.end()（不包括它）的元素中查找10，若存在返回其在向量中的位置
//find(a.begin(), a.end(), 10);

void Vector_To_Binary(vector<int>& Vec, int n)
{
	for (int i = 0; i < n; i++)
	{
		int flag = 0;
		for (int j = i; j; j /= 2)
		{
			if (j % 2 == 1)
			{
				flag++;
			}
		}
		Vec.push_back(flag);
	}
}

void Vector_Delete(vector<int>& Vec, int n)
{
	for (auto it = Vec.begin(); it != Vec.end(); it++)
	{
		if (*it == n)
		{
			it = Vec.erase(it);
		}
	}
}

void Vector_Sort(vector<int>& Vec)
{
	sort(Vec.begin(), Vec.end());
	for (auto it = Vec.begin(); it != Vec.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
