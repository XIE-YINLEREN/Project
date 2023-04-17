#include "File.h"

void FileWrite(char *str)
{
	FILE* fp = nullptr;
	fp = fopen("data.txt", "a");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	if ((fp = fopen("data.txt","a")) == NULL)
	{
		fp = fopen("data.txt", "w");
	}
	fprintf(fp, "%c", 10);
	fputs(str, fp);
	fclose(fp);
}

char* FileRead()
{
	FILE* fp = nullptr;
	char str[STR_SIZE]{};
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("\n文件不能打开\n");
		exit(-1);
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		while (!feof(fp)) 
		{
			memset(str, 0, sizeof(str));
			fread(str, sizeof(char), sizeof(str) - 1, fp);
			printf("历史创建的树为：\n %s", str);
		}
	}
	fclose(fp);
	return str;
}
