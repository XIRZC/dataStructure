/* conversion.cpp-- 数制转换 */
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
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack;
Status InitStack(SqStack &S);
ElemType GetTop(SqStack &S);
Status Push(SqStack &S,ElemType add);
Status Pop(SqStack &S,ElemType &del); 
Status StackLength(SqStack &S);
Status conversion(int num,int bit); 
int main(void)
{
	int num,bit;
	while(scanf("%d",&num)&&num)
	{
		printf("进制输入：");
		scanf("%d",&bit);
		conversion(num,bit);
	}
	return 0;
}
Status conversion(int num,int bit)
{
	int len,i;
	SqStack S;
	ElemType del;
	InitStack(S);
	while(num!=0)
	{
		Push(S,num%bit);
		num/=bit;
	}
	len=StackLength(S);
	for(i=0;i<len;i++)
	{
		Pop(S,del);
		printf("%d",del);
	}
	printf("\n");
}
Status InitStack(SqStack &S)
{
	S.base=(ElemType *)malloc(sizeof(ElemType)*(STACK_INIT_SIZE));
	if(!S.base)  return ERROR;
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
	return OK;
}
ElemType GetTop(SqStack &S)
{
	return *S.top;
}
Status Push(SqStack &S,ElemType add)
{
	if(S.top-S.base>=S.stackSize)  
	{
		S.base=(ElemType*)realloc(S.base,sizeof(ElemType)*(S.stackSize+STACKINCREMENT));
		if(!S.base)  return OVERFLOW;
		S.top=S.base+S.stackSize;
		S.stackSize+=STACKINCREMENT;
	}
	*(S.top++)=add;
	return OK;
}
Status Pop(SqStack &S,ElemType &del)
{
	if(S.top-S.base==0)  return ERROR;
	del=*(--S.top);
	return OK; 
}
Status StackLength(SqStack &S)
{
	return S.top-S.base;
}
