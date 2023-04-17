#include "service.h"

int sock_cids[SIZE]{};
int sock_index = 0;

int main()
{

	int Tcp_Message = socket(AF_INET, SOCK_STREAM, 0);
	int Tcp_File = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in IPV4_Message {};
	IPV4_Message.sin_family = AF_INET;
	IPV4_Message.sin_addr.s_addr = 0;		//ip地址
	IPV4_Message.sin_port = htons(PORT_MESSAGE);	//端口号

	struct sockaddr_in IPV4_File {};
	IPV4_File.sin_family = AF_INET;
	IPV4_File.sin_addr.s_addr = 0;		//ip地址
	IPV4_File.sin_port = htons(PORT_FILE);	//端口号


	if (bind(Tcp_Message, (struct sockaddr*)&IPV4_Message, sizeof(IPV4_Message)) < 0)
	{
		perror("bind");
		return -1;
	}

	if (bind(Tcp_File, (struct sockaddr*)&IPV4_File, sizeof(IPV4_File)) < 0)
	{
		perror("bind");
		return -1;
	}

	listen(Tcp_Message, 10);
	listen(Tcp_File, 10);

	printf("Servicer Opening\n");

	while (true)
	{
		if (fork() == 0) //信息处理
		{
			while (true)
			{
				int cid = accept(Tcp_Message, NULL, NULL);
				if (cid > 0)
				{
					char buf[SIZE]{};
					sock_cids[sock_index] = cid;
					sock_index++;
					pthread_t pthread_DateBase;

					memset(buf, 0, SIZE);
					read(cid, buf, SIZE);//获取用户信号 决定功能

					if (strcmp(buf, "DateBase") == 0)//用户登录注册功能 成功会跳转到信息收发
					{
						pthread_create(&pthread_DateBase, NULL, DateBase_Operate, &cid);
					}
				}
			}
		}
		else //文件处理
		{
			while (true)
			{
				int cid = accept(Tcp_File, NULL, NULL);
				if (cid > 0)
				{
					pthread_t pthread_file;
					pthread_create(&pthread_file, NULL, Pthread_File, &cid);
				}
			}
		}
		return -1;
	}

	}

	

/***************************************
函数名	：Message
作者	：XIE
维护时间：2023/3/6
功能	：接收客户端<信息>并且转发<信息>给客户端
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Message(int cid) 
{
	char buf[SIZE]{};
	ssize_t len = 0;
	char flag[SIZE]{};

	printf("Message Function\n");

	while (1)
	{

		len = read(cid, buf, SIZE);
		if (len <= 0)//容错处理
		{
			break;
		}
		printf("%d:--%s\n", cid, buf);

		sprintf(flag, "%d:--%s\n", cid, buf);
		for (int i = 0; i < sock_index; i++)//群发信息
		{
			if (sock_cids[i] != cid)
			{
				write(sock_cids[i], flag, SIZE);
			}
		}
		memset(flag, 0, SIZE);
		memset(buf, 0, SIZE);
	}
	pthread_exit(NULL);
}


/***************************************
函数名	：Pthread_File
作者	：XIE
维护时间：2023/3/6
功能	：收发文件函数主框架
参数	：（void* arg）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void* Pthread_File(void* arg)
{
	int cid = *(int*)arg;

	while (true)
	{
		printf("File Function\n");

		char buf[SIZE]{};
		memset(buf, 0, SIZE);
		ssize_t flag = read(cid, buf, SIZE);

		if (flag <= 0)//容错处理
		{
			break;
		}
		if (strcmp(buf, "Recive Servicer File") == 0) //发送服务器文件给客户端
		{
			printf("SENT Servicer FILE\n");

			Dir_Service(cid); //服务器文件目录发送
			File_Service(cid);//服务器文件发送

			pthread_exit(NULL);
		}
		if (strcmp(buf, "Recive Client File") == 0)//发送客户端文件给客户端
		{
			printf("SENT Client FILE\n");
			Dir_Client(cid);//客户端文件目录发送	
			File_Cilent(cid);//客户端文件发送

		}
		if (strcmp(buf, "File Sent") == 0)//接收客户端发来的文件
		{
			printf("Recive  Client FILE\n");
			Recive_File(cid);
		}
		if (strcmp(buf, "Delete") == 0)//删除客户端文件
		{
			printf("Delete  Client FILE\n");

			Dir_Client(cid);//客户端文件目录发送
			Delete(cid); //删除客户端文件

		}

	}


}

