#include "main.h"

/***************************************
函数名	：Newpthread_File
作者	：XIE
维护时间：2023/3/6
功能	：文件收发功能选择主界面
参数	：（void* arg）  
参数类型：传入参数
参数作用：传入 Cid 句柄 
***************************************/
void* Newpthread_File(void* arg) //收文件
{
	int cid = *(int*)arg;
	while (1)
	{
		char flag_pr[SIZE]{};
		int flag = -1;

		File_Interface();//文件界面
		
		scanf("%s", flag_pr);
		flag = *flag_pr - 48;  //防止异常输入 

		if (flag == 1 && strlen(flag_pr) == 1)
		{
			write(cid, "File Sent", SIZE);//给服务器发送 <发送文件处理>  信号
			File_Sent(cid);
		}
		else if (flag == 2 && strlen(flag_pr) == 1)
		{
			write(cid, "Recive Servicer File", SIZE);//给服务器发送 <接收服务器文件处理>  信号
			File_Service_Recive(cid);
		}
		else if (flag == 3 && strlen(flag_pr) == 1)
		{
			write(cid, "Recive Client File", SIZE);//给服务器发送 <接收客户端文件处理>  信号
			File_Client_Recive(cid);
		}
		else if (flag == 4 && strlen(flag_pr) == 1)
		{
			write(cid, "Delete", SIZE);//给服务器发送 <删除客户端文件处理>  信号
			Client_File_Delete(cid);
		}
		else if (flag == 5 && strlen(flag_pr) == 1)
		{
			return arg;
		}

	}
	pthread_exit(NULL);
}

/***************************************
函数名	：Newpthread_Message_Sent
作者	：XIE
维护时间：2023/3/6
功能	：发送<信息>给服务器
参数	：（void* arg）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void* Newpthread_Message_Sent(void* arg) //发信息
{
	int cid =  *(int*)arg;
	char buf[SIZE]{};
	printf("---------------------------------------\n");
	printf("sent message to other:\n");
	printf("if want to quit,please sent <quit>\n");
	while (1)
	{
		gets(buf);
		if (strcmp(buf,"quit") == 0)
		{
			break;
		}
		write(cid, buf, strlen(buf));	
		memset(buf, 0, SIZE);
	}
	pthread_exit(NULL);
}

/***************************************
函数名	：Newpthread_Message_Recive
作者	：XIE
维护时间：2023/3/6
功能	：接收服务器发送的信息
		  实质为其他用户发送的信息
参数	：（void* arg）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void* Newpthread_Message_Recive(void* arg)//收信息
{
	int cid = *(int*)arg;
	char buf[SIZE]{};
	while (1)
	{
		memset(buf, 0, SIZE);
		int len = read(cid, buf, SIZE);
		if (len < 0)
		{
			printf("servicer is close\n");
			break;
		}
		printf("%s", buf);
	}
	pthread_exit(NULL);
}

int main()
{
	int Cid_Message = socket(AF_INET, SOCK_STREAM, 0);//收发信息的套接字
	struct sockaddr_in IPV4_Message {};
	IPV4_Message.sin_family = AF_INET;
	IPV4_Message.sin_addr.s_addr = 0;				//ip地址
	IPV4_Message.sin_port = htons(PORT_MESSAGE);	//端口号

	int Cid_File = socket(AF_INET, SOCK_STREAM, 0);//文件处理的套接字
	struct sockaddr_in IPV4_File {};
	IPV4_File.sin_family = AF_INET;
	IPV4_File.sin_addr.s_addr = 0;				//ip地址
	IPV4_File.sin_port = htons(PORT_FILE);		//端口号


	/*   与服务器进行连接   */
	if (connect(Cid_Message, (struct sockaddr*)&IPV4_Message, sizeof(IPV4_Message)) < 0)
	{
		perror("conncet");
		return -1;
	}

	if (connect(Cid_File, (struct sockaddr*)&IPV4_File, sizeof(IPV4_File)) < 0)
	{
		perror("conncet");
		return -1;
	}

	DateBase_Operate(Cid_Message);//数据库操作  登录注册

	printf("connceting servicer ! \n");
	char buf[SIZE]{};
	while (true)
	{
		memset(buf, 0, SIZE);
		scanf("%s", buf);
		if (strcmp(buf, "quit") == 0)
		{
			exit(-1);
		}
		if (fork() != 0)
		{
			if (strcmp(buf, "file") == 0)
			{				
				printf("File Mode\n");
				pthread_t pthread_send;
				pthread_create(&pthread_send, NULL, Newpthread_File, &Cid_File);//文件处理
			
			}
		}
		else
		{
			if (strcmp(buf, "message") == 0)//给服务器发送信息处理信号
			{
				printf("Message Mode\n");
				pthread_t pthread_read;
				pthread_t pthread_recive;
				pthread_create(&pthread_read, NULL, Newpthread_Message_Sent, &Cid_Message);//发信息
				pthread_create(&pthread_recive, NULL, Newpthread_Message_Recive, &Cid_Message);//收信息
			}
		}
		waitpid(-1, NULL, NULL);
	}
	close(Cid_Message);
	close(Cid_File);

	return -1;
}
