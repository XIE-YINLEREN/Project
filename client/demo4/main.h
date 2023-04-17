#pragma once
#pragma comment(lib,"C:\Users\HP\OneDrive\桌面\sqlite-amalgamation-3410000\sqlite3.lib")
#include <cstdio>
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


typedef struct
{
    char file_name[20];  //文件名   
    int  file_len;       //文件大小
} data_t;

constexpr auto PORT_MESSAGE = 10002;//读取信息端口
constexpr auto PORT_FILE = 11002; //文件读取端口号
constexpr auto SIZE = 1024;
constexpr auto IP = "192.168.248.128";
constexpr auto NUM = 100;


void Recive_Dir_Client(int cid);
void Recive_File_Servicer(int cid, char name[20]);
void DateBase_Operate(int cid);
void DateBase_Interface();
void File_Interface();
void Regiset_DateBase(sqlite3* dp,int cid);
int  Login_DateBase(sqlite3* dp,int cid);
void File_Sent(int cid);
void File_Service_Recive(int cid);
void Sent_File_Client(int cid);
void Sent_Dir_Client();
void File_Client_Recive(int cid);
void Recive_File_Client(int cid, char name[20]);
void Client_File_Delete(int cid);
void Print(int len);