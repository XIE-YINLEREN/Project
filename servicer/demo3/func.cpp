#include "service.h"

/***************************************
函数名	：Dir_Service
作者	：XIE
维护时间：2023/3/6
功能	：发送<服务器>文件目录给客户端
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Dir_Service(int cid)
{
	char user[SIZE]{};
	char dirname[SIZE]{};
	char buf[SIZE]{};

	DIR* dir = opendir("/home/student/projects/servicer/file");//打开服务器文件目


	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	struct dirent* dnt;

	while ((dnt = readdir(dir)) != NULL)// 只要返回结果不为NULL，就一直遍历
	{
		printf("%s\n", dnt->d_name);
		strcpy(buf, dnt->d_name);
		if (strcmp(buf, ".") != 0 && strcmp(buf, "..") != 0)
		{
			write(cid, buf, SIZE);
			memset(buf, 0, SIZE);
		}
	}
	write(cid, "NULL", strlen("NULL"));
	closedir(dir);

	printf("Dir Sent Over\n");

	Syslog(user, "----Recive Servicer's File");
}


/***************************************
函数名	：Dir_Client
作者	：XIE
维护时间：2023/3/6
功能	：发送<客户端>文件目录给客户端
参数	：（int cid）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void Dir_Client(int cid)
{
	char name[SIZE]{};
	char realdir[SIZE]{};

	read(cid, name, SIZE);//获取用户名

	chdir(name);//到达用户的文件夹
	sprintf(realdir, "/home/student/projects/servicer/bin/x64/Debug/%s", name);

	printf("Cilent :%s \n", name);
	printf("Dir    :%s\n", realdir);

	DIR* dir = opendir(realdir);//打开用户目录

	char buf[SIZE];

	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	struct dirent* dnt;

	while ((dnt = readdir(dir)) != NULL)// 只要返回结果不为NULL，就一直遍历
	{
		printf("%s\n", dnt->d_name);
		strcpy(buf, dnt->d_name);
		if (strcmp(buf, ".") != 0 && strcmp(buf, "..") != 0)
		{
			write(cid, buf, SIZE);
			memset(buf, 0, SIZE);
		}
	}
	write(cid, "NULL", strlen("NULL")); 

	closedir(dir);
	printf("Dir Sent Over\n");
}


/***************************************
函数名	：File_Service
作者	：XIE
维护时间：2023/3/6
功能	：发送<客户端>文件给客户端
参数	：（int tcp_socket）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void File_Service(int tcp_socket)
{
	data_t cmd{};
	char name[SIZE]{}; //文件名

	read(tcp_socket, name, SIZE); //获取要发送的文件名

	struct stat stat_buf;//存取文件名 文件大小

	chdir("/home/student/projects/servicer/file");//找到文件目录

	if (stat(name, &stat_buf) != 0)        //获取文件信息
	{
		perror("stat");
		return;
	}

	cmd.file_len = stat_buf.st_size;
	char* str = strrchr(name, '/');

	if (str != NULL) //找到了 
	{
		str += 1;   //往后移动一位
	}
	else
	{
		str = name;
	}
	strcpy(cmd.file_name, str);  //获取文件名

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len / SIZE);

	int fd = open(cmd.file_name, O_RDONLY);

	if (fd < 0)
	{
		perror("open");
		return;
	}

	write(tcp_socket, &cmd, sizeof(cmd));     //发送包头:文件名　+　文件大小

	/***** 循环读取文件并发送 ****/
	char buf[SIZE]{};
	int len = 0;
	while (cmd.file_len > 0)
	{
		len = read(fd, buf, 1024);        //读文件
		write(tcp_socket, buf, len);      //写入
		cmd.file_len -= len;

	}
	printf("file over\n");

	/****4.关闭套接字 *****/
	close(fd);
}


/***************************************
函数名	：DateBase_Operate
作者	：XIE
维护时间：2023/3/6
功能	：数据库函数主体框架
参数	：（void* arg）
参数类型：传入参数
参数作用：传入 Cid 句柄
***************************************/
void* DateBase_Operate(void* arg)
{
	int cid = *(int*)arg;
	sqlite3* dp = nullptr;//数据库句柄
	sqlite3_open("/home/student/projects/servicer/person.db", &dp);//打开数据库

	int temp = 0;
	int len = 0;
	char buf[SIZE]{};

	printf("---------------------------------------\n");
	printf("DateBase Funciton\n");

	len = read(cid, buf, SIZE);
	if (len <= 0)
	{
		return arg;
	}
	if (strcmp(buf, "Login") == 0)
	{
		printf("Login Function\n");
		Login_DateBase(dp, cid); //登录
		return arg;
	}
	else if (strcmp(buf, "Regiset") == 0)
	{
		printf("Regiset Function\n");
		Regiset_DateBase(dp, cid);//注册
	}
	printf("---------------------------------------\n");



	sqlite3_close(dp);
	pthread_exit(NULL);
}

/***************************************
函数名	：Login_DateBase
作者	：XIE
维护时间：2023/3/6
功能	：运用数据库验证登录
参数	：（void* arg）
参数类型：传入参数
参数作用：传入 数据库句柄和 Cid 句柄
***************************************/
int Login_DateBase(sqlite3* dp, int cid)
{
	char Sql_Select[SIZE]{};
	char name[20]{};
	char password[20]{};
	char* err = nullptr;
	char** Result = nullptr;
	int Row = -1;
	int Column = -1;


	read(cid, name, SIZE);		//用户名
	read(cid, password, SIZE);	//密码


	sprintf(Sql_Select, "select name,password from  person  where name='%s' and password = '%s';", name, password);

	if (sqlite3_get_table(dp, Sql_Select, &Result, &Row, &Column, &err) != 0)
	{
		perror("sqlite3_get_table");
	}
	else
	{
		if ((Row > 0) && (Column > 0))
		{
			printf("Login Succsee\n");
			write(cid, "Login Succsee", SIZE);

			Syslog(name, "----visited");

			Message(cid);
			return -1;
		}
		else
		{
			printf("Login Fail\n");
			write(cid, "Login Fail", SIZE);
		}
	}

}

/***************************************
函数名	：Syslog
作者	：XIE
维护时间：2023/3/6
功能	：服务器记录日志
参数	：（char name[SIZE],char buf[SIZE]）
参数类型：传入参数
参数作用：传入 用户名和 用户操作
***************************************/
void Syslog(char name[SIZE],char buf[SIZE])
{
	chdir("/home/student/projects/servicer");
	int fd = open("syslog.txt", O_RDWR|O_APPEND);

	char* str = NULL;
	time_t tmp = 0;
	time(&tmp);
	str = ctime(&tmp);

	write(fd, str, 17);
	write(fd, name, strlen(name));
	write(fd, buf, strlen(buf));
	write(fd, "\n", 1);

	close(fd);
	printf("Syslog Over\n");
	chdir("/home/student/projects/servicer/bin/x64/Debug");
}


/***************************************
函数名	：Regiset_DateBase
作者	：XIE
维护时间：2023/3/6
功能	：客户端注册
参数	：（sqlite3* dp, int cid）
参数类型：传入参数
参数作用：传入 数据库句柄和 Cid 句柄
***************************************/
void Regiset_DateBase(sqlite3* dp, int cid)
{
	char Sql_Insert[SIZE]{};
	char name[20]{};
	char password[20]{};
	char password_Re[20]{};
	char* err = nullptr;

	read(cid, name, SIZE);
	read(cid, password, SIZE);

	sprintf(Sql_Insert, "insert into person(name,password) values('%s','%s');", name, password);

	if (sqlite3_exec(dp, Sql_Insert, __null, NULL, &err) != 0)
	{
		printf("%s", err);
		write(cid, "Registr Fail", SIZE);
	}
	write(cid, "Registr Succsee", SIZE);
	printf("%s Regiset Success\n", name);

	Syslog(name, "----Regiset");
	Message(cid);
}



/***************************************
函数名	：Recive_File
作者	：XIE
维护时间：2023/3/6
功能	：接收文件
参数	：（int cid）
参数类型：传入参数
参数作用：传入Cid 句柄
***************************************/
void Recive_File(int cid)
{
	data_t cmd{};
	char name[SIZE]{};
	char realname[SIZE]{};
	//'chdir("/home/student/projects/servicer/bin/x64/Debug");

	read(cid, name, SIZE);//读取用户名称 来确定文件夹位置
	sprintf(realname, "/home/student/projects/servicer/bin/x64/Debug/%s", name);
	printf("---------------------------------------\n");
	printf("user :%s\n", name);
	printf("dir  :%s\n", realname);

	if (chdir(realname) == -1)//到达用户指定文件夹
	{
		mkdir(name, 0777);//创建用户文件夹
	}
	chdir(realname); //到达用户指定文件夹



	read(cid, &cmd, sizeof(cmd)); //接收文件名和大小
	remove(cmd.file_name);
	int fd = open(cmd.file_name, O_WRONLY | O_CREAT, 0666);
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
	printf("Receive File Over\n");
}


/***************************************
函数名	：File_Cilent
作者	：XIE
维护时间：2023/3/6
功能	：发送<客户端>文件给客户端
参数	：（int cid）
参数类型：传入参数
参数作用：传入Cid 句柄
***************************************/
void File_Cilent(int cid)
{
	data_t cmd{};
	char name[SIZE]{}; //文件名
	char user[SIZE]{};
	char dir[SIZE]{};

	read(cid, name, SIZE); //获取要发送的文件名
	read(cid, user, SIZE);//获取用户名

	sprintf(dir, "/home/student/projects/servicer/bin/x64/Debug/%s", user);

	printf("user: %s\n", user);
	printf("file: %s\n", name);
	printf("dir : %s\n", dir);

	struct stat stat_buf;//存取文件名 文件大小

	if (chdir(dir) == -1)//找到文件目录
	{
		printf("Nothing File\n");
		//write(cid, "Nothing File", SIZE);
		return;
	}

	if (stat(name, &stat_buf) != 0)        //获取文件信息
	{
		perror("stat");
		return;
	}

	cmd.file_len = stat_buf.st_size;
	char* str = strrchr(name, '/');

	if (str != NULL) //找到了 
	{
		str += 1;   //往后移动一位
	}
	else
	{
		str = name;
	}
	strcpy(cmd.file_name, str);  //获取文件名

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len/SIZE);

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
	printf("file over\n");
	Syslog(user, "----Recive Client's  File");
	/****4.关闭套接字 *****/
	close(fd);
}


/***************************************
函数名	：Delete
作者	：XIE
维护时间：2023/3/6
功能	：删除<客户端>文件
参数	：（int cid）
参数类型：传入参数
参数作用：传入Cid 句柄
***************************************/
void Delete(int cid)
{
	char filename[SIZE]{};
	char user[SIZE]{};

	read(cid, filename, SIZE); //获取文件名
	read(cid, user, SIZE); //获取用户名

	printf("filename : %s\n",filename);
	printf("user : %s\n",user);

	chdir("/home/student/projects/servicer/bin/x64/Debug");

	if (chdir(user) == -1)
	{
		perror("chdir");
		write(cid, "No File", SIZE);//向客户端发送<没有文件>信号
		return;
	}

	remove(filename);
	write(cid, "Succseee Delete", SIZE);//向客户端发送<删除成功>信号

	printf("Delete Over\n");

	Syslog(user, "----Delete Client's File");
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
        usleep(60000/len);
    }
    printf("\n");
}
