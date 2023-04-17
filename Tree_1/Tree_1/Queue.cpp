#include "Queue.h"


void Init_Queue(SqQueue** q)
{
    *q = (SqQueue*)malloc(sizeof(SqQueue));
    if (*q == NULL)
    {
        printf("ÄÚ´æ·ÖÅäÊ§°Ü£¡");
        exit(-1);
    }
    (*q)->front = (*q)->rear = -1;
}

bool EmptyQueue(SqQueue* q)
{
    if (q->front == q->rear)
    {
        return true;
    }
    return false;
}

bool EnterQueue(SqQueue* q, Tree* h)
{
    if (q->rear == MAX_SIZE - 1)
    {
        return false;
    }
    q->rear++;
    q->data[q->rear] = h;
    return true;
}

bool OutQueue(SqQueue* q, Tree** h)
{
    if (q->front == q->rear)
    {
        return false;
    }
    q->front++;
    *h = q->data[q->front];
    return true;
}

