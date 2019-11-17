/* LinkQueue.cpp -- �����е���ϰ */
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;
typedef struct{
	ElemType data;
	QNode *next;
}QNode,QueuePtr; 
typedef struct{
	QueuePtr front;  //����ͷָ�룬������Ԫָ�룬���ڴ����򲻴�����ݵ� 
	QueuePtr rear;   //����βָ�� 
}LinkQueue;
Status InitQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
int QueueLength(LinkQueue &Q);
ElemType GetHead(LinkQueue &Q);
Status EnQueue(LinkQueue &Q,ElemType add);
Status DeQueue(LinkQueue &Q,ElemType &del);
Status DestroyQueue(LinkQueue &Q); 
int main(void)
{
	return 0;
}
Status InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)  return ERROR;
	Q.front->next=NULL;
	return OK;
}
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr temp1=Q.front->next,temp2;
	while(temp1!=NULL)
	{
		temp2=temp1->next;
		free((void*)temp1);
		temp1=temp2;
	}
	return OK;
} 
Status DestroyQueue(LinkQueue &Q)
{
	while(Q.front!=NULL)
	{
		Q.rear=Q.front->next;
		free((void*)Q.front);
		Q.front=Q.rear;
	}
	return OK;
}
Status EnQueue(LinkQueue &Q,ElemType add)
{	
	QueuePtr ins;
	ins=(QueuePtr)malloc(sizeof(QNode));
	if(!ins)  return ERROR;
	Q.rear->next=ins;
	Q.rear=ins;  //ע����¶���βָ���ֵ 
	ins->data=add;
	ins->next=NULL;
	return OK;
}
Status DeQueue(LinkQueue &Q,ElemType &del)
{
	QueuePtr temp=Q.front->next;
	if(Q.front==Q.rear)   return ERROR;
	del=temp->data;
	temp=temp->next;
	if(temp=Q.rear) Q.rear=Q.front;  //��ֻ����Ԫ��㻹Ҫ��ɾ��ʱ��Ϊ��ʱ��ָ�븳ֵΪ��� 
	free((void*)Q.front->next);
	Q.front->next=temp;
	return OK;
}
ElemType GetHead(LinkQueue &Q)
{
	return Q.front->next->data;
}
