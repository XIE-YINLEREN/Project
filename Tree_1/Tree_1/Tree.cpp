#include "Tree.h" 

int flag = 0;

Tree* Init_Tree()
{
	Tree* h = (Tree*)malloc(sizeof(Tree));
	if (h == NULL)
	{
		printf("�ڴ����ʧ�ܣ�");
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
	printf("�����ַ�������������,���롮O���˳�\n");
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
			printf("�����������ɹ�\n");
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
			printf("�����������ɹ�\n");
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
				printf("�ڴ����ʧ�ܣ�");
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
	printf("��������α�����\n");
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
	printf("\n���������������\n");
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
	printf("\n���������������\n");
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
	printf("\n���������������\n");
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
		printf("��ǰû���������ݣ�������������");
	}
	else
	{
		gotoxy(30, 7);
		printf("������Ҫ���ҵ��ַ�");
		gotoxy(30, 8);
		scanf_s("%c", &ch, 1);
		if (TreeSearch(head, ch) == 0)
		{
			gotoxy(30, 9);
			printf("���ַ� %c ���ڶ�������\n", ch);
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
		printf("���ַ� %c �ڶ�������\n", ch);
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
	printf("������Ҫ������ַ���");
	To_flag = getchar();
	gotoxy(30, 13);
	getchar();
	printf("���뵽�ĸ��ַ���");
	flag = getchar();
	gotoxy(25, 15);
	printf("���뵽���ӻ����Һ���,1Ϊ���ӣ�2Ϊ�Һ��ӣ�");
	scanf_s("%d", &LR_flag, sizeof(LR_flag));

	TreeAdd(head, flag, To_flag, LR_flag);
}

void TreeAdd(Tree** head, char flag, char To_flag,int LR_flag)
{				//flag��Ҫ���ҵĽڵ��ַ�  To_flag��Ҫ���ϵĽڵ��ַ�
				//LR_flag ���ж������ӻ����Һ���
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
			printf("����ɹ�");
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
			printf("����ɹ�");
			
			return;
		}
		else
		{
			gotoxy(25, 18);
			printf("�������λ�ò��ܲ���ڵ�");
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
	printf("������Ҫɾ�����ַ���");
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
		printf("ɾ���ɹ�");
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
	printf("������Ҫ���޸ĵ��ַ���");
	flag = getchar();
	gotoxy(30, 13);
	getchar();
	printf("�滻Ϊ��");
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
		printf("�޸ĳɹ�");
		return ;
	}
	else if ((*head)->num != '#')
	{
		TreeModify(&((*head)->lnext), flag, To_flag);
		TreeModify(&((*head)->rnext), flag, To_flag);
	}
}
