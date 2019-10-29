/* bracketsMatch.cpp  检测一个表达式字符串中括号是否匹配 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef char ElemType;
typedef int Status;
typedef struct SqStack{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack; 
Status InitStack(SqStack &S);
Status Pop(SqStack &S,ElemType &del);
Status Push(SqStack &S,ElemType add);
Status StackEmpty(SqStack &S);
ElemType GetTop(SqStack &S); 
Status DestroyStack(SqStack &S);
Status bracketsMatch(char *str);
int main(void)
{
	char str[30];
	int len,i;
	while(gets(str)&&str[0]!='q')
	{
		if(bracketsMatch(str))
			printf("括号匹配\n");
		else
			printf("括号不匹配\n");
	}
	return 0;
}
Status bracketsMatch(char *str)
{
	int i,len;
	SqStack S;
	ElemType del;
	InitStack(S);
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]=='('||str[i]=='['||str[i]=='{')
			Push(S,str[i]);
		else if(str[i]==')'||str[i]==']'||str[i]=='}')
		{
			Pop(S,del);
			if(abs(str[i]-del)>2)  //不匹配， 通过ASCAII码看出若左右括号匹配，则两字符相差值的绝对值为2以内 
			{
				Push(S,del);
				return FALSE;
			}	 
		}
	}
	if(!StackEmpty(S))
		return FALSE;
	else
		return TRUE;
}
Status InitStack(SqStack &S)
{
	S.base=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base)  exit(ERROR);
	S.stackSize=STACK_INIT_SIZE;
	S.top=S.base;
	return OK;
}
Status Pop(SqStack &S,ElemType &del)
{
	if(S.top==S.base)  exit(ERROR);
	del=*--S.top;
	return OK;
}
Status Push(SqStack &S,ElemType add)
{
	if(S.top-S.base>=S.stackSize)
	{
		S.base=(ElemType *)realloc(S.base,(S.stackSize+STACKINCREMENT)*sizeof(ElemType));
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
ElemType GetTop(SqStack &S)
{
	return *(S.top);
}
Status DestroyStack(SqStack &S)
{
	int len=S.stackSize,i;
	for(i=0;i<len;i++)
	{
		free((void *)S.base++);
	}
	return OK;
}
