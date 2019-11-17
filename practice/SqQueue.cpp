/* SqQueue.cpp -- 循环顺序队列的练习 */ 
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;
typedef struct{
	ElemType *base;   //队列基地址 
	int front;  //队列头索引 
	int rear;  //队列尾索引的后一个内存位置 
}SqQueue;
Status InitQueue(SqQueue &Q);
Status EnQueue(SqQueue &Q,ElemType add);
Status DeQueue(SqQueue &Q,ElemType &del);
int QueueLength(SqQueue &Q);
ElmeType GetHead(SqQueue &Q); 
int main(void)
{
	return 0;
}
Status InitQueue(SqQueue &Q)
{
	Q.base=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
	if(!S.base)  return ERROR;
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
