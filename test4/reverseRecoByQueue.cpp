/* reverseRecoByStack.cpp ʶ��һ����@�������ַ����Ƿ�Ϊ��str1&str2,��str2��str1�������ö���ʵ�� */
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef char ElemType;
typedef int Status;
typedef struct{
	ElemType *base;   //���л���ַ 
	int front;  //����ͷ���� 
	int rear;  //����β�����ĺ�һ���ڴ�λ�� 
}SqQueue;
Status InitQueue(SqQueue &Q);
Status EnQueue(SqQueue &Q,ElemType add);
Status DeQueue(SqQueue &Q,ElemType &del);
int QueueLength(SqQueue &Q);
ElemType GetHead(SqQueue &Q); 
ElemType GetTail(SqQueue &Q);
Status reverseReco(void); 
int main(void)
{
	if(reverseReco())  printf("���ַ�����������\n");
	else printf("���ַ�������������\n");
	return 0;
}
Status reverseReco(void)
{
	int len;
	char ch;
	SqQueue Q;
	InitQueue(Q);
	while((ch=getchar())!='@')
	{
		if(ch=='&')  continue;
		EnQueue(Q,ch);
	}
	len=QueueLength(Q);
	while(len--)
	{
		if(GetHead(Q)!=GetTail(Q))  
		{
			DestroyQueue(Q);
			return FALSE;
		}
		Q.front=(Q.front+1)%MAXSIZE;
		Q.rear=(Q.rear+MAXSIZE-1)%MAXSIZE;
	}
	return TRUE;
}
Status InitQueue(SqQueue &Q)
{
	Q.base=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
	if(!Q.base)  return ERROR;
	Q.front=Q.rear=0;
	return OK;
}
Status EnQueue(SqQueue &Q,ElemType add)
{
	if((Q.rear+1)%MAXSIZE==Q.front)  return OVERFLOW;
	Q.base[Q.rear]=add;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}
Status DeQueue(SqQueue &Q,ElemType &del)
{
	if(Q.front==Q.rear)  return ERROR;
	del=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
} 
int QueueLength(SqQueue &Q)
{
	return (Q.rear-Q.front+MAXSIZE) % MAXSIZE;
}
ElemType GetHead(SqQueue &Q)
{
	return Q.base[Q.front];
}
ElemType GetTail(SqQueue &Q)
{
	return Q.base[Q.rear-1];
} 
