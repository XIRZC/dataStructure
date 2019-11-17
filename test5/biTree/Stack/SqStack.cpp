/* SqStack.cpp */
#include"SqStack.h"
Status InitStack(SqStack &S)
{
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)  exit(ERROR);
	S.stackSize=STACK_INIT_SIZE;
	S.top=S.base;
	return OK;
}
Status Pop(SqStack &S,SElemType &del)
{
	if(S.top==S.base)  exit(ERROR);
	del=*--S.top;
	return OK;
}
Status Push(SqStack &S,SElemType add)
{
	if(S.top-S.base>=S.stackSize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stackSize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)  exit(OVERFLOW);
		S.stackSize+=STACKINCREMENT;
		S.top=S.base+STACKINCREMENT;
	}
	*S.top++=add;
	return OK;
}
Status StackEmpty(SqStack &S)
{
	return S.top==S.base;
}
Status GetTop(SqStack &S,SElemType &top)
{
	top=*(S.top-1);
	return OK;
}
int StackLength(SqStack &S)
{
	return S.top-S.base;
}

