#include"Member.h"
#include"File.h"

LinkList* Link_Init()
{
	LinkList* head = (LinkList*)malloc(sizeof(LinkList));
	if (head == NULL)
	{
		printf("�ڴ����ʧ��");
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

	printf("������Ҫ�½�ְԱ������:  ");
	gets_s((*NewData).name);
	printf("������Ҫ�½�ְԱ������:  ");
	scanf_s("%d", &((*NewData).age));

	while (true)
	{
		if ((*NewData).age <= 65 && (*NewData).age >= 18)
		{
			break;
		}
		else
		{
			printf("������������������\n");
			scanf_s("%d", &((*NewData).age));
		}
	}
	printf("������Ҫ�½�ְԱ�Ĺ���\n");
	printf("����Ϊ��λ�������һλ����ΪŮ��ż��Ϊ��:\n"); 
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
			printf("������������������: ");
			scanf_s("%s", (*NewData).number);
			P = FileRead();
		}
		P = P->after;
	}
	printf("������Ҫ�½�ְԱ�Ĳ���:  ");
	scanf_s("%s", (*NewData).department);
	printf("������Ҫ�½�ְԱ��нˮ:  ");
	scanf_s("%d", &((*NewData).salary));
	(*NewData).bonus = 0;
	printf("�����ɹ�");
}

void Member_Del(LinkList *head)
{
	head = FileRead();
	FileShow(head);
	LinkList* p ,*q;
	p = q = head;
	Member* Data = NULL;
	char num[20]{};
	printf("������Ҫɾ����ְԱ�Ĺ��ţ� ");
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
				printf("ɾ���ɹ�");
				break;
			}
			else
			{
				q->after = p->after;
				free(p);
				printf("ɾ���ɹ�");
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
		printf("������Ҫ�޸ĵ�ְ���Ĺ���:  ");
		gets_s(num);

		while (p != NULL)
		{
			if (0 == strcmp(Data->number, num))
			{
				system("cls");
				printf("��ְ�����ҵ�\n");
				printf("����\t����\t����\t����\tнˮ\t����\n");
				printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name, Data->age, Data->number, Data->department, Data->salary, Data->bonus);
				break;
			}
			p = p->after;
		}
		if (Data == NULL)
		{
			printf("δ�ҵ���ְԱ");
			return;
		}
		printf("������Ҫ�޸ĵ�����\n");
		printf("1.���� 2.���� 3.���� 4.нˮ 5.����\n");
		while (true)
		{
			gets_s(flag_1);
			flag = (*flag_1) - 48;
			switch (flag)
			{
			case 1:
			{
				printf("�� %s �޸�Ϊ: ", Data->name);
				gets_s(buff);
				strcpy(Data->name, buff);
				FileReWirte(head);
				printf("�޸ĳɹ�");
				return;
			}
			case 2:
			{
				printf("�� %d �޸�Ϊ: ", Data->age);
				scanf_s("%d", &To_flag);
				Data->age = To_flag;
				FileReWirte(head);
				printf("�޸ĳɹ�");
				return;
			}
			case 3:
			{
				printf("�� %s �޸�Ϊ: ", Data->department);
				gets_s(buff);
				strcpy(Data->department, buff);
				FileReWirte(head);
				printf("�޸ĳɹ�");
				return;
			}
			case 4:
			{
				printf("�� %d �޸�Ϊ: ", Data->salary);
				scanf_s("%d", &To_flag);
				Data->salary = To_flag;
				FileReWirte(head);
				printf("�޸ĳɹ�");
				return;
			}
			case 5:
			{
				printf("�� %d �޸�Ϊ: ", Data->bonus);
				scanf_s("%d", &To_flag);
				Data->bonus = To_flag;
				FileReWirte(head);
				printf("�޸ĳɹ�");
				return;
			}
			default:
			{
				printf("�����������������");
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
	printf("������Ҫ���ҵ�ְԱ�Ĺ��ţ� ");
	gets_s(num);
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		if (0 == strcmp(Data->number, num))
		{
			printf("��ְ�����ҵ�\n");
			printf("%s\t%d\t%s\t%s\t%d\t%d\n", Data->name,Data->age, Data->number, Data->department, Data->salary, Data->bonus);
			break;
		}
		head = head->after;
	}
	if (head == NULL)
	{
		printf("��ְ��δ�ҵ�\n");
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
	printf("����Ҫ�ӽ����ְԱ�Ĺ��ţ� ");
	gets_s(num);
	printf("���� ");
	scanf("%d", &money);
	while (p != NULL)
	{
		Data = (Member*)(p->data_member);
		if (0 == strcmp(Data->number, num))
		{
			Data->bonus += money;
			printf("�����¼�ɹ�");
			break;
		}
		p = p->after;
	}
	if (p == NULL)
	{
		printf("���ţ�%s û������", num);
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
	printf("ְԱ��ƽ������Ϊ%d", AverageSalary / flag);
}

void Ascending_Sort()
{
	LinkList* head, *p,*q;
	head = p = q = FileRead();
	Member* Data_Q = NULL;
	Member* Data_P = NULL;
	int flag = -1;
	printf("����\t����\t����\t����\tнˮ\t����\n");
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
	printf("����\t����\t����\t����\tнˮ\t����\n");
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
