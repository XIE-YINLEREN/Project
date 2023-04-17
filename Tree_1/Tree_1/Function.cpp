#include "Function.h"

Tree* head;

void Function()
{
	head = Init_Tree();
	int flag = -1;
	while (true)
	{
		ShowFace_Frame();
		ShowFace_Main();
		char* str;	
		scanf_s("%d", &flag, sizeof(flag));
		if (flag >= 0 && flag <= 9)
		{
			switch (flag)
			{
			case 1:
			{
				system("cls");
				TreeCreate_Pre(&head);
				_getch();
				break;
			}
			case 2:
			{
				system("cls");
				Draw(head);
				_getch();
				break;
			}
			case 3:
			{
				system("cls");
				Choice_Function();
				break;
			}
			case 4:
			{
				system("cls");
				TreeLevelShow(head);	//层次遍历
				TreePreShow_Pre();
				TreePreShow(head);		//先序遍历
				TreeInShow_Pre();		//中序遍历
				TreeInShow(head);
				TreePostShow_Pre();		//后序遍历
				TreePostShow(head);
				_getch();
				break;
			}
			case 5:
			{
				system("cls");
				str = FileRead();
				_getch();
				break;
			}
			case 6:
			{
				system("cls");
				exit(-1);
				_getch();
				break;
			}
			default:
			{
				gotoxy(30, 25);
				printf("在按回车键后，重新输入");
				_getch();
				break;
			}
			}
		}
		else
		{
			gotoxy(30, 25);
			printf("输入有误，在按回车键后，重新输入");
			getchar();
			getchar();
			getchar();
		}
		
		
	}
}

void Choice_Function()
{
	int flag = 0;
	ShowFace_Funciton();
	while (true)
	{
		system("cls");
		ShowFace_Funciton();
		gotoxy(30, 23);
		scanf_s("%d", &flag);
		switch (flag)
		{
			case 1:
			{
				system("cls");
				TreeAdd_Pre(&head);
				_getch();
				break;
			}
			case 2:
			{
				system("cls");
				TreeDel_Pre(head);
				_getch();
				break;
			}
			case 3:
			{
				system("cls");
				TreeModify_Pre(&head);
				_getch();
				break;
			}
			case 4:
			{
				system("cls");
				TreeSearch_Pre(head);
				_getch();
				break;
			}
			case 5:
			{
				system("cls");
				Draw(head);
				_getch();
				break;
			}
			case 6:
			{
				system("cls");
				return;
			}
		default:
			{
				gotoxy(30, 23);
				printf("输入有误，重新输入");
				_getch();
				break;
			}

		}
	}
}
