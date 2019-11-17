/* SqQueue.cpp */
#include"SqQueue.h"
Status InitQueue(SqQueue &Q)
{
	Q.base=(QElemType *)malloc(sizeof(QElemType)*MAXSIZE);
	if(!Q.base)  return ERROR;
	Q.front=Q.rear=0;
	return OK;
}
Status EnQueue(SqQueue &Q,QElemType add)
{
	if((Q.rear+1)%MAXSIZE==Q.front)  return OVERFLOW;
	Q.base[Q.rear]=add;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}
Status DeQueue(SqQueue &Q,QElemType &del)
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
QElemType GetHead(SqQueue &Q)
{
	return Q.base[Q.front];
}
Status QueueEmpty(SqQueue &Q)
{
	return Q.front==Q.rear;
} 
