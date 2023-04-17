#pragma once
#ifndef _FUNCTION_H
#define _FUNCTION_H
#include"Member.h"
#include"File.h"
#include<string.h>
#include<conio.h>
#include <Windows.h>

void Choice_Function_Member_Pre();
void Choice_Function_Member(LinkList* head);
void Function_Main();
void Choice_Function(LinkList* head);
void Function_Main_Regular_Personnel();
void Choice_Function_Regular_Personnel(LinkList* head,char* name);
void Choice_Function_FileRead_Pre();
void Choice_Function_FileRead();
void FileRead_Department();
void FileRead_Gender();
void FileRead_AgeRange();
void FileRead_SalaryRange();
void Summarize();
void Choice_Salary_Function_Pre();
void Choice_Salary_Function();
void Hidden_Input(char* pwd);

#endif // !_FUNCTION_H
