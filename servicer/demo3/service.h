#pragma once
#pragma comment(lib, "pthreadVC2.lib")
#ifndef _SERVICER_H_
#define _SERVICER_H_

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <poll.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sqlite3.h>

constexpr auto PORT_MESSAGE = 10002;//��ȡ��Ϣ�˿�
constexpr auto PORT_FILE = 11002; //�ļ���ȡ�˿ں�
constexpr auto SIZE = 1024;
constexpr auto IP = "192.168.248.128";
constexpr auto NUM = 100;

typedef struct
{
    char file_name[20]; //�ļ���
    int file_len;       //�ļ���С
} data_t;

void Message(int cid);
void* Pthread_File(void* arg);
extern void Dir_Service(int cid);
void Dir_Client(int cid);
extern void File_Service(int tcp_socket);
void *DateBase_Operate(void *arg);
int Login_DateBase(sqlite3* dp, int cid);
void Regiset_DateBase(sqlite3* dp, int cid);
void Recive_File(int cid);
void File_Cilent(int cid);
void Delete(int cid);
void Syslog(char name[SIZE], char buf[SIZE]);
void Print(int len);
#endif

