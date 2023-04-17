#include "service.h"

/***************************************
������	��Dir_Service
����	��XIE
ά��ʱ�䣺2023/3/6
����	������<������>�ļ�Ŀ¼���ͻ���
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Dir_Service(int cid)
{
	char user[SIZE]{};
	char dirname[SIZE]{};
	char buf[SIZE]{};

	DIR* dir = opendir("/home/student/projects/servicer/file");//�򿪷������ļ�Ŀ


	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	struct dirent* dnt;

	while ((dnt = readdir(dir)) != NULL)// ֻҪ���ؽ����ΪNULL����һֱ����
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
������	��Dir_Client
����	��XIE
ά��ʱ�䣺2023/3/6
����	������<�ͻ���>�ļ�Ŀ¼���ͻ���
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Dir_Client(int cid)
{
	char name[SIZE]{};
	char realdir[SIZE]{};

	read(cid, name, SIZE);//��ȡ�û���

	chdir(name);//�����û����ļ���
	sprintf(realdir, "/home/student/projects/servicer/bin/x64/Debug/%s", name);

	printf("Cilent :%s \n", name);
	printf("Dir    :%s\n", realdir);

	DIR* dir = opendir(realdir);//���û�Ŀ¼

	char buf[SIZE];

	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	struct dirent* dnt;

	while ((dnt = readdir(dir)) != NULL)// ֻҪ���ؽ����ΪNULL����һֱ����
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
������	��File_Service
����	��XIE
ά��ʱ�䣺2023/3/6
����	������<�ͻ���>�ļ����ͻ���
����	����int tcp_socket��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void File_Service(int tcp_socket)
{
	data_t cmd{};
	char name[SIZE]{}; //�ļ���

	read(tcp_socket, name, SIZE); //��ȡҪ���͵��ļ���

	struct stat stat_buf;//��ȡ�ļ��� �ļ���С

	chdir("/home/student/projects/servicer/file");//�ҵ��ļ�Ŀ¼

	if (stat(name, &stat_buf) != 0)        //��ȡ�ļ���Ϣ
	{
		perror("stat");
		return;
	}

	cmd.file_len = stat_buf.st_size;
	char* str = strrchr(name, '/');

	if (str != NULL) //�ҵ��� 
	{
		str += 1;   //�����ƶ�һλ
	}
	else
	{
		str = name;
	}
	strcpy(cmd.file_name, str);  //��ȡ�ļ���

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len / SIZE);

	int fd = open(cmd.file_name, O_RDONLY);

	if (fd < 0)
	{
		perror("open");
		return;
	}

	write(tcp_socket, &cmd, sizeof(cmd));     //���Ͱ�ͷ:�ļ�����+���ļ���С

	/***** ѭ����ȡ�ļ������� ****/
	char buf[SIZE]{};
	int len = 0;
	while (cmd.file_len > 0)
	{
		len = read(fd, buf, 1024);        //���ļ�
		write(tcp_socket, buf, len);      //д��
		cmd.file_len -= len;

	}
	printf("file over\n");

	/****4.�ر��׽��� *****/
	close(fd);
}


/***************************************
������	��DateBase_Operate
����	��XIE
ά��ʱ�䣺2023/3/6
����	�����ݿ⺯��������
����	����void* arg��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void* DateBase_Operate(void* arg)
{
	int cid = *(int*)arg;
	sqlite3* dp = nullptr;//���ݿ���
	sqlite3_open("/home/student/projects/servicer/person.db", &dp);//�����ݿ�

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
		Login_DateBase(dp, cid); //��¼
		return arg;
	}
	else if (strcmp(buf, "Regiset") == 0)
	{
		printf("Regiset Function\n");
		Regiset_DateBase(dp, cid);//ע��
	}
	printf("---------------------------------------\n");



	sqlite3_close(dp);
	pthread_exit(NULL);
}

/***************************************
������	��Login_DateBase
����	��XIE
ά��ʱ�䣺2023/3/6
����	���������ݿ���֤��¼
����	����void* arg��
�������ͣ��������
�������ã����� ���ݿ����� Cid ���
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


	read(cid, name, SIZE);		//�û���
	read(cid, password, SIZE);	//����


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
������	��Syslog
����	��XIE
ά��ʱ�䣺2023/3/6
����	����������¼��־
����	����char name[SIZE],char buf[SIZE]��
�������ͣ��������
�������ã����� �û����� �û�����
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
������	��Regiset_DateBase
����	��XIE
ά��ʱ�䣺2023/3/6
����	���ͻ���ע��
����	����sqlite3* dp, int cid��
�������ͣ��������
�������ã����� ���ݿ����� Cid ���
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
������	��Recive_File
����	��XIE
ά��ʱ�䣺2023/3/6
����	�������ļ�
����	����int cid��
�������ͣ��������
�������ã�����Cid ���
***************************************/
void Recive_File(int cid)
{
	data_t cmd{};
	char name[SIZE]{};
	char realname[SIZE]{};
	//'chdir("/home/student/projects/servicer/bin/x64/Debug");

	read(cid, name, SIZE);//��ȡ�û����� ��ȷ���ļ���λ��
	sprintf(realname, "/home/student/projects/servicer/bin/x64/Debug/%s", name);
	printf("---------------------------------------\n");
	printf("user :%s\n", name);
	printf("dir  :%s\n", realname);

	if (chdir(realname) == -1)//�����û�ָ���ļ���
	{
		mkdir(name, 0777);//�����û��ļ���
	}
	chdir(realname); //�����û�ָ���ļ���



	read(cid, &cmd, sizeof(cmd)); //�����ļ����ʹ�С
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
������	��File_Cilent
����	��XIE
ά��ʱ�䣺2023/3/6
����	������<�ͻ���>�ļ����ͻ���
����	����int cid��
�������ͣ��������
�������ã�����Cid ���
***************************************/
void File_Cilent(int cid)
{
	data_t cmd{};
	char name[SIZE]{}; //�ļ���
	char user[SIZE]{};
	char dir[SIZE]{};

	read(cid, name, SIZE); //��ȡҪ���͵��ļ���
	read(cid, user, SIZE);//��ȡ�û���

	sprintf(dir, "/home/student/projects/servicer/bin/x64/Debug/%s", user);

	printf("user: %s\n", user);
	printf("file: %s\n", name);
	printf("dir : %s\n", dir);

	struct stat stat_buf;//��ȡ�ļ��� �ļ���С

	if (chdir(dir) == -1)//�ҵ��ļ�Ŀ¼
	{
		printf("Nothing File\n");
		//write(cid, "Nothing File", SIZE);
		return;
	}

	if (stat(name, &stat_buf) != 0)        //��ȡ�ļ���Ϣ
	{
		perror("stat");
		return;
	}

	cmd.file_len = stat_buf.st_size;
	char* str = strrchr(name, '/');

	if (str != NULL) //�ҵ��� 
	{
		str += 1;   //�����ƶ�һλ
	}
	else
	{
		str = name;
	}
	strcpy(cmd.file_name, str);  //��ȡ�ļ���

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len/SIZE);

	int fd = open(cmd.file_name, O_RDONLY);

	if (fd < 0)
	{
		perror("open");
		return;
	}

	write(cid, &cmd, sizeof(cmd));     //���Ͱ�ͷ:�ļ�����+���ļ���С

	/***** ѭ����ȡ�ļ������� ****/
	char buf[SIZE]{};
	int len = 0;
	while (cmd.file_len > 0)
	{
		len = read(fd, buf, 1024);        //���ļ�
		write(cid, buf, len);      //д��
		cmd.file_len -= len;

	}
	printf("file over\n");
	Syslog(user, "----Recive Client's  File");
	/****4.�ر��׽��� *****/
	close(fd);
}


/***************************************
������	��Delete
����	��XIE
ά��ʱ�䣺2023/3/6
����	��ɾ��<�ͻ���>�ļ�
����	����int cid��
�������ͣ��������
�������ã�����Cid ���
***************************************/
void Delete(int cid)
{
	char filename[SIZE]{};
	char user[SIZE]{};

	read(cid, filename, SIZE); //��ȡ�ļ���
	read(cid, user, SIZE); //��ȡ�û���

	printf("filename : %s\n",filename);
	printf("user : %s\n",user);

	chdir("/home/student/projects/servicer/bin/x64/Debug");

	if (chdir(user) == -1)
	{
		perror("chdir");
		write(cid, "No File", SIZE);//��ͻ��˷���<û���ļ�>�ź�
		return;
	}

	remove(filename);
	write(cid, "Succseee Delete", SIZE);//��ͻ��˷���<ɾ���ɹ�>�ź�

	printf("Delete Over\n");

	Syslog(user, "----Delete Client's File");
}

/***************************************
������	��Print
����	��XIE
ά��ʱ�䣺2023/3/6
����	��������
����	����int len��
�������ͣ��������
�������ã������ļ�����
***************************************/
void Print(int len)
{
	if (len == 0)
	{
		len = 1;
	}
	char buffer[NUM + 1] = { 0 };//�洢�������ַ�
    char arr[5] = { "-/|\\" };//�洢�����ı仯��Ļ
    for (int i = 0; i < NUM; ++i) 
    {
		buffer[i] = '#';
        printf("[%-100s][%d%%][%c]\r", buffer, i + 1, arr[i % 4]);
        fflush(stdout);
        usleep(60000/len);
    }
    printf("\n");
}
