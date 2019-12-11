#ifndef MGRAPH_H
#define MGRAPH_H
#include "base.h"
typedef struct ArcCell{
    int adj;  //VRType�Ƕ����ϵ���ͣ���Ȩͼ��1 ����,0�������ڣ���Ȩͼ��Ȩֵ
    InfoType *info;  //�û������Ϣ��ָ��
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //Adjacency Matrix �ڽӾ���
typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];   //��������
    AdjMatrix arcs;    //�������ɵľ���
    int vexnum,arcnum;   //��������ͻ���ߵĸ���
    int kind;   //ͼ������
}MGraph;
Status CreateMGraph(MGraph &G);
Status CreateUDN_M(MGraph &G);
Status CreateUDG_M(MGraph &G);
Status CreateDN_M(MGraph &G);
Status CreateDG_M(MGraph &G);
int LocateVex(MGraph &G,VertexType vex);
void DFSTraverse(MGraph G,Status(*Visit)(VertexType vex));  //�ڽӾ����������ȱ���
void DFS(MGraph G,int vex,Status(*Visit)(VertexType vex));   //��ÿ��������ڽӵ���б����ĵݹ麯��
#endif // MGRAPH_H
