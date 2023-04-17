#include "Draw.h"

void Draw_level(Tree* node, bool left, char* str) 
{
    if (node->rnext) 
    {
        Draw_level(node->rnext, false, strcat(str, (left ? "|     " : "      ")));
    }
    printf("%s", str);
    printf("%c", (left ? '\\' : '/'));
    printf("-----");
    printf("%c\n", node->num);
    if (node->lnext) 
    {
        Draw_level(node->lnext , true, strcat(str, (left ? "      " : "|     ")));
    }
    str[strlen(str) - 6] = '\0';
}

void Draw(Tree* root) 
{
    char str[STR_SIZE];
    if (root->num == 0 || root == NULL)
    {
        gotoxy(30, 11);
        printf("当前没有树的数据，请先输入数据");
    }
    else
    {
        memset(str, '\0', STR_SIZE); 
        if (root->rnext)
        {
            Draw_level(root->rnext, false, str);
        }
        printf("%c\n", root->num);
        if (root->lnext)
        {
            Draw_level(root->lnext, true, str);
        }
    }
    
}
