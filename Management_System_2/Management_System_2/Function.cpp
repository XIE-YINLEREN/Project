#include"Function.h"
#include"File.h"


void Choice_Function_Member_Pre()
{
	printf("��ӭ���������ܣ������Ӧ��������ʵ�ֹ���\n");
	printf("1.�½�һ��ְ������\n");
	printf("2.ɾ��һ��ְ������\n");
	printf("3.�޸�һ��ְ������\n");
	printf("4.����һ��ְ������\n");
	printf("5.��ʾ����ְ������\n");
	printf("6.�˳�\n");
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
			printf("����������������");
			_getch();
			break;
		}
		}
	}
}

void Function_Main()
{
	printf("��ӭ���������������Ӧ��������ʵ�ֹ���\n");
	printf("1.�鿴���е�ְ��\n");
	printf("2.�Ե�ǰְ��������ɾ���\n");
	printf("3.������鿴ְ������\n");
	printf("4.������鿴ְ������\n");
	printf("5.�½Ṥ��\n");
	printf("6.ְ������\n");
	printf("7.�˳�\n");
}

void Function_Main_Regular_Personnel()
{
	printf("��ӭ���������������Ӧ��������ʵ�ֹ���\n");
	printf("1.�鿴���е�ְ��\n");
	printf("2.������鿴ְ������\n");
	printf("3.������鿴ְ������\n");
	printf("4.�������Աͨ�����ȡ����Ա�ʸ�\n");
	printf("5.�˳�\n");
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
			printf("�������󣬰����������������");
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
			printf("�������󣬰����������������");
			_getch();
			break;
		}
		}
	}
}

void Choice_Function_FileRead_Pre()
{
	printf("��ӭ���������ܣ������Ӧ��������ʵ�ֹ���\n");
	printf("1.���ղ�����ʾְ������\n");
	printf("2.�����Ա���ʾְ������\n");
	printf("3.��������������ʾְ������\n");
	printf("4.���չ���������ʾְ������\n");
	printf("5.�˳�\n");
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
			printf("����������������");
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
	printf("���벿�����ƣ� ");
	gets_s(num);
	printf("����\t����\t����\t����\tнˮ\t����\n");
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
		printf("��ǰ %s ����û��ְ������", num);
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
	printf("�����Ա� ");
	scanf("%s", num);
	printf("����\t����\t����\t����\tнˮ\t����\n");
	while (head != NULL)
	{
	Loop:
		Data = (Member*)(head->data_member);
		flag = *(Data->number + 4);
		if (0 == strcmp(num, "��"))
		{
			if (0 == flag % 2)
			{
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
				flag = -1;
			}
		}
		else if (0 == strcmp(num, "Ů"))
		{
			if (0 != flag % 2)
			{
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
				flag = -1;
			}
		}
		else
		{
			printf("������������������: ");
			scanf("%s", num);
			system("cls");
			printf("����\t����\t����\t����\tнˮ\t����\n");
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
	printf("�����������䣺 ");
	scanf_s("%d  %d", &Range_Left, &Range_Right);
	printf("����\t����\t����\t����\tнˮ\t����\n");
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
		printf("��ǰ���� %d--%d û��ְ������", Range_Left, Range_Right);
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
	printf("���빤�����䣺 ");
	scanf_s("%d  %d", &Range_Left, &Range_Right);
	printf("����\t����\t����\t����\tнˮ\t����\n");
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
		printf("��ǰ���� %d--%d û��ְ������", Range_Left, Range_Right);
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
	printf("�����ܹ�����Ҫ���ţ� %ld Ԫ\n", SumSalary);
	printf("���¹����ѽᣬ��������");
	FileReWirte(head);
}

void Choice_Salary_Function_Pre()
{
	printf("��ӭ���������ܣ������Ӧ��������ʵ�ֹ���\n");
	printf("1.��ʾְ��ƽ������\n");
	printf("2.������ʾְ������\n");
	printf("3.������ʾְ������\n");
	printf("4.��ʾְ������\n");
	printf("5.�˳�\n");
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
			printf("������������������");
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
