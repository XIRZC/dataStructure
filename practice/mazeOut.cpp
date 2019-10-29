/**/
#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef struct{
	int x;
	int y;
}PosType;
typedef struct{
	int order;  //通道块在路径上的序号
	PosType seat;  //通道块在迷宫中的"坐标位置"
	int direct;  //从此通道块走向下一通道块的"方向" 
}ElemType;
typedef int Status;
typedef struct SqStack{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack;
Status InitStack(SqStack &S);
int StackLength(SqStack &S);
Status Push(SqStack &S,ElemType add);
Status Pop(SqStack &S,ElemType &del);
ElemType GetTop(SqStack &S);
Status ClearStack(SqStack &S);
void ElemOutput(ElemType &elem);
void DestroyStack(SqStack &S);
int main(void)
{
	
	return 0;
}
Status InitStack(SqStack &S)
{
	S.base=(ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
	if(!S.base)  return ERROR;
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
	return OK;
}
Status StackLength(SqStack &S)
{
	return S.top-S.base;
}
Status Push(SqStack &S,ElemType add)
{
	if(StackLength(S)>=S.stackSize)
	{
		S.base=(ElemType *)realloc(S.base,sizeof(ElemType)*(S.stackSize+STACKINCREMENT));
		if(!S.base)  return OVERFLOW;
		S.top=S.base+S.stackSize;
		S.stackSize+=STACKINCREMENT;
	}
	*(S.top++)=add;
	return OK;
}
Status Pop(SqStack &S,ElemType &del)
{
	if(StackLength(S)==0)  return ERROR;
	del=*(--S.top);
	return OK;
}
ElemType GetTop(SqStack &S)
{
	return *(S.top-1);
}
Status ClearStack(SqStack &S)
{
	ElemType del;
	int i,len=StackLength(S);
	for(i=0;i<len;i++)
		Pop(S,del);
	return OK;
}
