#include "base.h"
#include "MGraph.h"
#include "ALGraph.h"
void MiniSpanTree_PRIM(MGraph G,VertexType vex);  //����prim�㷨ȥ��һ��ͼ����С������(MST)
int minEdge(Edge *closedge,MGraph G);
Status TopologicalSort(ALGraph G);
void FindInDegree(int *indegree,ALGraph G);
Status TopologicalOrder(ALGraph G,SqStack &T,int *ves);
Status CriticalPath(ALGraph &G);
void ShortestPath_DIJ(MGraph &G,VertexType vex0,int P[][MAX_VERTEX_NUM],int D[]);
/*�������룺
8 9
ABCDEFGH
ͼ���룺AB AC BD BE DH EH CF CG FG
�����룺AB 1 AC 2 BD 1 BE 3 DH 3 EH 2 CF 1 CG 2 FG 3
����� �ڽӾ���洢��������ȱ�����ABDHECFG
�ڽӱ�洢��������ȱ���(ͷ�巨��������ıߺ�����ڽӵ㣩��ACGFBEHD

��С���������룺 ����������
6 10
ABCDEF
AB 6 AC 1 AD 5 BC 5 CD 5 BE 3 CE 6 CF 4 EF 6 DF 2
�����AC CF FD CB BE,�Ӳ�ͬ��ʼ��ó�����С����������ͬ��

�����������룺  �������޻�ͼ��
6 8
ABCDEF
AB AC AD CD EB EF BF CF
�����E A B C D F
�л�ͼ�� AB AC DA CD EB EF BF CF

�ؼ�·�����룺  �������޻�����
6 8
ABCDEF
AB 3 AC 2 BD 2 BE 3 CD 4 CF 3 DF 2 EF 1
������ؼ�·����A->C->D->F

9 11
123456789
12 6 13 4 14 5 25 1 35 1 46 2 57 9 58 7 68 4 79 2 89 4
������ؼ���� 12 25 57 58 79 89

���·�����룺  ����������
6 8
012345
05 100 04 30 02 10 12 5 23 50 43 20 35 10 45 60
�����0 1000000 10  50  30  60
*/
int main(void)
{
    int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM]={0},D[MAX_VERTEX_NUM]={0},i;
    MGraph MG;
    CreateMGraph(MG);
    //ALGraph ALG;
    //CreateALGraph(ALG);
    // �ڽӾ���������ȱ���
    //DFSTraverse(MG,VexOutput);
    // �ڽӱ�������ȱ���
    //DFSTraverse_AL(ALG,VexOutput);
    //�ڽӾ�����ʵ����С����������,����ͼΪ������
    //MiniSpanTree_PRIM(MG,MG.vexs[1]);
    //�ڽӱ���ʵ����������
    //if(!TopologicalSort(ALG))
    //    printf("������ͼ��Ϊ�޻�ͼ");
    //if(!CriticalPath(ALG))
    //    printf("������ͼ��Ϊ�޻�ͼ\n");
    //���·��
    ShortestPath_DIJ(MG,MG.vexs[0],P,D);
    for(i=0;i<MG.vexnum;i++)
    {
        printf("%d\t",D[i]);
    }
    return 0;
}
void ShortestPath_DIJ(MGraph &G,VertexType vex0,int P[][MAX_VERTEX_NUM],int D[])
{
    int final[MAX_VERTEX_NUM]={0};
    int i,j,v,min;
    int v0=LocateVex(G,vex0);
    for(v=0;v<G.vexnum;v++)
    {
        D[v]=G.arcs[v0][v].adj;
        if(D[v]<INFINITY)
        {
            P[v][v0]=1;
            P[v][v]=1;
        }
    }
    D[v0]=0;
    final[v0]=1;  //v0��������S����
    for(i=1;i<G.vexnum;i++)
    {
        min=INFINITY;
        for(j=0;j<G.vexnum;j++)
        {
            if(!final[j])
            {
                if(D[j]<min)
                {
                    min=D[j];
                    v=j;
                }
            }
        }
        final[v]=1;
        for(j=0;j<G.vexnum;j++)
        {
            if(!final[j]&&(D[j]>G.arcs[v][j].adj+min))
            {
                D[j]=G.arcs[v][j].adj+min;
                P[j][j]=1;
            }
        }
    }
}
Status CriticalPath(ALGraph &G)
{
    int ve[MAX_VERTEX_NUM]={0},vl[MAX_VERTEX_NUM]={0},i,k;
    char tag[30];
    ArcNode *temp;
    SqStack T;
    if(!TopologicalOrder(G,T,ve))
        return ERROR;
    vl[G.vexnum-1]=ve[G.vexnum-1];  //�������������д�n-1��ʼ����
    while(!StackEmpty(T))
    {
        Pop(T,i);
        for(temp=G.vexs[i].firstarc->nextarc;temp;temp=temp->nextarc)
        {
            if(!temp)  break;
            if(vl[i]==0)  vl[i]=vl[temp->adjvex]-*(temp->info);  //��֤vl[i]��ֵ��vl[temp->adjvex]-*(temp->info)����Сֵ
            if(vl[temp->adjvex]-*(temp->info)<vl[i])
                vl[i]=vl[temp->adjvex]-*(temp->info);
        }
    }
    for(i=0;i<G.vexnum;i++)
    {
        for(temp=G.vexs[i].firstarc->nextarc;temp;temp=temp->nextarc)
        {
            if(!temp)  break;
            k=temp->adjvex;
            if(ve[i]==vl[k]-*(temp->info))
            {
                strcpy(tag,"�ûΪ�ؼ��");
            }
            else
                strcpy(tag,"  ");
            printf("�%c->%c ��ʱ%d ����ʱ��%d ����ʱ��%d %s\n",G.vexs[i].data,G.vexs[k].data,*(temp->info),ve[i],vl[k]-*(temp->info),tag);
        }
    }
    return OK;
}
Status TopologicalOrder(ALGraph G,SqStack &T,int *ve)
{
    int indegree[MAX_VERTEX_NUM]={0},i,count=0;
    ArcNode *temp;
    SqStack S;
    InitStack(S);
    InitStack(T);
    FindInDegree(indegree,G);
    for(i=0;i<G.vexnum;i++)
    {
        if(!indegree[i])
            Push(S,i);
    }
    while(!StackEmpty(S))
    {
        Pop(S,i);
        Push(T,i);
        count++;
        for(temp=G.vexs[i].firstarc->nextarc;temp;temp=temp->nextarc)
        {
            if(!temp)  break;
            if(!--indegree[temp->adjvex])
            {
                Push(S,temp->adjvex);
            }
            if(ve[i]+*(temp->info)>ve[temp->adjvex])
                ve[temp->adjvex]=ve[i]+*(temp->info);
        }
    }
    if(count<G.vexnum)
        return ERROR;
    else
        return OK;
}
Status TopologicalSort(ALGraph G)
{
    int indegree[MAX_VERTEX_NUM]={0},i,count=0;
    ArcNode *temp;
    SqStack S;
    InitStack(S);
    FindInDegree(indegree,G);
    for(i=0;i<G.vexnum;i++)
    {
        if(!indegree[i])
            Push(S,i);
    }
    while(!StackEmpty(S))
    {
        Pop(S,i);
        printf("%c  ",G.vexs[i].data);
        count++;
        for(temp=G.vexs[i].firstarc->nextarc;temp;temp=temp->nextarc)
        {
            if(!temp)  break;
            if(!--indegree[temp->adjvex])
            {
                Push(S,temp->adjvex);
            }
        }
    }
    if(count<G.vexnum)
        return ERROR;
    else
        return OK;
}
void FindInDegree(int *indegree,ALGraph G)
{
    int i;
    ArcNode *temp;
    for(i=0;i<G.vexnum;i++)
    {
        for(temp=G.vexs[i].firstarc->nextarc;temp;temp=temp->nextarc)
        {
            if(!temp)  break;
            indegree[temp->adjvex]++;
        }
    }
}
void MiniSpanTree_PRIM(MGraph G,VertexType vex)
{
    int k,i,j,fix;
    Edge closedge[MAX_VERTEX_NUM];
    fix=k=LocateVex(G,vex);
    for(i=0;i<G.vexnum;i++)  //���������ʼ��
    {
        if(i!=k)
        {
            closedge[i].adjvex=vex;   //������U�����еĶ���ֵ
            closedge[i].lowcost=G.arcs[k][i].adj;
        }
    }
    closedge[k].lowcost=0;
    closedge[k].adjvex=vex;
    for(i=0;i<G.vexnum;i++)  //��ʼ���������k�����������Ȩֵ��С�ı߲���ʼ���뼯��U��
    {
        if(i!=fix)
        {
            k=minEdge(closedge,G);   //�ҵ���k�����������Ȩֵ��С�ı�����Ӧ���ڽӵ����
            printf("%c %c\n",closedge[k].adjvex,G.vexs[k]);
            closedge[k].lowcost=0;   //���뼯��U��
            for(j=0;j<G.vexnum;j++)  //����closedge��ֵ,��U��V-U�е����Ӧ��V-U�еĶ�����СȨֵ��ż���ܸı�
            {
                if(G.arcs[k][j].adj<closedge[j].lowcost)
                {
                    closedge[j].lowcost=G.arcs[k][j].adj;
                    closedge[j].adjvex=G.vexs[k];
                }
            }
        }
    }
}
int minEdge(Edge *closedge,MGraph G)
{
    int i,minVex;
    for(i=0;i<G.vexnum;i++)
    {
        if(closedge[i].lowcost!=0)  //��һ������������lowcost��Ϊ0��minVexֵ
        {
            minVex=i;
            break;
        }
    }
    for(i=minVex+1;i<G.vexnum;i++)
    {
        if(minVex!=i&&closedge[i].lowcost!=0&&closedge[minVex].lowcost>closedge[i].lowcost)
            minVex=i;
    }
    return minVex;
}
Status VexOutput(VertexType vex)
{
    printf("%c",vex);
    return OK;
}
Status InitStack(SqStack &S)
{
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)  exit(ERROR);
	S.stackSize=STACK_INIT_SIZE;
	S.top=S.base;
	return OK;
}
Status Pop(SqStack &S,SElemType &del)
{
	if(S.top==S.base)  exit(ERROR);
	del=*--S.top;
	return OK;
}
Status Push(SqStack &S,SElemType add)
{
	if(S.top-S.base>=S.stackSize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stackSize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)  exit(OVERFLOW);
		S.stackSize+=STACKINCREMENT;
		S.top=S.base+STACKINCREMENT;
	}
	*S.top++=add;
	return OK;
}
Status StackEmpty(SqStack &S)
{
	return S.top==S.base;
}
