#pragma once
#ifndef _MEMBER_H_
#define _MEMBER_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct member
{
	char name[20];
	char number[20];
	char department[20];
	int age;
	int salary;
	int bonus;
}Member;

typedef struct  linklist
{
	void* data_member;
	void* data_personnel;
	struct linklist* before;
	struct linklist* after;
}LinkList;

void Member_Create(LinkList** head);
LinkList* Link_Init();
void Member_Del(LinkList* head);
void Member_Modify(LinkList* head);
void Member_Search();
void Member_Bonus();
void Algorithm_AverageSalary();
void Ascending_Sort();
void Descending_Sort();

#endif // !_MEMBER_H_
