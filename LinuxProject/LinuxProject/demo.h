#pragma once
#ifndef _FILEDISPLAY_H_
#define _FILEDISPLAY_H_

typedef struct student
{
	int age;
	char name[20];
}Student;

#include <iostream>      
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>   
#include <sys/stat.h>
#include <sys/wait.h> 
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <pthread.h>
#include <stdlib.h>

void Process_Demo();
void Read_Dir(char* dir);
void IsFile(char* name);
void Filesearch();
void SleepTime();
void SrandTime();
void cp();
void ShowDir();
void demo();
void guard();
void family();
void logfile();
void Creat_Dir();
void pipe();
void pipecommunication();
void filestr();
void Signal_processing();

#endif // !_FILEDISPLAY_H_

