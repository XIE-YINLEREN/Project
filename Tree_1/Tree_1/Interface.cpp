#include "Interface.h"

void gotoxy(int x, int y)
{
	COORD p{};
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p.X = x; p.Y = y;
	SetConsoleCursorPosition(handle, p);
}

void ShowFace_Frame()
{
	system("mode con:cols=100 lines=40");
	gotoxy(20, 6);
	printf("*******************************************************");
	for (int i = 7; i < 28; i++)
	{
		gotoxy(20, i);
		printf("***\t\t\t\t\t\t\t***");
	}

}

void ShowFace_Main()
{
	gotoxy(20, 27);
	printf("*******************************************************");
	gotoxy(30, 10);
	printf("欢迎来到本程序，输入对应序列数字实现功能");
	gotoxy(30, 13);
	printf("1.新建一个二叉树");
	gotoxy(30, 15);
	printf("2.用图的形式查看二叉树");
	gotoxy(30, 17);
	printf("3.对当前二叉树进行增删改查");
	gotoxy(30, 19);
	printf("4.遍历二叉树");
	gotoxy(30, 21);
	printf("5.查看历史创建的树");
	gotoxy(30, 23);
	printf("6.退出");
	gotoxy(30, 26);
}

void ShowFace_Funciton()
{
	ShowFace_Frame();
	gotoxy(30, 11);
	printf("1.对当前二叉树增加节点");
	gotoxy(30, 13);
	printf("2.对当前二叉树删除节点");
	gotoxy(30, 15);
	printf("3.对当前二叉树修改节点");
	gotoxy(30, 17);
	printf("4.对当前二叉树查找节点");
	gotoxy(30, 19);
	printf("5.显示当前二叉树");
	gotoxy(30, 21);
	printf("6.退出当前功能");
	gotoxy(20, 27);
	printf("*******************************************************");
}

