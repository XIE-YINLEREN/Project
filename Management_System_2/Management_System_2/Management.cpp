#include"Management.h"

Personnel* Personnel_Init()
{
	Personnel* Person = (Personnel*)malloc(sizeof(Personnel));
	Person->flag = -1;
	Person->number = 5;
	Person->name;
	Person->password ;
	return Person;
}

void Choice_Authority_Pre()
{
	printf("��ӭ����������\n");
	printf("1.�����˺ŵ�¼\n");
	printf("2.ע���˺�\n");
	printf("3.�˳�\n");
}

void Choice_Authority(LinkList* head)
{
	Choice_Authority_Pre();
	char flag_1[254]{};
	int flag = -1;
	while (true)
	{
		system("cls");
		Choice_Authority_Pre();
		gets_s(flag_1);
		flag = (*flag_1) - 48;
		switch (flag)
		{
		case 1:
		{
			system("cls");
			Management_Older(head);
			_getch();
			break;
		}
		case 2:
		{
			system("cls");
			Register_Management();
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			exit(-1);
			_getch();
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

void Management_Older(LinkList* head)
{
	Personnel* Data = Personnel_Init();
	Personnel* Data_Old = Personnel_Init();
	LinkList* P = Management_FileRead();
	printf("�û�����\n");
	gets_s(Data->name);
	printf("���룺\n");
	Hidden_Input(Data->password);
	while (P != NULL)
	{	
		Data_Old = (Personnel*)(P->data_personnel);
		if (0 == strcmp(Data_Old->name,Data->name))
		{
			break;
		}
		P = P->after;
	}
	if (P != NULL)
	{
		printf("��¼�ɹ�\n");
		if (Data_Old->flag == 1)
		{
			printf("��ӭ��������Ա�û� %s \n", Data->name);
			getch();
			Choice_Function(head);
		}
		else
		{
			printf("��ӭ���������û� %s \n", Data->name);
			getch();
			Choice_Function_Regular_Personnel(head,Data->name);
		}
	}
	else
	{
		printf("��¼ʧ�ܣ����ݿ���û�иó�Ա����");
	}
}

void Register_Management()
{
	char flag[20]{};
	Authority_FileRead(flag);
	LinkList* head = Link_Init();
	LinkList* P = Management_FileRead();
	Personnel* Man ,* Man_Old;
	Man = Man_Old = Personnel_Init();
	head->data_member = Personnel_Init();
	Man = (Personnel*)(head->data_member);
	char word[20]{};
	char Reword[20]{};
	Loop:
	system("cls");
	printf("ע���˻���\n");
	gets_s(Man->name);
	while (P != NULL)
	{
		Man_Old = (Personnel*)(P->data_personnel);
		if (0 ==  strcmp(Man_Old->name,Man->name))
		{
			printf("���û���ͬ������������\n");
			_getch();
			goto Loop; 
		}
		P = P->after;
	}
	printf("ע�����룺\n");
	Hidden_Input(Man->password);
	printf("ȷ�����룺\n");
	Hidden_Input(Reword);
	if (0 != strcmp(Reword,Man->password))
	{
		printf("�������벻һ��,����������\n");
		goto Loop;
	}

	printf("����Աͨ���룺\n");
	Hidden_Input(word);
	if (0 == strcmp(flag,word))
	{
		printf("�ѳ�Ϊ����Ա���\n");
		Man->flag = 1;
	}
	else
	{
		printf("����Աͨ�������\n");
		printf("��ע��Ϊ�ǹ���Ա\n");
		Man->flag = -1;
	}
	printf("�����ɹ�");
	Management_FileWirte(head);
}

void ObtainPermission(char* name)
{
	Personnel* Data = Personnel_Init();
	LinkList* head = Management_FileRead();
	LinkList* P = head;
	char flag[20]{}, word[20]{};
	Authority_FileRead(flag);
	Data = (Personnel*)(P->data_personnel);
	while (0 != strcmp(Data->name, name))
	{
		P = P->after;
		Data = (Personnel*)(P->data_personnel);
	}
	if (Data->number <= 0)
	{
		printf("���������Ѿ����������������ٻ�ȡ����Ա���\n");
		getchar();
		return;
	}
	printf("�������Աͨ����\n");
	printf("���� %d �λ�����Գ���\n", Data->number);
	Hidden_Input(word);
	
	if (0 == strcmp(word, flag))
	{
		printf("������ȷ���ѳ�Ϊ����Ա\n");
		printf("���������Ա����\n");
		Data->flag = 1;
		Data->number = 0;
		Management_FileReWirte(head);
		getchar();
		Choice_Function(head);
		return;
	}
	else
	{
		printf("�������\n");
		Data->number -= 1;
		Management_FileReWirte(head);
		printf("%s ����ǰ��ʣ�� %d �������\n", name, Data->number);
		getchar();
	}
}
