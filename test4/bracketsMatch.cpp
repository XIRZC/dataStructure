/* SqStack.cpp  ���һ�����ʽ�ַ����������Ƿ�ƥ�������a+b&b+a@�ļ��� */
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
	printf("1.����ƥ����   2.�ַ�����ϳɼ�� \n");
	scanf("%d",&order);
	getchar();   //��ȡ���з� 
	if(order==1)
		while(gets(str)&&str[0]!='q')
		{
			if(bracketsMatch(str))
				printf("����ƥ��\n");
			else
				printf("���Ų�ƥ��\n");
		}
	else
	{
		while(1)
		{
			if(reverseReco())  
				printf("���ַ�����������\n");
			else 
				printf("���ַ�������������\n");
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
			if(abs(str[i]-del)>2)  //��ƥ�䣬 ͨ��ASCII�뿴������������ƥ�䣬�����ַ����ֵ�ľ���ֵΪ2���� 
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
	int flag=0;   //��һ��������&ǰ������ȡ�����ַ� 
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
					getchar();  //��ȡ���з� 
					return 0;
				}
			}
		}
		else flag=1;  //������ȡ����&���ţ��˺�ʼ��ջ 
	}
	getchar();  //��ȡ���з�
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
