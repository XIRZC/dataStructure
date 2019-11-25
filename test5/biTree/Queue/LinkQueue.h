/* SqQueue.h */
#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include"../proj/base.h"
#include"../biTree/biTree.h"
#define MAXSIZE 100
typedef BiTNode* QElemType;
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr; 
typedef struct{
	QueuePtr front;  //����ͷָ�룬������Ԫָ�룬���ڴ����򲻴�����ݵ� 
	QueuePtr rear;   //����βָ�� 
}LinkQueue;
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q,QElemType add);
Status DeQueue(LinkQueue &Q,QElemType &del);
Status QueueEmpty(LinkQueue &Q);
#endif
