#ifndef ALGRAPH_H
#define ALGRAPH_H
#include "base.h"
typedef struct ArcNode{
    int adjvex;   //�û���ָ��Ļ�ͷ�Ķ���λ��
    struct ArcNode *nextarc;    //�û�ָ�����һ������ָ��
    InfoType *info;  //�û������Ϣ��ָ��
}ArcNode;
typedef struct VNode{  //����������
    VertexType data;  //������Ϣ
    ArcNode *firstarc;   //ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vexs;  //�ڽӱ��ͷ�������
    int vexnum,arcnum;
    int kind;
}ALGraph;
int LocateVex_AL(ALGraph &G,VertexType vex);
Status CreateUDN_AL(ALGraph &G);
Status CreateDN_AL(ALGraph &G);
Status CreateUDG_AL(ALGraph &G);
Status CreateDG_AL(ALGraph &G);
Status CreateALGraph(ALGraph &G);
void DFSTraverse_AL(ALGraph G,Status(*Visit)(VertexType vex)); //�ڽӱ�ʽ��������ȱ���
void DFS_AL(ALGraph G,int vex,Status(*Visit)(VertexType vex)); //��ÿ��������ڽӵ���б����ĵݹ麯��
#endif // ALGRAPH_H
