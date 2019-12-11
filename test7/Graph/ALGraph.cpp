#include "ALGraph.h"
int visited_AL[MAX_VERTEX_NUM]={0};  //������ʱ�־����
void DFSTraverse_AL(ALGraph G,Status(*Visit)(VertexType vex))
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited_AL[i])
            DFS_AL(G,i,Visit);
    }
}
void DFS_AL(ALGraph G,int vex,Status(*Visit)(VertexType vex))
{
    int i=vex;
    ArcNode *temp=G.vexs[i].firstarc->nextarc;
    visited_AL[i]=1;
    Visit(G.vexs[i].data);
    while(temp!=NULL)
    {
        if(!visited_AL[temp->adjvex])
        {
            DFS_AL(G,temp->adjvex,Visit);
        }
        temp=temp->nextarc;
    }
}
int LocateVex_AL(ALGraph &G,VertexType vex)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i].data==vex)
            return i;
    }
    return 0;
}
Status CreateUDN_AL(ALGraph &G)  //����������
{
    int i,loc1,loc2,*weight;
    char vex1,vex2;
    ArcNode *ins=NULL;
    printf("�������ͼ�Ķ�������ͻ��ĸ�����");
    scanf("%d %d",&G.vexnum,&G.arcnum);
    getchar();
    printf("��������������㣺");
    for(i=0;i<G.vexnum;i++)  //����������ʼ��
    {
        scanf("%c",&G.vexs[i].data);
        G.vexs[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
        G.vexs[i].firstarc->nextarc=NULL;
    }
    getchar();
    printf("�������������Ӧ����������ֵ�͸û���Ӧ��Ȩֵ��");
    for(i=0;i<G.arcnum;i++)
    {
        weight=(int *)malloc(sizeof(int));
        scanf("%c %c %d",&vex1,&vex2,weight);
        getchar();
        loc1=LocateVex_AL(G,vex1);  //ֻ���㻡β����Ӧ�Ķ������
        loc2=LocateVex_AL(G,vex2);
        ins=(ArcNode*)malloc(sizeof(ArcNode));
        ins->adjvex=loc2;  //�满ͷ�Ķ�������
        ins->info=weight;  //��û�����Ӧ��Ȩֵ
        ins->nextarc=G.vexs[loc1].firstarc->nextarc;  //��ͷ�巨���½�����
        G.vexs[loc1].firstarc->nextarc=ins;
    }
    return OK;
}
Status CreateDN_AL(ALGraph &G)   //����������
{
    int i,*weight,loc1,loc2;
    char vex1,vex2;
    ArcNode *ins=NULL;
    printf("�������ͼ�Ķ�������ͻ��ĸ�����");
    scanf("%d %d",&G.vexnum,&G.arcnum);
    getchar();
    printf("��������������㣺");
    for(i=0;i<G.vexnum;i++)  //����������ʼ��
    {
        scanf("%c",&G.vexs[i].data);
        G.vexs[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
        G.vexs[i].firstarc->nextarc=NULL;
    }
    getchar();
    printf("�������������Ӧ����������ֵ�͸û�����Ӧ��Ȩֵ��");
    for(i=0;i<G.arcnum;i++)
    {
        weight=(int *)malloc(sizeof(int));
        scanf("%c %c %d",&vex1,&vex2,weight);
        getchar();
        loc1=LocateVex_AL(G,vex1);  //ֻ���㻡β����Ӧ�Ķ������
        loc2=LocateVex_AL(G,vex2);
        ins=(ArcNode*)malloc(sizeof(ArcNode));
        ins->adjvex=loc2;  //�满ͷ�Ķ�������
        ins->info=weight;  //��û�����Ӧ��Ȩֵ
        ins->nextarc=G.vexs[loc1].firstarc->nextarc;  //��ͷ�巨���½�����
        G.vexs[loc1].firstarc->nextarc=ins;
    }
    return OK;
}
Status CreateDG_AL(ALGraph &G)
{
    int i,loc1,loc2;
    char vex1,vex2;
    ArcNode *ins=NULL;
    printf("�������ͼ�Ķ�������ͻ��ĸ�����");
    scanf("%d %d",&G.vexnum,&G.arcnum);
    getchar();
    printf("��������������㣺");
    for(i=0;i<G.vexnum;i++)  //����������ʼ��
    {
        scanf("%c",&G.vexs[i].data);
        G.vexs[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
        G.vexs[i].firstarc->nextarc=NULL;
    }
    getchar();
    printf("�������������Ӧ����������ֵ��");
    for(i=0;i<G.arcnum;i++)
    {
        scanf("%c %c",&vex1,&vex2);
        getchar();
        loc1=LocateVex_AL(G,vex1);  //ֻ���㻡β����Ӧ�Ķ������
        loc2=LocateVex_AL(G,vex2);
        ins=(ArcNode*)malloc(sizeof(ArcNode));
        ins->adjvex=loc2;  //�满ͷ�Ķ�������
        ins->nextarc=G.vexs[loc1].firstarc->nextarc;  //��ͷ�巨���½�����
        G.vexs[loc1].firstarc->nextarc=ins;
    }
    return OK;
}
Status CreateUDG_AL(ALGraph &G)
{
    int i,loc1,loc2;
    char vex1,vex2;
    ArcNode *ins=NULL;
    printf("�������ͼ�Ķ�������ͱߵĸ�����");
    scanf("%d %d",&G.vexnum,&G.arcnum);
    getchar();
    printf("��������������㣺");
    for(i=0;i<G.vexnum;i++)  //����������ʼ��
    {
        scanf("%c",&G.vexs[i].data);
        G.vexs[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
        G.vexs[i].firstarc->nextarc=NULL;
    }
    getchar();
    printf("�������������Ӧ����������ֵ��");
    for(i=0;i<G.arcnum;i++)
    {
        scanf("%c %c",&vex1,&vex2);   //�������߾���������
        getchar();
        loc1=LocateVex_AL(G,vex1);
        loc2=LocateVex_AL(G,vex2);
        ins=(ArcNode*)malloc(sizeof(ArcNode));
        ins->adjvex=loc2;
        ins->nextarc=G.vexs[loc1].firstarc->nextarc;
        G.vexs[loc1].firstarc->nextarc=ins;
        ins=(ArcNode*)malloc(sizeof(ArcNode));
        ins->adjvex=loc1;
        ins->nextarc=G.vexs[loc2].firstarc->nextarc;
        G.vexs[loc2].firstarc->nextarc=ins;
    }
    return OK;
}
Status CreateALGraph(ALGraph &G)
{
    printf("������Ҫ������ͼ�����ͣ�0��1��2��3�ֱ��ʾ����ͼ����������ͼ����\n");
    scanf("%d",&G.kind);
    switch(G.kind)
    {
        case 0: CreateDG_AL(G);return OK;
        case 1: CreateDN_AL(G);return OK;
        case 2: CreateUDG_AL(G);return OK;
        case 3: CreateUDN_AL(G);return OK;
    }
    return OK;
}
