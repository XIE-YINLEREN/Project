#pragma once
#ifndef _MANAGEMENT_H_
#define _MANAGEMENT_H_
#define _CRT_SECURE_NO_WARNINGS
#include"File.h"
#include"Function.h"
#include"Member.h"
#include <conio.h>

typedef struct  personnel
{
	char name[256];
	char password[256];
	int flag;
	int number;
}Personnel;

Personnel* Personnel_Init();
void Choice_Authority(LinkList* head);
void Choice_Authority_Pre();
void Register_Management();
void Management_Older(LinkList* head);
void ObtainPermission(char* name);

#endif // !_MANAGEMENT_H_
