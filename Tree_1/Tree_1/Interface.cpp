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
	printf("��ӭ���������������Ӧ��������ʵ�ֹ���");
	gotoxy(30, 13);
	printf("1.�½�һ��������");
	gotoxy(30, 15);
	printf("2.��ͼ����ʽ�鿴������");
	gotoxy(30, 17);
	printf("3.�Ե�ǰ������������ɾ�Ĳ�");
	gotoxy(30, 19);
	printf("4.����������");
	gotoxy(30, 21);
	printf("5.�鿴��ʷ��������");
	gotoxy(30, 23);
	printf("6.�˳�");
	gotoxy(30, 26);
}

void ShowFace_Funciton()
{
	ShowFace_Frame();
	gotoxy(30, 11);
	printf("1.�Ե�ǰ���������ӽڵ�");
	gotoxy(30, 13);
	printf("2.�Ե�ǰ������ɾ���ڵ�");
	gotoxy(30, 15);
	printf("3.�Ե�ǰ�������޸Ľڵ�");
	gotoxy(30, 17);
	printf("4.�Ե�ǰ���������ҽڵ�");
	gotoxy(30, 19);
	printf("5.��ʾ��ǰ������");
	gotoxy(30, 21);
	printf("6.�˳���ǰ����");
	gotoxy(20, 27);
	printf("*******************************************************");
}

