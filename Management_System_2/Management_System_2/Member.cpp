#include"Member.h"
#include"File.h"

LinkList* Link_Init()
{
	LinkList* head = (LinkList*)malloc(sizeof(LinkList));
	if (head == NULL)
	{
		printf("内存分配失败");
		exit(-1);
	}
	head->after = NULL;
	head->before = NULL;
	head->data_member = NULL;
	head->data_personnel = NULL;
	return head;
}

void Member_Create(LinkList **head)
{
	LinkList* P = FileRead();
	Member* NewData = (Member*)((*head)->data_member);
	Member* OldData = (Member*)(P->data_member);

	printf("输入你要新建职员的姓名:  ");
	gets_s((*NewData).name);
	printf("输入你要新建职员的年龄:  ");
	scanf_s("%d", &((*NewData).age));

	while (true)
	{
		if ((*NewData).age <= 65 && (*NewData).age >= 18)
		{
			break;
		}
		else
		{
			printf("输入有误请重新输入\n");
			scanf_s("%d", &((*NewData).age));
		}
	}
	printf("输入你要新建职员的工号\n");
	printf("工号为五位数，最后一位奇数为女，偶数为男:\n"); 
	gets_s((*NewData).number);
	scanf_s("%s", (*NewData).number);
	while (P != NULL)
	{
		if (strlen((*NewData).number) == 5 && P == NULL)
		{
			break;
		}
		if (0 == strcmp((*NewData).number, (*OldData).number) || strlen((*OldData).number) != 5)
		{
			printf("输入有误请重新输入: ");
			scanf_s("%s", (*NewData).number);
			P = FileRead();
		}
		P = P->after;
	}
	printf("输入你要新建职员的部门:  ");
	scanf_s("%s", (*NewData).department);
	printf("输入你要新建职员的薪水:  ");
	scanf_s("%d", &((*NewData).salary));
	(*NewData).bonus = 0;
	printf("创建成功");
}

void Member_Del(LinkList *head)
{
	head = FileRead();
	FileShow(head);
	LinkList* p ,*q;
	p = q = head;
	Member* Data = NULL;
	char num[20]{};
	printf("输入你要删除的职员的工号： ");
	scanf("%s", num);
	while (p != NULL)
	{
		Member* Data = (Member*)(p->data_member);
		if (0 == strcmp(Data->number, num))
		{
			if (p == head)
			{
				head = head->after;
				free(p);
				printf("删除成功");
				break;
			}
			else
			{
				q->after = p->after;
				free(p);
				printf("删除成功");
				break;
			}
		}
		q = p;
		p = p->after;
	}
	FileReWirte(head);
}

void Member_Modify(LinkList *head)
{

	{
		head = FileRead();
		FileShow(head);
		LinkList* p = head;
		Member* Data = (Member*)(p->data_member);
		char num[20]{};
		char buff[20]{};
		int To_flag = -1;
		char flag_1[254]{};
		int flag = -1;
		printf("输入你要修改的职工的工号:  ");
		gets_s(num);

		while (p != NULL)
		{
			if (0 == strcmp(Data->number, num))
			{
				system("cls");
				printf("该职工已找到\n");
				printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
				break;
			}
			p = p->after;
		}
		if (Data == NULL)
		{
			printf("未找到改职员");
			return;
		}
		printf("输入你要修改的内容\n");
		printf("1.姓名 2.年龄 3.部门 4.薪水 5.奖金\n");
		while (true)
		{
			gets_s(flag_1);
			flag = (*flag_1) - 48;
			switch (flag)
			{
			case 1:
			{
				printf("将 %s 修改为: ", Data->name);
				gets_s(buff);
				strcpy(Data->name, buff);
				FileReWirte(head);
				printf("修改成功");
				return;
			}
			case 2:
			{
				printf("将 %d 修改为: ", Data->age);
				scanf_s("%d", &To_flag);
				Data->age = To_flag;
				FileReWirte(head);
				printf("修改成功");
				return;
			}
			case 3:
			{
				printf("将 %s 修改为: ", Data->department);
				gets_s(buff);
				strcpy(Data->department, buff);
				FileReWirte(head);
				printf("修改成功");
				return;
			}
			case 4:
			{
				printf("将 %d 修改为: ", Data->salary);
				scanf_s("%d", &To_flag);
				Data->salary = To_flag;
				FileReWirte(head);
				printf("修改成功");
				return;
			}
			case 5:
			{
				printf("将 %d 修改为: ", Data->bonus);
				scanf_s("%d", &To_flag);
				Data->bonus = To_flag;
				FileReWirte(head);
				printf("修改成功");
				return;
			}
			default:
			{
				printf("输入错误请重新输入");
			}
			}
		}

	}
}

void Member_Search()
{
	LinkList* head;
	head = FileRead();
	FileShow(head);
	Member* Data =  NULL;
	char num[20]{};
	printf("输入你要查找的职员的工号： ");
	gets_s(num);
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		if (0 == strcmp(Data->number, num))
		{
			printf("该职工已找到\n");
			printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name,Data->age, Data->number, Data->department, Data->salary, Data->bonus);
			break;
		}
		head = head->after;
	}
	if (head == NULL)
	{
		printf("该职工未找到\n");
	}
	
}

void Member_Bonus()
{
	LinkList* head, * p;
	Member* Data = NULL;
	p = head = FileRead();
	FileShow(head);
	int money = 0;
	char num[20]{};
	printf("输入要加奖金的职员的工号： ");
	gets_s(num);
	printf("奖金： ");
	scanf("%d", &money);
	while (p != NULL)
	{
		Data = (Member*)(p->data_member);
		if (0 == strcmp(Data->number, num))
		{
			Data->bonus += money;
			printf("奖金记录成功");
			break;
		}
		p = p->after;
	}
	if (p == NULL)
	{
		printf("工号：%s 没有数据", num);
		return;
	}
	FileReWirte(head);
}

void Algorithm_AverageSalary()
{
	LinkList* head = FileRead();
	FileShow(head);
	Member* Data = NULL;
	long int AverageSalary = 0;
	int flag = 0;
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		AverageSalary += Data->salary;
		head = head->after;
		flag++;
	}
	printf("职员的平均工资为%d", AverageSalary / flag);
}

void Ascending_Sort()
{
	LinkList* head, *p,*q;
	head = p = q = FileRead();
	Member* Data_Q = NULL;
	Member* Data_P = NULL;
	int flag = -1;
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (q != NULL)
	{
		Data_Q = (Member*)(q->data_member);
		p = head;
		flag = Data_Q->salary;
		while (p != NULL)
		{
			Data_P = (Member*)(p->data_member);
			if (Data_P->salary > flag)
			{
				flag = Data_P->salary;
			}
			p = p->after;
		}
		p = head;
		while (p != NULL)
		{
			Data_P = (Member*)(p->data_member);
			if (Data_P->salary == flag && Data_P->salary != -1)
			{
				printf("%s\t%d\t%s\t%s\t%d\t%d\n",
					Data_P->name, Data_P->age, Data_P->number,
					Data_P->department, Data_P->salary, Data_P->bonus);
				Data_P->salary = -1;
			}
			p = p->after;
		}
		q = q->after;
	}
}

void Descending_Sort()
{
	LinkList* head, * p, * q;
	head = p = q = FileRead();
	Member* Data_Q = NULL;
	Member* Data_P = NULL;
	int flag = -1;
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (q != NULL)
	{
		Data_Q = (Member*)(q->data_member);
		p = head;
		flag = Data_Q->salary;
		while (p != NULL)
		{
			Data_P = (Member*)(p->data_member);
			if (Data_P->salary < flag)
			{
				flag = Data_P->salary;
			}
			p = p->after;
		}
		p = head;
		while (p != NULL)
		{
			Data_P = (Member*)(p->data_member);
			if (Data_P->salary == flag && Data_P->salary != -1)
			{
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", 
					Data_P->name, Data_P->age, Data_P->number, 
					Data_P->department, Data_P->salary, Data_P->bonus);
				Data_P->salary = 65535;
			}
			p = p->after;
		}
		q = q->after;
	}
}
