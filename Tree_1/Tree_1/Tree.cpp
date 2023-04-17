#include "Tree.h" 

int flag = 0;

Tree* Init_Tree()
{
	Tree* h = (Tree*)malloc(sizeof(Tree));
	if (h == NULL)
	{
		printf("内存分配失败！");
		exit(-1);
	}
	h->lnext = NULL;
	h->rnext = NULL;
	h->num = 0;
	return h;
}

void TreeCreate_Pre(Tree **head)
{
	gotoxy(30, 7);
	printf("输入字符来创建二叉树,输入‘O’退出\n");
	char* str = nullptr;
	str = (char*)malloc(sizeof(char) * STR_SIZE);
	gotoxy(30, 9);
	scanf_s("%s", str, STR_SIZE);
	if (str != NULL)
	{
		if (*(str) == 'O')
		{
			return;
		}
		else if(strlen(str) == TreeCreate(head, str, 0))
		{
			gotoxy(30, 11);
			printf("二叉树建立成功\n");
			FileWrite(str);
			TreeCreate(head,str,0);
			_getch();
		}
	}
}

void __TreeCreate_Pre(Tree** head,char* str)
{
	if (str != NULL)
	{
		if (strlen(str) == TreeCreate(head, str, 0))
		{
			gotoxy(30, 11);
			printf("二叉树建立成功\n");
			TreeCreate(head, str, 0);                                
		}
	}
}

int  TreeCreate(Tree** h, char* str, int n) 
{
	char ch = str[n++];  
	if (ch != '\0') 
	{    
		if (ch == '#') 
		{ 
			*h = NULL;
		}
		else 
		{
			if (!(*h = (Tree*)malloc(sizeof(Tree)))) 
			{
				printf("内存分配失败！");
				exit(-1);
			}
			else 
			{
				(*h)->num = ch;
				n = TreeCreate(&((*h)->lnext), str, n);
				n = TreeCreate(&((*h)->rnext), str, n);
			}
		}
	}
	return n;
}

void TreeLevelShow(Tree* h)
{
	printf("二叉树层次遍历：\n");
	SqQueue* q;
	Init_Queue(&q);
	if (h != NULL)
	{
		EnterQueue(q, h);
	}
	while (!EmptyQueue(q)) 
	{
		if (OutQueue(q, &h) != false)
		{
			printf("%c", h->num);
			if (h->lnext != NULL)
			{
				EnterQueue(q, h->lnext);
			}
			if (h->rnext != NULL)
			{
				EnterQueue(q, h->rnext);
			}
		}
		
	}
}

void TreeInShow_Pre()
{
	printf("\n二叉树中序遍历：\n");
}

void TreeInShow(Tree* h)
{
	if (h!= NULL)
	{
		TreeInShow(h->lnext);
		printf("%c", h->num);
		TreeInShow(h->rnext);
	}
}

void TreePreShow_Pre()
{
	printf("\n二叉树先序遍历：\n");
}

void TreePreShow(Tree *h)
{
	if (h != NULL) 
	{           
		printf("%c", h->num); 
		TreePreShow(h->lnext);
		TreePreShow(h->rnext); 
	}
}

void TreePostShow_Pre()
{
	printf("\n二叉树后序遍历：\n");
}

void TreePostShow(Tree* h)
{
	if (h != NULL)
	{
		TreePreShow(h->lnext);
		TreePreShow(h->rnext);
		printf("%c", h->num);
	}
}

void TreeSearch_Pre(Tree *head)
{
	char ch = 0;
	flag = 0;
	getchar();
	if (head->num == 0)
	{
		gotoxy(30, 11);
		printf("当前没有树的数据，请先输入数据");
	}
	else
	{
		gotoxy(30, 7);
		printf("输入你要查找的字符");
		gotoxy(30, 8);
		scanf_s("%c", &ch, 1);
		if (TreeSearch(head, ch) == 0)
		{
			gotoxy(30, 9);
			printf("该字符 %c 不在二叉树中\n", ch);
		}
	}
	
}

int  TreeSearch(Tree* h, char ch)
{
	if (h == NULL)
	{
		return flag;
	}
	else if(h->num == ch)
	{
		gotoxy(30, 9);
		printf("该字符 %c 在二叉树中\n", ch);
		flag = 1;
		return flag;
	}
	else if(h->num != '#')
	{
		TreeSearch(h->lnext, ch);
		TreeSearch(h->rnext, ch);
	}
}

void TreeAdd_Pre(Tree** head)
{
	char flag = 0, To_flag = 0;
	int LR_flag = -1;
	getchar();
	gotoxy(30, 11);
	printf("输入你要插入的字符：");
	To_flag = getchar();
	gotoxy(30, 13);
	getchar();
	printf("插入到哪个字符后：");
	flag = getchar();
	gotoxy(25, 15);
	printf("插入到左孩子还是右孩子,1为左孩子，2为右孩子：");
	scanf_s("%d", &LR_flag, sizeof(LR_flag));

	TreeAdd(head, flag, To_flag, LR_flag);
}

void TreeAdd(Tree** head, char flag, char To_flag,int LR_flag)
{				//flag是要查找的节点字符  To_flag是要加上的节点字符
				//LR_flag 是判断在左孩子还是右孩子
	if ((*head) == NULL)
	{
		return;
	}
	else if ((*head)->num == flag)
	{
		if (LR_flag == 1 && (*head)->lnext == NULL)
		{
			
			(*head)->lnext = (Tree*)malloc(sizeof(Tree));
			head = &(*head)->lnext;
			(*head)->num = To_flag;
			(*head)->lnext = NULL;
			(*head)->rnext = NULL;
			gotoxy(25, 18);
			printf("插入成功");
			return;
		}
		else if(LR_flag == 2 && (*head)->rnext == NULL)
		{
			(*head)->rnext = (Tree*)malloc(sizeof(Tree));
			head = &(*head)->rnext;
			(*head)->num = To_flag;
			(*head)->lnext = NULL;
			(*head)->rnext = NULL;
			gotoxy(25, 18);
			printf("插入成功");
			
			return;
		}
		else
		{
			gotoxy(25, 18);
			printf("出错！这个位置不能插入节点");
			return;
		}
	}
	else if((*head)->num != '#')
	{
		TreeAdd(&((*head)->lnext), flag, To_flag, LR_flag);
		TreeAdd(&((*head)->rnext), flag, To_flag, LR_flag);
	}
}

void TreeDel_Pre(Tree* head)
{
	char flag = 0;
	getchar();
	gotoxy(30, 11);
	printf("输入你要删除的字符：");
	flag = getchar();
	getchar();
	TreeDel(head, flag);
}

void TreeDel(Tree* head ,char flag)
{
	if ( head == NULL)
	{
		return;
	}
	else if ( head->num == flag)
	{
		gotoxy(30, 15);
		head->num = NULL;
		head->lnext = NULL;
		head->rnext = NULL;
		printf("删除成功");
		return;
	}
	else if (head->num != '#')
	{
		TreeDel(head->lnext, flag);
		TreeDel(head->rnext, flag);
	}
}

void TreeModify_Pre(Tree** head)
{
	char flag = 0, To_flag = 0;
	getchar();
	gotoxy(30, 11);
	printf("输入你要被修改的字符：");
	flag = getchar();
	gotoxy(30, 13);
	getchar();
	printf("替换为：");
	To_flag = getchar();
	getchar();
	TreeModify(head, flag, To_flag);
}

void TreeModify(Tree** head,char flag,char To_flag)
{
	if ((*head) == NULL)
	{
		return ;
	}
	else if ((*head)->num == flag)
	{
		(*head)->num = To_flag;
		gotoxy(30, 15);
		printf("修改成功");
		return ;
	}
	else if ((*head)->num != '#')
	{
		TreeModify(&((*head)->lnext), flag, To_flag);
		TreeModify(&((*head)->rnext), flag, To_flag);
	}
}
