#include "main.h"

////��a�еĴ�a.begin()������������a.end()��������������Ԫ�ؽ��д�С��������
//sort(a.begin(), a.end());
////��a�еĴ�a.begin()������������a.end()��������������Ԫ�ص��ã��������У���a��Ԫ��Ϊ1,3,2,4,���ú�Ϊ4,2,3,1
//reverse(a.begin(), a.end());
////��a�еĴ�a.begin()������������a.end()��������������Ԫ�ظ��Ƶ�b�У���b.begin()+1��λ�ã�����������ʼ���ƣ����ǵ�ԭ��Ԫ��
//copy(a.begin(), a.end(), b.begin() + 1);
////��a�еĴ�a.begin()������������a.end()��������������Ԫ���в���10�������ڷ������������е�λ��
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
