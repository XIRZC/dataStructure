/* DNF_CNF.cpp-- 利用真值表法求出某几个变元合成公式的主合取范式和主析取范式 */
//include和宏定义 
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
//全局变量声明 
int valueList[100][50];   //用来存不同变元取值下的公式值 
//typedef 
typedef int Status;
typedef char ElemType;
typedef struct SqStack{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack;
//函数声明 
Status InitStack(SqStack &S);
Status StackLength(SqStack &S);
Status Push(SqStack &S,ElemType add);
Status Pop(SqStack &S,ElemType &del);
ElemType GetTop(SqStack &S);
int main(void)
{
	
}
Status InitStack(SqStack &S)
{
	S.base=(ElemType*)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
	if(!S.base)  exit(OVERFLOW);
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
	if(S.top-S.base>=S.stackSize)
	{
		if(!(S.base=(ElemType*)realloc(S.base,sizeof(ElemType)*(S.stackSize+STACKINCREMENT))))
			exit(OVERFLOW);
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
