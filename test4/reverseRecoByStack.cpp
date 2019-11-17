/* reverseRecoByStack.cpp 识别一个以@结束的字符串是否为：str1&str2,且str2和str1逆序，利用栈实现 */
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
typedef char ElemType;
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
Status reverseReco(void);
Status StackEmpty(SqStack &S); 
int main(void)
{
	while(1)
	{
		if(reverseReco())  printf("该字符串符合题意\n");
		else printf("该字符串不符合题意\n");
	}
	return 0;
}
Status reverseReco(void)
{
	char ch;
	int flag=0;   //设一标记来标记&前后所读取到的字符 
	ElemType del;
	SqStack S;
	InitStack(S);
	while((ch=getchar())!='@')
	{
		if(ch!='&')
		{
			if(flag==0)
				Push(S,ch);
			else
			{
				Pop(S,del);
				if(del!=ch) return 0;
			}
		}
		else flag=1;  //表明读取到了&符号，此后开始出栈 
	}
	if(!StackEmpty(S))  return 0;
	return 1;
}
Status StackEmpty(SqStack &S)
{
	return S.top==S.base;
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
