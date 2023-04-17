#pragma once
#ifndef __DRAW_H_
#define __DRAW_H_
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "Queue.h"
#pragma warning(disable:4996)
void Draw_level(Tree* node, bool left, char* str);
void Draw(Tree* root);

#endif // !__DRAW_H_
