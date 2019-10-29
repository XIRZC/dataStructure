/* LinkList.cpp-- ������Ļ������� */
#include<stdio.h>
#include<stdlib.h> 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status; 
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	LNode *next;
}LNode,*LinkList;
//���������������� 
int LocateElem(LinkList &L,ElemType loc);
Status GetElem(LinkList &L,int num,ElemType &get);
int ElemInput(ElemType &input);
void ElemOutput(ElemType &output);
Status InitList(LinkList &L);
Status ClearList(LinkList &L);
Status GetList(LinkList &L);
int ListLength(LinkList &L);
Status ListInsert(LinkList &L,int num,ElemType add);  //�ڵ�num��Ԫ��֮ǰ�����Ԫ�� 
Status ListDelete(LinkList &L,int num,ElemType& del);
//���ڻ��������ĺϳɲ�����������
Status ListCreate(LinkList &L); 
Status ListCreate_reverse(LinkList &L); 
Status ListScreen(LinkList &L,ElemType minKey,ElemType maxKey); 
Status ListReverse(LinkList &L);


int main(void)
{
	int maxKey,minKey;
	ElemType del,add;
	LinkList L;
	InitList(L);
	ListCreate(L);   //�������˳�򴴽� 
	getchar();  //��ȡ�������ڵ�q�ַ� 
	scanf("%d %d",&minKey,&maxKey);   //������ĸ���Ԫ�ش�С��ɸѡ 
	ListScreen(L,minKey,maxKey);
	GetList(L);
	
	ListReverse(L);  //�������ԭ������ 
	GetList(L);
	
	ClearList(L);   //����������򴴽� 
	ListCreate_reverse(L);
	GetList(L);
	
	if(!ListInsert(L,5,999))     //ɾ�������뵥�ڵ� 
		printf("����%d��Ԫ�أ������ڵ�%d��λ�ü���������!!\n",ListLength(L),ListLength(L)+2);
	GetList(L);   //������������� 
	if(!ListDelete(L,5,del))   
		printf("����%d��Ԫ�أ������ڵ�%d��λ���ϼ������ɾ��!!\n",ListLength(L),ListLength(L)+1);
	GetList(L);   
	return 0;
}
Status ListCreate_reverse(LinkList &L)  //����������򴴽� 
{
	LNode *add;
	ElemType ins;
	printf("�������򴴽�������\n");
	L=(LNode*)malloc(sizeof(LNode));
	L->next=NULL;
	while(ElemInput(ins))
	{
		add=(LNode *)malloc(sizeof(LNode));
		add->data=ins;
		add->next=L->next;
		L->next=add;
	}
	return OK;
}
Status ListReverse(LinkList &L)  //�����ԭ������ 
{
	LNode *front=L->next,*rear;
	if(!front||!front->next)  return ERROR;
	rear=front->next;
	front->next=NULL;  //����β����ΪNULL 
	while(rear)
	{
		front=rear;
		rear=rear->next;
		front->next=L->next;
		L->next=front;
	}
	return OK;
}
Status GetList(LinkList &L)
{
	LNode *temp=L;
	while(temp->next!=NULL)
	{
		temp=temp->next;
		ElemOutput(temp->data);
	}
	printf("\n");
	return OK;
}
Status ListScreen(LinkList &L,ElemType minKey,ElemType maxKey)
{
	LNode *temp=L,*tempMin,*tempMax,*k;
	ElemType del;
	int i=0,min=LocateElem(L,minKey),max=LocateElem(L,maxKey);
	while(temp->next!=NULL)  
	{
		i++;
		temp=temp->next;
		if(i==max&&temp->data>maxKey)
			max--;
	}
	if(maxKey>temp->data)  max--;
	temp=L,i=0;
	while(temp->next!=NULL)
	{
		if(i==min-1) { tempMin=temp;break; }
		temp=temp->next;
		i++;
	} 
	i=0;temp=L;
	while(temp->next!=NULL)
	{
		temp=temp->next;
		i++;
		if(i==max)  { tempMax=temp;break; }
	}
	k=tempMin->next;
	temp=k;
	tempMin->next=tempMax->next;
	for(i=min;i<=max;i++)
	{
		temp=k->next;
		free((void*)k);
		k=temp;
	}
	return OK;
}
Status ListCreate(LinkList &L)
{
	ElemType ins;
	printf("��ʼ��������������\n");
	while(ElemInput(ins))
		ListInsert(L,LocateElem(L,ins),ins);
	return OK;
}
int ElemInput(ElemType &input)
{
	return scanf("%d",&input);
}
void ElemOutput(ElemType &output)
{
	printf("%d\t",output);
}
Status InitList(LinkList &L)
{
	LNode *headNode;
	headNode=(LNode *)malloc(sizeof(LNode));
	L=headNode;
	L->next=NULL;
	return TRUE;
} 
int ListLength(LinkList &L)
{
	int len=0,i;
	LNode *temp=L;
	while(temp->next!=NULL)  
	{
		len++;
		temp=temp->next;
	}
	return len;
}
Status ListInsert(LinkList &L,int num,ElemType add)
{
	LNode *temp=L,*ins;
	int i;
	if(num!=-1&&(num>ListLength(L)+1||num<=0))  return ERROR;
	if(num==-1)  num=1;  //�������򴴽����ϲ���ʱ�״β�������ڵ�һ��Ԫ��֮ǰ����ʱʹ�õĽӿ� 
	for(i=0;i<num-1;i++)   //������Ҫ�����λ�õ�ǰһ��λ�� 
		temp=temp->next;
	ins=(LNode *)malloc(sizeof(LNode));
	if(!ins)  return ERROR;
	ins->data=add;
	ins->next=temp->next;
	temp->next=ins;
	return OK;
}
Status ListDelete(LinkList &L,int num,ElemType &del)
{
	LNode *temp=L,*delTemp;
	int i;
	if(!ListLength(L)||num<=0||num>ListLength(L))  return ERROR;
	for(i=0;i<num-1;i++)
		temp=temp->next;
	delTemp=temp->next;
	temp->next=delTemp->next;
	del=delTemp->data;
	free((void *)delTemp);
	return OK;
}
Status GetElem(LinkList &L,int num,ElemType &get)
{
	LNode *temp=L;
	int i;
	if(!ListLength(L)||num<=0||num>ListLength(L))  return ERROR;
	for(i=0;i<num;i++)
		temp=temp->next;
	get=temp->data;
	return OK;
}
int LocateElem(LinkList &L,ElemType loc)  //�������ҵ��±귵�غ�������봴��ʱ���±귵�� 
{
	int i=0;
	LNode *temp=L;
	if(!ListLength(L))  return -1;  //�ձ�ʱ�Ĳ����һ��Ԫ�أ��������ڿձ�ʱ�������ҷ��ش���ı�ʶ  
	while(temp->next!=NULL)
	{
		temp=temp->next;
		if(temp->next!=NULL&&(loc>temp->data&&loc<temp->next->data))  //���Ѳ��������Ԫ��֮�� 
			return i+2;
		else if(temp->next!=NULL&&loc==temp->data)  //��������µĲ��� 
			return i+1;
		else if(temp->next==NULL&&loc>temp->data)  //�����Ѳ��������Ԫ��ʱ 
			return ListLength(L)+1;
		i++;
	}
	return 1;
}
Status ClearList(LinkList &L)
{
	LNode *temp=L->next,*tempF;
	while(temp!=NULL)
	{
		tempF=temp->next;
		free((void *)temp);
		temp=tempF;
	}
	return OK;
}
