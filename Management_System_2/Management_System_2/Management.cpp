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
	printf("欢迎来到本功能\n");
	printf("1.已有账号登录\n");
	printf("2.注册账号\n");
	printf("3.退出\n");
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
			printf("输入有误，重新输入");
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
	printf("用户名：\n");
	gets_s(Data->name);
	printf("密码：\n");
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
		printf("登录成功\n");
		if (Data_Old->flag == 1)
		{
			printf("欢迎您，管理员用户 %s \n", Data->name);
			getch();
			Choice_Function(head);
		}
		else
		{
			printf("欢迎您，常规用户 %s \n", Data->name);
			getch();
			Choice_Function_Regular_Personnel(head,Data->name);
		}
	}
	else
	{
		printf("登录失败，数据库中没有该成员数据");
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
	printf("注册账户：\n");
	gets_s(Man->name);
	while (P != NULL)
	{
		Man_Old = (Personnel*)(P->data_personnel);
		if (0 ==  strcmp(Man_Old->name,Man->name))
		{
			printf("该用户名同名，重新输入\n");
			_getch();
			goto Loop; 
		}
		P = P->after;
	}
	printf("注册密码：\n");
	Hidden_Input(Man->password);
	printf("确认密码：\n");
	Hidden_Input(Reword);
	if (0 != strcmp(Reword,Man->password))
	{
		printf("两次输入不一致,请重新输入\n");
		goto Loop;
	}

	printf("管理员通行码：\n");
	Hidden_Input(word);
	if (0 == strcmp(flag,word))
	{
		printf("已成为管理员身份\n");
		Man->flag = 1;
	}
	else
	{
		printf("管理员通行码错误\n");
		printf("已注册为非管理员\n");
		Man->flag = -1;
	}
	printf("创建成功");
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
		printf("您的输入已经超过次数，不能再获取管理员身份\n");
		getchar();
		return;
	}
	printf("输入管理员通行码\n");
	printf("你有 %d 次机会可以尝试\n", Data->number);
	Hidden_Input(word);
	
	if (0 == strcmp(word, flag))
	{
		printf("口令正确，已成为管理员\n");
		printf("将进入管理员界面\n");
		Data->flag = 1;
		Data->number = 0;
		Management_FileReWirte(head);
		getchar();
		Choice_Function(head);
		return;
	}
	else
	{
		printf("口令错误\n");
		Data->number -= 1;
		Management_FileReWirte(head);
		printf("%s 您当前还剩下 %d 输入机会\n", name, Data->number);
		getchar();
	}
}
