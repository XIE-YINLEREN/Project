#include "File.h"

void FileReWirte(LinkList* head)
{
	FILE* fp = nullptr;
	Member* Data = NULL;
	fp = fopen("data.txt", "w");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		fprintf(fp, " %s %d %s %s %d %d ",
			Data->name, Data->age, Data->number, 
			Data->department, Data->salary, Data->bonus);
		fputc('\n', fp);
		head = head->after;
	}
	fclose(fp);
}

void FileWirte(LinkList* head)
{
	FILE* fp = nullptr;
	Member* Data = NULL;
	Data = (Member*)(head->data_member);
	fp = fopen("data.txt", "a+");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	fprintf(fp, "%s %d %s %s %d %d ",
		Data->name, Data->age, Data->number,
		Data->department, Data->salary, Data->bonus);
	fputc('\n', fp);
	fclose(fp);
}

LinkList* FileRead()
{
	FILE* fp = nullptr;
	LinkList* head, * p, * pp;
	Member *Data = NULL;
	pp = p = head = Link_Init();
	int ret = 0;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	else
	{
		while (!feof(fp))
		{
			p->data_member = (Member*)malloc(sizeof(Member));
			Data = (Member*)(p->data_member);
			ret = fscanf(fp, "%s %d %s %s %d %d ",
				Data->name, &Data->age, Data->number, 
				Data->department,&Data->salary, &Data->bonus);
			if (ret < 6)
			{
				break;
			}
			p->after = (LinkList*)malloc(sizeof(LinkList));
			pp = p;
			p = p->after;
		}
		pp->after = NULL;
	}
	fclose(fp);
	return head;
}

void FileShow(LinkList* head)
{
	Member* Data;
	printf("姓名\t年龄\t工号\t部门\t薪水\t奖金\n");
	while (head != NULL)
	{
		Data = (Member*)(head->data_member);
		printf("%s\t%d\t%s\t%s\t%d\t%d\n",\
			Data->name, Data->age, Data->number,
			Data->department, Data->salary, Data->bonus);
		head = head->after;
	}
}

void Authority_FileRead(char *flag)
{
	FILE* fp = nullptr;
	fp = fopen("Management.txt", "r+");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	else
	{
		fgets(flag, sizeof(flag), fp);
	}
}

LinkList* Management_FileRead()
{
	FILE* fp = nullptr;
	LinkList* head, * p, * pp;
	Personnel* Data = NULL;
	pp = p = head = Link_Init();
	int ret = 0;
	fp = fopen("power.txt", "r");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	else
	{
		while (!feof(fp))
		{
			p->data_personnel = (Personnel*)malloc(sizeof(Personnel));
			Data = (Personnel*)(p->data_personnel);
			fscanf(fp, "%s %s %d %d ",
				Data->name, Data->password, &Data->flag,&Data->number);
			p->after = (LinkList*)malloc(sizeof(LinkList));
			pp = p;
			p = p->after;
		}
		pp->after = NULL;
	}
	fclose(fp);
	return head;
}

void Management_FileWirte(LinkList* head)
{
	FILE* fp = nullptr;
	Personnel* Data = NULL;
	Data = (Personnel*)(head->data_personnel);
	fp = fopen("power.txt", "a+");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	fprintf(fp, "%s %s %d %d ", 
		Data->name, Data->password, Data->flag,Data->number);
	fputc('\n', fp);
	fclose(fp);
}

void Management_FileReWirte(LinkList* head)
{
	FILE* fp = nullptr;
	Personnel* Data = Personnel_Init();
	fp = fopen("power.txt", "w");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	while (head != NULL)
	{
		Data = (Personnel*)(head->data_personnel);
		fprintf(fp, " %s %s %d %d ", 
			Data->name, Data->password, Data->flag,Data->number);
		fputc('\n', fp);
		head = head->after;
	}
	fclose(fp);
	
}
