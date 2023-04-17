#pragma once
#ifndef __QUEUE_H_
#define	__QUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
constexpr auto MAX_SIZE = 128;
constexpr auto STR_SIZE = 1024;
 typedef struct Queue
 {
	 int		front;
	 int     rear;
	 Tree* data[MAX_SIZE];
 }SqQueue;

void Init_Queue(SqQueue** q);
bool EmptyQueue(SqQueue* q);
bool OutQueue(SqQueue* q, Tree** node);
bool EnterQueue(SqQueue* q, Tree* node);

#endif 



