#include"demo.h"

void demo()
{
	
	
}


void abc(int x)
{
	printf("---%d---\n", x);
}

void Signal_processing()
{
	if (fork() == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			sleep(1);
			kill(getppid(), SIGUSR1);
		}
		exit(0);
	}
	else
	{
		signal(SIGUSR1, abc);
		wait(NULL);
		printf("abcdefg\n");
		exit(0);
	}
}

void pipecommunication()
{
	if (mkfifo("./777", 0666) == -1)
	{
		perror("mkfifo");
		exit(-1);
	}
	int fd = open("./777", O_RDWR);
	if (fd < 0)
	{
		perror("open");
		exit(0);
	}
	char a[20]{};
	while (true)
	{
		printf("Input:\n");
		scanf("%s", a);
		write(fd, a, sizeof(a));
		if (strstr(a, "bye") != NULL)
		{
			exit(0);
		}
	}
}

void pipe()
{
	int fd[2];
	//创建管道文件
	int res = pipe(fd);
	if (res < 0)
	{
		perror("pipe");
		exit(-1);
	}
	//创建子进程
	int pid = fork();
	if (pid == 0)
	{
		//先关闭写描述符
		close(fd[1]);
		char buf[10];
		while (1)
		{
			bzero(buf, sizeof(buf));
			//fd[0]是读取端
			read(fd[0], buf, sizeof(buf));
			printf("recv:%s\n", buf);
			if (strcmp(buf, "quit") == 0)
			{
				exit(1);
			}
		}

	}
	//父进程
	if (pid > 0)
	{
		//关闭读描述符
		close(fd[0]);
		char buf[10];
		while (1)
		{
			printf("Input: \n");
			scanf("%s", buf);
			//写入到无名管道中
			write(fd[1], buf, sizeof(buf));
			if (strcmp(buf, "quit") == 0)
			{
				wait(NULL);
				exit(0);
			}
		}
	}

}

void logfile()
{
	openlog("XIE:", LOG_PID, LOG_DAEMON);
	int fd = open("/etc/passwd", O_RDONLY);
	char* str = nullptr;
	int i = 0;
	while (i < 10)
	{
		str = NULL;
		read(fd, str, sizeof(str));
		syslog(LOG_ERR, "%s", str);
		i++;
	}
	close(fd);
	closelog();
}

void guard()//创建守护进程
{
	if (fork() > 0)
	{
		exit(-1);
	}
	if (setsid() == -1)
	{
		printf("创建失败\n");
		exit(-1);
	}
	if (fork() > 0)
	{
		exit(-1);
	}
	umask(0);
	chdir("/tmp");
	int max = sysconf(_SC_OPEN_MAX);
	for (int i = 0; i < max; i++)
	{
		close(i);
	}
	int fd0 = open("/dev/null", O_RDWR);
	dup2(fd0, 0);
	dup2(fd0, 1);
	dup2(fd0, 2);
	FILE* fd = fopen("./xie", "w+");
	if (fd == NULL)
	{
		printf("error");
		exit(-1);
	}
	time_t b;
	char* str = nullptr;
	while (true)
	{
		time(&b);
		str = ctime(&b);
		fputs(str, fd);
		sleep(1);
		fflush(fd);
	}

}

void family()
{
	pid_t a;
	pid_t b;
	printf("--------B------\n");
	a = fork();
	if (0 == a)
	{
		b = fork();
		if (0 == b)
		{

			printf("this is grandson id is %d ---", getpid());
			printf("my father is %d \n", getppid());
			exit(1);
		}
		else
		{
			waitpid(b, NULL, 0);
			printf("this is son id is %d ---", getpid());
			printf("my father is %d \n", getppid());
			exit(1);
		}
	}
	else
	{
		waitpid(a, NULL, 0);
		printf("this is father id is %d ---", getpid());
		printf("my father is %d \n", getppid());
		printf("-----good grandson-----\n");
	}

}

void cp()
{
	char oldfile[20]{}, newfile[20]{};
	char data[10]{};
	char* str = nullptr;
	printf("The first file name is:\n");
	scanf("%s", oldfile);
	remove(oldfile);
	printf("You want to writr to this file'data is:\n");
	scanf("%s", data);
	int fd = open(oldfile, O_CREAT | O_RDWR, 777);
	if (fd < 0)
	{
		perror("open");
	}
	write(fd, data, strlen(data));
	close(fd);
	time_t a;
	time(&a);
	str = ctime(&a);
	printf("The second file name is:\n");
	scanf("%s", newfile);
	int fd1 = open(newfile, O_CREAT | O_RDWR, 777);
	if (fd1 < 0)
	{
		perror("open");
	}
	write(fd1, str, 40);
	write(fd1, data, 10);
	close(fd1);
}

void SleepTime()
{
	char* str = NULL;
	int i = 0;
	remove("1.txt");
	int fd = open("1.txt", O_WRONLY | O_CREAT, 777);
	while (61 != i)
	{
		str = NULL;
		time_t a;
		time(&a);
		str = ctime(&a);
		sleep(1);
		printf("%s\n", str);
		write(fd, str, 30);
		i++;
	}
	close(fd);
}

void SrandTime()
{
	srand(time(NULL));
	int flag = rand();
	printf("%d\n", flag);
}

void Filesearch()
{
	char flag[256]{};
	scanf("%s", flag);
	int fd = access(flag, R_OK);
	if (fd == 0)
	{
		printf("the file is exist \n");
		remove(flag);
	}
	else
	{
		printf("the file is not exist \n");
	}
	close(fd);
}

void ShowDir()
{
	char a[20]{};
	struct dirent* sdp = nullptr;
	printf("What the dir name that you want to open\n");
	scanf("%s", a);
	if (NULL == opendir(a))
	{
		perror("opendir");
	}
	DIR* dp = opendir(a);
	while (((sdp = readdir(dp)) != NULL))
	{
		if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0)
		{
			continue;
		}
		if (sdp->d_type == DT_REG)
		{
			printf("Rugular file");
			printf("--- %s ---\n", sdp->d_name);
		}
		if (sdp->d_type == DT_DIR)
		{
			printf("Dir file");
			printf("--- %s ---\n", sdp->d_name);
		}

	}
}

void Creat_Dir()
{
	char a[40]{}, b[40]{};
	printf("What the dir name that you want to creat\n");
	scanf("%s", a);
	mkdir(a, 0777);
	printf("now dir is %s\n", get_current_dir_name());
	chdir(a);
	printf("What the file name that you want to creat in %s dir \n", a);
	scanf("%s", b);
	int fd = creat(b, 0666);
	write(fd, "abcd", 5);
	printf("now dir is %s\n", get_current_dir_name());
	close(fd);
}

void IsFile(char* name)
{
	int ret = 0;
	struct stat s;
	ret = stat(name, &s);
	if (-1 == ret)
	{
		perror("stat error");
		return;
	}
	if (S_ISDIR(s.st_mode))
	{
		Read_Dir(name);
	}
	printf("%10s\t\t%ld\n", name, s.st_size);
}

void Read_Dir(char* dir)
{
	char path[256];
	DIR* dp;
	struct dirent* sdp;
	dp = opendir(dir);
	if (dp == NULL)
	{
		perror("opendir error");
		return;
	}
	while (((sdp = readdir(dp)) != NULL))
	{
		if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0)
		{
			continue;
		}
		sprintf(path, "%s/%s", dir, sdp->d_name);
		IsFile(path);
	}
	closedir(dp);
	return;
}

void filestr()
{
	int fd = 0;
	int fa = 0;
	fd = open("huaqing.txt", O_WRONLY | O_CREAT, 0777);
	Student* stu = (Student*)malloc(sizeof(Student));
	scanf("%d", &stu->age);
	scanf("%s", stu->name);
	write(fd, stu, sizeof(stu));
	stu->age = 0;
	stu->name;
	close(fd);
	fa = open("huaqing.txt", O_RDONLY);
	read(fd, stu, sizeof(stu));
	printf("%d  %s\n", stu->age, stu->name);
}

void Process_Demo()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (0 == fork())
			break;
	}
	if (5 == i)
	{
		sleep(5);
		printf("This is parent\n");
	}
	else
	{
		sleep(i);
		printf("I'm %dth child\n", i + 1);
	}
	return;
}
