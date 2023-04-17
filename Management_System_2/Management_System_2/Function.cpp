#include"Function.h"
#include"File.h"


void Choice_Function_Member_Pre()
{
	printf("欢迎来到本功能，输入对应序列数字实现功能\n");
	printf("1.新建一个职工数据\n");
	printf("2.删除一个职工数据\n");
	printf("3.修改一个职工数据\n");
	printf("4.查找一个职工数据\n");
	printf("5.显示所有职工数据\n");
	printf("6.退出\n");
}

void Choice_Function_Member(LinkList* head)
{
	char flag_1[254]{};
	int flag = -1;
	while (true)
	{
		system("cls");
		Choice_Function_Member_Pre();
		gets_s(flag_1);
		flag = (*flag_1) - 48;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			Member_Create(&head);
			FileWirte(head);
			_getch();
			break;
		}
		case 2:
		{
			system("cls");
			Member_Del(head);
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			Member_Modify(head);
			_getch();
			break;
		}
		case 4:
		{
			system("cls");
			Member_Search();
			_getch();
			break;
		}
		case 5:
		{
			system("cls");
			FileShow(FileRead());
			_getch();
			break;
		}
		case 6:
		{
			return;
		}
		default:
		{
			printf("输入有误，重新输入");
			_getch();
			break;
		}
		}
	}
}

void Function_Main()
{
	printf("欢迎来到本程序，输入对应序列数字实现功能\n");
	printf("1.查看所有的职工\n");
	printf("2.对当前职工数据增删查改\n");
	printf("3.按情况查看职工数据\n");
	printf("4.按情况查看职工工资\n");
	printf("5.月结工资\n");
	printf("6.职工奖金\n");
	printf("7.退出\n");
}

void Function_Main_Regular_Personnel()
{
	printf("欢迎来到本程序，输入对应序列数字实现功能\n");
	printf("1.查看所有的职工\n");
	printf("2.按情况查看职工数据\n");
	printf("3.按情况查看职工工资\n");
	printf("4.输入管理员通行码获取管理员资格\n");
	printf("5.退出\n");
}

void Choice_Function(LinkList* head)
{
	char flag_1[254]{};
	int flag = -1;
	Function_Main();
	while (true)
	{
		system("cls");
		Function_Main();
		gets_s(flag_1);
		flag = (*flag_1) - 48;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			FileShow(FileRead());
			_getch();
			break;
		}
		case 2:
		{
			system("cls");
			Choice_Function_Member(head);
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			Choice_Function_FileRead();
			break;
		}
		case 4:
		{
			system("cls");
			Choice_Salary_Function();
			break;
		}
		case 5:
		{
			system("cls");
			Summarize();
			_getch();
			break;
		}
		case 6:
		{
			system("cls");
			Member_Bonus();
			_getch();
			break;
		}
		case 7:
		{
			return;
			break;
		}
		default:
		{
			printf("输入有误，按任意键后重新输入");
			_getch();
			break;
		}
		}
	}
}

void Choice_Function_Regular_Personnel(LinkList* head,char* name)
{
	char flag_1[254]{};
	int flag = -1;
	Function_Main_Regular_Personnel();
	while (true)
	{
		system("cls");
		Function_Main_Regular_Personnel();
		gets_s(flag_1);
		flag = (*flag_1) - 48;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			FileShow(FileRead());
			_getch();
			break;
		}
		case 2:
		{
			system("cls");
			Choice_Function_FileRead();
			break;
		}
		case 3:
		{
			system("cls");
			Choice_Salary_Function();
			break;
		}
		case 4:
		{
			system("cls");
			ObtainPermission(name);
			break;
		}
		case 5:
		{
			return;
		}
		default:
		{
			printf("输入有误，按任意键后重新输入");
			_getch();
			break;
		}
		}
	}
}

void Choice_Function_FileRead_Pre()
{
	printf("欢迎来到本功能，输入对应序列数字实现功能\n");
	printf("1.按照部门显示职工数据\n");
	printf("2.按照性别显示职工数据\n");
	printf("3.按照年龄区间显示职工数据\n");
	printf("4.按照工资区间显示职工数据\n");
	printf("5.退出\n");
}

void Choice_Function_FileRead()
{
	Choice_Function_FileRead_Pre();
	char flag_1[254]{};
	int flag = -1;
	while (true)
	{
		system("cls");
		Choice_Function_FileRead_Pre();
		gets_s(flag_1);
		flag = (*flag_1) - 48;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			FileRead_Department();
			_getch();
			break;
		}
		case 2:
		{
			system("cls");
			FileRead_Gender();
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			FileRead_AgeRange();
			_getch();
			break;
		}
		case 4:
		{
			system("cls");
			FileRead_SalaryRange();
			break;
		}
		case 5:
		{
			return;
			break;
		}
		default:
		{
			printf("输入有误，重新输入");
			_getch();
			break;
		}
		}
	}
}

void FileRead_Department()
{
	LinkList* head = Link_Init();
	Member* Data = NULL;
	head = FileRead();
	char num[20]{};
	int flag = -1;
	printf("输入部门名称： ");
	gets_s(num);
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		if (head != NULL && (0 == strcmp(Data->department, num)))
		{
			flag = 1;
			printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
		}
		head = head->after;
	}
	if (head == NULL && -1 == flag)
	{
		system("cls");
		printf("当前 %s 部门没有职工数据", num);
		return;
	}
}

void FileRead_Gender()
{
	LinkList* head = Link_Init();
	Member* Data = NULL;
	head = FileRead();
	char num[20]{};
	int flag = -1;
	printf("输入性别： ");
	scanf("%s", num);
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (head != NULL)
	{
	Loop:
		Data = (Member*)(head->data_member);
		flag = *(Data->number + 4);
		if (0 == strcmp(num, "男"))
		{
			if (0 == flag % 2)
			{
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
				flag = -1;
			}
		}
		else if (0 == strcmp(num, "女"))
		{
			if (0 != flag % 2)
			{
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
				flag = -1;
			}
		}
		else
		{
			printf("输入有误，请重新输入: ");
			scanf("%s", num);
			system("cls");
			printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
			goto Loop;
		}
		head = head->after;
	}
}

void FileRead_AgeRange()
{
	LinkList* head = Link_Init();
	Member* Data = NULL;
	head = FileRead();
	int Range_Left = -1;
	int Range_Right = -1;
	int flag = -1;
	printf("输入年龄区间： ");
	scanf_s("%d  %d", &Range_Left, &Range_Right);
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		if (head != NULL && (Data->age >= Range_Left) && (Data->age <= Range_Right))
		{
			flag = 1;
			printf("%s\t%d\t%s\t%s\t%d\t%d\n", 
				Data->name, Data->age, Data->number, 
				Data->department, Data->salary, Data->bonus);
		}
		head = head->after;
	}
	if (head == NULL && -1 == flag)
	{
		system("cls");
		printf("当前年龄 %d--%d 没有职工数据", Range_Left, Range_Right);
		return;
	}
}

void FileRead_SalaryRange()
{
	LinkList* head = Link_Init();
	Member* Data = NULL;
	head = FileRead();
	int Range_Left = -1;
	int Range_Right = -1;
	int flag = -1;
	printf("输入工资区间： ");
	scanf_s("%d  %d", &Range_Left, &Range_Right);
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		if (head != NULL && (Data->salary >= Range_Left) && (Data->salary <= Range_Right))
		{
			flag = 1;
			printf("%s\t%d\t%s\t%s\t%d\t%d\n",
				Data->name, Data->age, Data->number,
				Data->department, Data->salary, Data->bonus);
		}
		head = head->after;
	}
	if (head == NULL && -1 == flag)
	{
		system("cls");
		printf("当前工资 %d--%d 没有职工数据", Range_Left, Range_Right);
		return;
	}
}

void Summarize()
{
	LinkList* head, * p;
	Member* Data = NULL;
	p = head = FileRead();
	long int SumSalary = 0;
	while (p != NULL)
	{
		Data = (Member*)(p->data_member);
		SumSalary = SumSalary + Data->salary + Data->bonus;
		Data->bonus = 0;
		p = p->after;
	}
	printf("本月总共工资要发放： %ld 元\n", SumSalary);
	printf("本月工资已结，奖金清零");
	FileReWirte(head);
}

void Choice_Salary_Function_Pre()
{
	printf("欢迎来到本功能，输入对应序列数字实现功能\n");
	printf("1.显示职工平均工资\n");
	printf("2.降序显示职工数据\n");
	printf("3.升序显示职工数据\n");
	printf("4.显示职工数据\n");
	printf("5.退出\n");
}

void Choice_Salary_Function()
{
	char flag_1[254]{};
	int flag = -1;
	Choice_Salary_Function_Pre();
	while (true)
	{
		system("cls");
		Choice_Salary_Function_Pre();
		gets_s(flag_1);
		flag = (*flag_1) - 48;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			Algorithm_AverageSalary();
			_getch();
			break;
		}
		case 2:
		{
			system("cls");
			Ascending_Sort();
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			Descending_Sort();
			_getch();
			break;
		}
		case 4:
		{
			system("cls");
			
			_getch();
			break;
		}
		case 5:
		{
			return;
		}
		default :
		{
			printf("输入有误，请重新输入");
			_getch();
			break;
		}
		}
	}
}

void Hidden_Input(char* pwd)
{
	char input_char;
	int index = 0;
	fflush(stdin);
	while ((input_char = _getch()) != '\r')
	{
		if (input_char == '\b')
		{
			if (index < 0)
				continue;
			if (index > 0)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				index--;
			}
		}
		else
		{
			printf("*");
			pwd[index++] = input_char;
		}
	}
	pwd[index] = '\0';
	printf("\n");
}
