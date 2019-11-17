/* SqStack.cpp */
#ifndef SQSTACK_H
#define SQSTACK_H
#include"../proj/base.h"
#include"../biTree/biTree.h"
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10 
typedef BiTNode* SElemType;
typedef struct SqStack{
	SElemType *base;
	SElemType *top;
	int stackSize;
}SqStack; 
Status InitStack(SqStack &S);
Status Pop(SqStack &S,SElemType &del);
Status Push(SqStack &S,SElemType add);
Status StackEmpty(SqStack &S);
Status GetTop(SqStack &S,SElemType &top); 
int StackLength(SqStack &S);
#endif
