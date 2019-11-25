/* LinkQueue.cpp -- �����е���ϰ */
#include"LinkQueue.h"
Status QueueEmpty(LinkQueue &Q)
{
	return Q.front==Q.rear;
}
Status InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)  return ERROR;
	Q.front->next=NULL;
	return OK;
}
Status EnQueue(LinkQueue &Q,QElemType add)
{	
	QueuePtr ins;
	ins=(QueuePtr)malloc(sizeof(QNode));
	if(!ins)  return ERROR;
	ins->data=add;
	ins->next=NULL;
	Q.rear->next=ins;
	Q.rear=ins;  //ע����¶���βָ���ֵ 
	return OK;
}
Status DeQueue(LinkQueue &Q,QElemType &del)
{
	QueuePtr temp=Q.front->next;
	if(Q.front==Q.rear)   return ERROR;
	del=temp->data;
	Q.front->next=temp->next;
	if(temp==Q.rear) Q.rear=Q.front;  //��ֻ����Ԫ��㻹Ҫ��ɾ��ʱ��Ϊ��ʱ��ָ�븳ֵΪ��� 
	free((void*)temp);
	return OK;
}
