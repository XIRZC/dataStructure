/* SqQueue.h */
#ifndef SQQUEUE_H
#define SQQUEUE_H
#include"../proj/base.h"
#include"../biTree/biTree.h"
#define MAXSIZE 100
typedef BiTNode* QElemType;
typedef struct{
	QElemType *base;   //���л���ַ 
	int front;  //����ͷ���� 
	int rear;  //����β�����ĺ�һ���ڴ�λ�� 
}SqQueue;
Status InitQueue(SqQueue &Q);
Status EnQueue(SqQueue &Q,QElemType add);
Status DeQueue(SqQueue &Q,QElemType &del);
int QueueLength(SqQueue &Q);
Status QueueEmpty(SqQueue &Q);
QElemType GetHead(SqQueue &Q); 
#endif
