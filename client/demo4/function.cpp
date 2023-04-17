#include "main.h"
char name[SIZE]{};

/***************************************
������	��Recive_Dir_Client
����	��XIE
ά��ʱ�䣺2023/3/6
����	�����շ����������û���<�ͻ����ļ�Ŀ¼>
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Recive_Dir_Client(int cid)
{
	char buf[SIZE]{};
	ssize_t flag = 0;
	while (1)
	{
		flag = read(cid, buf, SIZE);
		if (flag <= 0) //�ݴ���
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
������	��Recive_File_Servicer
����	��XIE
ά��ʱ�䣺2023/3/13
����	�����շ��������͸��û���<�������ļ�>
����	����int cid, char filename[20]��
�������ͣ��������
�������ã����� Cid ��� �� �ļ���
***************************************/
void Recive_File_Servicer(int cid, char filename[20])
{
	data_t cmd;
	read(cid, &cmd, sizeof(cmd)); //�����ļ����ʹ�С
	chdir("/home/student/projects/client/bin/x64/Debug");

	if (chdir(name) == -1)
	{
		mkdir(name,0777);
	}

	chdir(name);
	
	remove(filename); //��ɾ���ļ� �����ļ��ظ�
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

	while (cmd.file_len > 0) //ѭ�����տͻ��˷��������ļ�
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
������	��Recive_File_Client
����	��XIE
ά��ʱ�䣺2023/3/6
����	�����շ��������͸��ͻ��˵� <�ͻ����ļ�> 
����	����int cid, char filename[20]��
�������ͣ��������
�������ã����� Cid ��� �� �ļ���
***************************************/
void Recive_File_Client(int cid, char filename[20])
{
	data_t cmd;
	read(cid, &cmd, sizeof(cmd)); //�����ļ����ʹ�С
	char dir[SIZE]{};


	if (chdir(name) == -1)//�����û��ļ���
	{
		mkdir(name, 0777);
	}

	chdir(name);

	remove(filename);//ɾ���ļ�

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


/*�ļ��շ�������*/
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

/*�ͻ��˵�¼������*/
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
������	��DateBase_Operate
����	��XIE
ά��ʱ�䣺2023/3/6
����	���ͻ��˵�¼�������
����	����int cid��
�������ͣ��������
�������ã�Cid ���
***************************************/
void DateBase_Operate(int cid)
{
	sqlite3* dp = nullptr;//���ݿ���
	sqlite3_open("/home/student/projects/servicer/person.db", &dp);//�����ݿ�

	char flag_long[SIZE]{};
	int temp = 0;

	write(cid, "DateBase", SIZE);

Loop:
	DateBase_Interface();//��¼ע�����
	scanf("%s", flag_long);
	char* flag = flag_long;
	if ((*flag - 48) == 1 && (strlen(flag_long) == 1))
	{
		temp = Login_DateBase(dp, cid);//��¼

		if (temp == -1)
		{
			exit(1);
		}
	}
	else if ((*flag - 48) == 2 && (strlen(flag_long) == 1))
	{
		Regiset_DateBase(dp, cid);//ע��
	}
	else
	{
		printf("Error Enter! \n");
		printf("Please Reenter\n");
		goto Loop;
	}
}

/***************************************
������	��Login_DateBase
����	��XIE
ά��ʱ�䣺2023/3/6
����	�������û���¼��Ϣ��������
����	����sqlite3* dp, int cid��
�������ͣ��������
�������ã����� ���ݿ��� �� Cid ���
***************************************/
int Login_DateBase(sqlite3* dp, int cid)//�����û���¼��Ϣ��������
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
	read(cid, buf, SIZE); //��ȡ���������صĵ�¼״̬��Ϣ

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
������	��Regiset_DateBase
����	��XIE
ά��ʱ�䣺2023/3/6
����	�������û�ע����Ϣ��������
����	����sqlite3* dp, int cid��
�������ͣ��������
�������ã����� ���ݿ��� �� Cid ���
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

	write(cid, name, SIZE);//��Ҫע������ֺ������������
	write(cid, password, SIZE);

	read(cid, buf, SIZE);//��ȡ�Ƿ�ע��ɹ�

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
������	��Sent_Dir_Client
����	��XIE
ά��ʱ�䣺2023/3/6
����	����ʾ�ͻ��˿ɷ��͸����������ļ�
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Sent_Dir_Client()
{
	DIR* dir = opendir(name);//��һ��Ŀ¼

	if (dir == NULL)
	{
		perror("opendir");
		return;
	}

	struct dirent* dnt;

	while ((dnt = readdir(dir)) != NULL)// ֻҪ���ؽ����ΪNULL����һֱ����
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
������	��Sent_File_Client
����	��XIE
ά��ʱ�䣺2023/3/6
����	���û����͸������� <�ͻ����ļ�>
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Sent_File_Client(int cid)
{

	data_t cmd{};
	char Filename[SIZE]{}; //�ļ���

	write(cid, name, SIZE);//�����Լ������ƹ�ȥ  ʹ�ù̶����ļ���

	printf("Sent  File  Name is:\n");
	scanf("%s", Filename);

	struct stat stat_buf;//��ȡ�ļ��� �ļ���С

	chdir(name);//�ҵ��ļ�Ŀ¼

	if (stat(Filename, &stat_buf) != 0)        //��ȡ�ļ���Ϣ
	{
		perror("stat");
		return;
	}

	cmd.file_len = stat_buf.st_size;
	char* str = strrchr(Filename, '/');

	if (str != NULL) //�ҵ��� 
	{
		str += 1;   //�����ƶ�һλ
	}
	else
	{
		str = Filename;
	}
	strcpy(cmd.file_name, str);  //��ȡ�ļ���

	printf("file name:%s\n", cmd.file_name);
	printf("file size:%d\n", cmd.file_len);

	Print(cmd.file_len / SIZE);//������

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

	printf("---------------------------------------\n");
	printf("Sent File Over\n");
	/****4.�ر��׽��� *****/
	chdir("..");
	close(fd);


}

/***************************************
������	��File_Sent
����	��XIE
ά��ʱ�䣺2023/3/6
����	���û����͸������� <�ͻ����ļ�>�����庯�����
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void File_Sent(int cid)
{
	char buf[SIZE]{};

	printf("---------------------------------------\n");
	Sent_Dir_Client(); //�ͻ����ļ���ȡĿ¼

	printf("Sent A File \n");
	printf("if want to quit,please sent <quit>\n");
	printf("if want to continue,please enter file name\n");
	printf("---------------------------------------\n");
	scanf("%s", buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}
	Sent_File_Client(cid);//�����ļ���������

}

/***************************************
������	��File_Service_Recive
����	��XIE
ά��ʱ�䣺2023/3/6
����	�����շ��������������ļ�<�������ļ�>�����庯�����
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void File_Service_Recive(int cid)//���շ������ļ�
{

	char buf[SIZE]{};

	printf("---------------------------------------\n");
	Recive_Dir_Client(cid); //�������ļ���ȡĿ¼

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

	Recive_File_Servicer(cid, buf);//�ļ�����
}

/***************************************
������	��File_Client_Recive
����	��XIE
ά��ʱ�䣺2023/3/6
����	�����շ��������������ļ�<�ͻ����ļ�>�����庯�����
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void File_Client_Recive(int cid)//���տͻ����ļ�                                                                                                                                           
{
	char buf[SIZE]{};
	write(cid, name, SIZE);//�����û�����������

	printf("---------------------------------------\n");
	Recive_Dir_Client(cid); //�������д洢�Ŀͻ����ļ���ȡĿ¼

	printf("Receive A Client File \n");
	printf("if want to quit,please sent <quit>\n");;
	printf("---------------------------------------\n");
	scanf("%s", buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}

	write(cid, buf, SIZE);
	write(cid, name, SIZE);//�����û�����������

	Recive_File_Client(cid, buf);//���տͻ����ļ�

}

/***************************************
������	��Client_File_Delete
����	��XIE
ά��ʱ�䣺2023/3/6
����	��ɾ����������<�ͻ����ļ�>�����庯�����
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Client_File_Delete(int cid)
{
	char buf[SIZE]{};
	char flag[SIZE]{};

	printf("---------------------------------------\n");

	write(cid, name, SIZE);//�����û�����������
	Recive_Dir_Client(cid); //�������д洢�Ŀͻ����ļ���ȡĿ¼

	printf("Delete A Client File \n");
	printf("if want to quit,please sent <quit>\n");;
	printf("---------------------------------------\n");

	
	scanf("%s",buf);

	if (strcmp(buf, "quit") == 0)
	{
		return;
	}
	
	write(cid, buf, SIZE);//�����ļ�����������
	write(cid, name, SIZE);//�����ļ�����������

	printf("name : %s\n", name);
	printf("filename : %s\n", buf);

	read(cid, flag, SIZE);//��ȡ�ļ�ɾ��״̬

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
		usleep(60000 / len);
	}
	printf("\n");
}


