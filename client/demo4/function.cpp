#include "main.h"
char name[SIZE]{};

/***************************************
函数名	：Recive_Dir_Client
作者	：XIE
维护时间：2023/3/6
功能	：接收服务器发送用户的<客户端文件目录>
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Recive_Dir_Client(int cid)
{
	char buf[SIZE]{};
	ssize_t flag = 0;
	while (1)
	{
		flag = read(cid, buf, SIZE);
		if (flag <= 0) //容错处理
		{
			return;
		}

		if (strcmp(buf, "NULL") == 0)
		{
			return;
		}
		printf("   %s\n", buf);
		memset(buf, 0, SIZE);
	}
	printf("Reserve Dir  Over\n");
}

/***************************************
函数名	：Recive_File_Servicer
作者	：XIE
维护时间：2023/3/13
功能	：接收服务器发送给用户的<服务器文件>
参数	：（int cid, char filename[20]）
参数类型：传入参数
参数作用：传入 Cid 句柄 和 文件名
***************************************/
void Recive_File_Servicer(int cid, char filename[20])
{
	data_t cmd;
	read(cid, &cmd, sizeof(cmd)); //接收文件名和大小
	chdir("/home/student/projects/client/bin/x64/Debug");

	if (chdir(name) == -1)
	{
		mkdir(name,0777);
	}

	chdir(name);
	
	remove(filename); //先删除文件 避免文件重复
	int fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("open:");
		return;
	}
	char* buf = (char*)malloc(1024);
	int len = 0;

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len / SIZE);

	while (cmd.file_len > 0) //循环接收客户端发过来的文件
	{
		len = read(cid, buf, 1024);
		if (len <= 0)
		{
			perror("read:");
			break;
		}
		cmd.file_len -= len;
		write(fd, buf, len);
	}
	close(fd);
	chdir("..");
	printf("Receive File Over\n");
}

/***************************************
函数名	：Recive_File_Client
作者	：XIE
维护时间：2023/3/6
功能	：接收服务器发送给客户端的 <客户端文件> 
参数	：（int cid, char filename[20]）
参数类型：传入参数
参数作用：传入 Cid 句柄 和 文件名
***************************************/
void Recive_File_Client(int cid, char filename[20])
{
	data_t cmd;
	read(cid, &cmd, sizeof(cmd)); //接收文件名和大小
	char dir[SIZE]{};


	if (chdir(name) == -1)//创建用户文件夹
	{
		mkdir(name, 0777);
	}

	chdir(name);

	remove(filename);//删除文件

	int fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("open:");
		return;
	}
	char* buf = (char*)malloc(1024);
	int len = 0;

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len / SIZE);

	while (cmd.file_len > 0)
	{
		len = read(cid, buf, 1024);
		if (len <= 0)
		{
			perror("read:");
			break;
		}
		cmd.file_len -= len;
		write(fd, buf, len);
	}
	close(fd);
	chdir("..");
	printf("Receive File Over\n");
}


/*文件收发主界面*/
void File_Interface()
{
	printf("*************************************************************\n");
	printf("*****     Enter the number selection function           *****\n");
	printf("*****                                                   *****\n");
	printf("*****     1. Sent File.                                 *****\n");
	printf("*****     2. Receive  Servicer File.                    *****\n");
	printf("*****     3. Receive  Client File.                      *****\n");
	printf("*****     4. Delete File.                               *****\n");
	printf("*****     5. quit.                                      *****\n");
	printf("*************************************************************\n");
}

/*客户端登录主界面*/
void DateBase_Interface()
{
	printf("*************************************************************\n");
	printf("*****     Enter the number selection function           *****\n");
	printf("*****                                                   *****\n");
	printf("*****     1. Login in.                                  *****\n");
	printf("*****     2. Register                                   *****\n");
	printf("*****                                                   *****\n");
	printf("*****                                                   *****\n");
	printf("*************************************************************\n");
}


/***************************************
函数名	：DateBase_Operate
作者	：XIE
维护时间：2023/3/6
功能	：客户端登录函数框架
参数	：（int cid）
参数类型：传入参数
参数作用：Cid 句柄
***************************************/
void DateBase_Operate(int cid)
{
	sqlite3* dp = nullptr;//数据库句柄
	sqlite3_open("/home/student/projects/servicer/person.db", &dp);//打开数据库

	char flag_long[SIZE]{};
	int temp = 0;

	write(cid, "DateBase", SIZE);

Loop:
	DateBase_Interface();//登录注册界面
	scanf("%s", flag_long);
	char* flag = flag_long;
	if ((*flag - 48) == 1 && (strlen(flag_long) == 1))
	{
		temp = Login_DateBase(dp, cid);//登录

		if (temp == -1)
		{
			exit(1);
		}
	}
	else if ((*flag - 48) == 2 && (strlen(flag_long) == 1))
	{
		Regiset_DateBase(dp, cid);//注册
	}
	else
	{
		printf("Error Enter! \n");
		printf("Please Reenter\n");
		goto Loop;
	}
}

/***************************************
函数名	：Login_DateBase
作者	：XIE
维护时间：2023/3/6
功能	：发送用户登录信息给服务器
参数	：（sqlite3* dp, int cid）
参数类型：传入参数
参数作用：传入 数据库句柄 和 Cid 句柄
***************************************/
int Login_DateBase(sqlite3* dp, int cid)//发送用户登录信息给服务器
{

	char password[SIZE]{};
	char buf[SIZE]{};

	write(cid, "Login", SIZE);

	printf("Enter you name\n");
	scanf("%s", name);

	printf("Enter you password\n");
	scanf("%s", password);

	write(cid, name, SIZE);
	write(cid, password, SIZE);
	read(cid, buf, SIZE); //读取服务器发回的登录状态信息

	if (strcmp(buf, "Login Succsee") == 0)
	{
		printf("Login Succsee\n");
		return 1;
	}
	if (strcmp(buf, "Login Fail") == 0)
	{
		printf("Login Fail\n");
		return -1;
	}
}


/***************************************
函数名	：Regiset_DateBase
作者	：XIE
维护时间：2023/3/6
功能	：发送用户注册信息给服务器
参数	：（sqlite3* dp, int cid）
参数类型：传入参数
参数作用：传入 数据库句柄 和 Cid 句柄
***************************************/
void Regiset_DateBase(sqlite3* dp, int cid)
{
	char password[SIZE]{};
	char password_Re[SIZE]{};
	char buf[SIZE]{};
	char* err = nullptr;

	write(cid, "Regiset", SIZE);

Loop:
	printf("Enter you name\n");
	scanf("%s", name);
	printf("Enter you password\n");
	scanf("%s", password);
	printf("ReEnter you password\n");
	scanf("%s", password_Re);

	if (strcmp(password, password_Re) != 0)
	{

		printf("The password is different twice!\n");
		printf("Please ReEnter Password\n");
		goto Loop;
	}

	write(cid, name, SIZE);//把要注册的名字和密码给服务器
	write(cid, password, SIZE);

	read(cid, buf, SIZE);//读取是否注册成功

	if (strcmp(buf, "Registr Succsee") == 0)
	{
		printf("Registr Succsee\n");
	}
	else
	{
		printf("Registr Fail\n");
	}
}

/***************************************
函数名	：Sent_Dir_Client
作者	：XIE
维护时间：2023/3/6
功能	：显示客户端可发送给服务器的文件
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Sent_Dir_Client()
{
	DIR* dir = opendir(name);//打开一个目录

	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	struct dirent* dnt;

	while ((dnt = readdir(dir)) != NULL)// 只要返回结果不为NULL，就一直遍历
	{
		//if (strcmp(dnt->d_name, ".") != 0 && strcmp(dnt->d_name, "..") != 0)
		{
			printf("   %s\n", dnt->d_name);
			//memset(dnt->d_name, 0, SIZE);
		}
	}
	closedir(dir);
	printf("Dir Over\n");
	printf("---------------------------------------\n");
}

/***************************************
函数名	：Sent_File_Client
作者	：XIE
维护时间：2023/3/6
功能	：用户发送给服务器 <客户端文件>
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Sent_File_Client(int cid)
{

	data_t cmd{};
	char Filename[SIZE]{}; //文件名

	write(cid, name, SIZE);//发送自己的名称过去  使用固定的文件夹

	printf("Sent  File  Name is:\n");
	scanf("%s", Filename);

	struct stat stat_buf;//存取文件名 文件大小

	chdir(name);//找到文件目录

	if (stat(Filename, &stat_buf) != 0)        //获取文件信息
	{
		perror("stat");
		return;
	}

	cmd.file_len = stat_buf.st_size;
	char* str = strrchr(Filename, '/');

	if (str != NULL) //找到了 
	{
		str += 1;   //往后移动一位
	}
	else
	{
		str = Filename;
	}
	strcpy(cmd.file_name, str);  //获取文件名

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len / SIZE);//进度条

	int fd = open(cmd.file_name, O_RDONLY);

	if (fd < 0)
	{
		perror("open");
		return;
	}

	write(cid, &cmd, sizeof(cmd));     //发送包头:文件名　+　文件大小

	/***** 循环读取文件并发送 ****/
	char buf[SIZE]{};
	int len = 0;
	while (cmd.file_len > 0)
	{
		len = read(fd, buf, 1024);        //读文件
		write(cid, buf, len);      //写入
		cmd.file_len -= len;

	}

	printf("---------------------------------------\n");
	printf("Sent File Over\n");
	/****4.关闭套接字 *****/
	chdir("..");
	close(fd);


}

/***************************************
函数名	：File_Sent
作者	：XIE
维护时间：2023/3/6
功能	：用户发送给服务器 <客户端文件>的整体函数框架
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void File_Sent(int cid)
{
	char buf[SIZE]{};

	printf("---------------------------------------\n");
	Sent_Dir_Client(); //客户端文件读取目录

	printf("Sent A File \n");
	printf("if want to quit,please sent <quit>\n");
	printf("if want to continue,please enter file name\n");
	printf("---------------------------------------\n");
	scanf("%s", buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}
	Sent_File_Client(cid);//发送文件给服务器

}

/***************************************
函数名	：File_Service_Recive
作者	：XIE
维护时间：2023/3/6
功能	：接收服务器发过来的文件<服务器文件>的整体函数框架
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void File_Service_Recive(int cid)//接收服务器文件
{

	char buf[SIZE]{};

	printf("---------------------------------------\n");
	Recive_Dir_Client(cid); //服务器文件读取目录

	printf("Receive A Servicer File \n");
	printf("if want to quit,please sent <quit>\n");
	printf("if want to continue,please enter file name\n");
	printf("---------------------------------------\n");
	scanf("%s", buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}
	write(cid, buf, SIZE);

	Recive_File_Servicer(cid, buf);//文件接收
}

/***************************************
函数名	：File_Client_Recive
作者	：XIE
维护时间：2023/3/6
功能	：接收服务器发过来的文件<客户端文件>的整体函数框架
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void File_Client_Recive(int cid)//接收客户端文件                                                                                                                                           
{
	char buf[SIZE]{};
	write(cid, name, SIZE);//发送用户名给服务器

	printf("---------------------------------------\n");
	Recive_Dir_Client(cid); //服务器中存储的客户端文件读取目录

	printf("Receive A Client File \n");
	printf("if want to quit,please sent <quit>\n");;
	printf("---------------------------------------\n");
	scanf("%s", buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}

	write(cid, buf, SIZE);
	write(cid, name, SIZE);//发送用户名给服务器

	Recive_File_Client(cid, buf);//接收客户端文件

}

/***************************************
函数名	：Client_File_Delete
作者	：XIE
维护时间：2023/3/6
功能	：删除服务器的<客户端文件>的整体函数框架
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Client_File_Delete(int cid)
{
	char buf[SIZE]{};
	char flag[SIZE]{};

	printf("---------------------------------------\n");

	write(cid, name, SIZE);//发送用户名给服务器
	Recive_Dir_Client(cid); //服务器中存储的客户端文件读取目录

	printf("Delete A Client File \n");
	printf("if want to quit,please sent <quit>\n");;
	printf("---------------------------------------\n");

	
	scanf("%s",buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}
	
	write(cid, buf, SIZE);//发送文件名给服务器
	write(cid, name, SIZE);//发送文件名给服务器

	printf("name : %s\n", name);
	printf("filename : %s\n", buf);

	read(cid, flag, SIZE);//获取文件删除状态

	if (strcmp(flag, "Succseee Delete") == 0)
	{
		printf("File :%s  Is  Delete\n", buf);
	}
	else
	{
		printf("File :%s  Not Delete\n", buf);
	}
}

/***************************************
函数名	：Print
作者	：XIE
维护时间：2023/3/6
功能	：进度条
参数	：（int len）
参数类型：传入参数
参数作用：传入文件长度
***************************************/
void Print(int len)
{
	if (len == 0)
	{
		len = 1;
	}
	char buffer[NUM + 1] = { 0 };//存储进度条字符
	char arr[5] = { "-/|\\" };//存储基本的变化字幕
	for (int i = 0; i < NUM; ++i)
	{
		buffer[i] = '#';
		printf("[%-100s][%d%%][%c]\r", buffer, i + 1, arr[i % 4]);
		fflush(stdout);
		usleep(60000 / len);
	}
	printf("\n");
}


