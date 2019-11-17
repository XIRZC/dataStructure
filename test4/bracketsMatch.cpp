/* SqStack.cpp  检测一个表达式字符串中括号是否匹配和逆序a+b&b+a@的检验 */
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
Status bracketsMatch(char *str);
Status reverseReco(void); 
int main(void)
{
	char str[30];
	int len,i,order,result;
	printf("1.括号匹配检测   2.字符逆序合成检测 \n");
	scanf("%d",&order);
	getchar();   //读取换行符 
	if(order==1)
		while(gets(str)&&str[0]!='q')
		{
			if(bracketsMatch(str))
				printf("括号匹配\n");
			else
				printf("括号不匹配\n");
		}
	else
	{
		while(1)
		{
			if(reverseReco())  
				printf("该字符串符合题意\n");
			else 
				printf("该字符串不符合题意\n");
		}
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
			if(abs(str[i]-del)>2)  //不匹配， 通过ASCII码看出若左右括号匹配，则两字符相差值的绝对值为2以内 
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
				if(del!=ch) 
				{
					getchar();  //读取换行符 
					return 0;
				}
			}
		}
		else flag=1;  //表明读取到了&符号，此后开始出栈 
	}
	getchar();  //读取换行符
	if(!StackEmpty(S))  return 0;
	return 1;
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
