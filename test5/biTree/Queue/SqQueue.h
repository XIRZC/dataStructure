/* SqQueue.h */
#ifndef SQQUEUE_H
#define SQQUEUE_H
#include"../proj/base.h"
#include"../biTree/biTree.h"
#define MAXSIZE 100
typedef BiTNode* QElemType;
typedef struct{
	QElemType *base;   //队列基地址 
	int front;  //队列头索引 
	int rear;  //队列尾索引的后一个内存位置 
}SqQueue;
Status InitQueue(SqQueue &Q);
Status EnQueue(SqQueue &Q,QElemType add);
Status DeQueue(SqQueue &Q,QElemType &del);
int QueueLength(SqQueue &Q);
Status QueueEmpty(SqQueue &Q);
QElemType GetHead(SqQueue &Q); 
#endif
