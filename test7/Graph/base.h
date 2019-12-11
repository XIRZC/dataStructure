#ifndef BASE_H
#define BASE_H
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>  //INT_MAX�����ڿ�
#include<string.h>
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define INFINITY 1000000
#define MAX_VERTEX_NUM 20
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10
typedef int Status;
typedef int InfoType;
typedef char VertexType;
typedef int SElemType;
typedef struct SqStack{
	SElemType *base;
	SElemType *top;
	int stackSize;
}SqStack;
typedef struct Edge{
    int lowcost;
    VertexType adjvex;
}Edge;  //����һ�����ߣ��±�Ϊһ����㣬adj��Ϊ��õ��ڽӵ�Ȩֵ��С���ڽӵ㣬lowcost��ӦȨֵ
Status VexOutput(VertexType vex);
Status InitStack(SqStack &S);  //ջ��غ���
Status Pop(SqStack &S,SElemType &del);
Status Push(SqStack &S,SElemType add);
Status StackEmpty(SqStack &S);
#endif
