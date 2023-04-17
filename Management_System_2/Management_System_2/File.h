#pragma once
#ifndef __FILE_H_
#define __FILE_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include"Member.h"
#include"Management.h"

void FileReWirte(LinkList* head);
void FileWirte(LinkList* head);
LinkList* FileRead();
void FileShow(LinkList* head);
void Authority_FileRead(char *flag);
LinkList* Management_FileRead();
void Management_FileWirte(LinkList* head);
void Management_FileReWirte(LinkList* head);

#endif // !__FILE_H_

