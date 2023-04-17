#pragma once		
#ifndef __TREE_H_
#define __TREE_H_
typedef struct tree
{
	char num;
	struct tree* lnext;
	struct tree* rnext;
}Tree;
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "File.h"
#include "Queue.h"
#include "Interface.h"
#include "Draw.h"

void TreeCreate_Pre(Tree** head);
void __TreeCreate_Pre(Tree** head, char* str);
int  TreeCreate(Tree** h, char* str, int n);
void TreeAdd_Pre(Tree** head);
void TreeAdd(Tree** head, char flag, char To_flag, int LR_flag);
void TreeDel_Pre(Tree* head);
void TreeDel(Tree* head, char flag);
void TreeSearch_Pre(Tree* head);
int  TreeSearch(Tree* h, char ch);
void TreeModify_Pre(Tree** head);
void TreeModify(Tree** head , char flag,char To_flag);
void TreeLevelShow(Tree* h);
void TreePreShow_Pre();
void TreePreShow(Tree* h);
void TreeInShow_Pre();
void TreeInShow(Tree* h);
void TreePostShow_Pre();
void TreePostShow(Tree* head);
Tree* Init_Tree();

#endif
