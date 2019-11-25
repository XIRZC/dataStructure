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
	QueuePtr front;  //队列头指针，不是首元指针，该内存区域不存放数据的 
	QueuePtr rear;   //队列尾指针 
}LinkQueue;
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q,QElemType add);
Status DeQueue(LinkQueue &Q,QElemType &del);
Status QueueEmpty(LinkQueue &Q);
#endif
