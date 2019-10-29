/* SqList.c-- ˳���Ļ������� */
#include<stdio.h>
#include<stdlib.h> 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status; 
typedef int Bool;
typedef int ElemType;
typedef struct{
	ElemType *elem;  //˳������ʼ��ַ 
	int length;
	int listSize;
}SqList;
Bool compare(ElemType elem1,ElemType elem2);
Status InitList(SqList * L);
int FindElem(SqList * L,ElemType elem);
Status ListInsert(SqList * L,ElemType add);
Status ListDelete(SqList * L,int num,ElemType *delPt) ;
Status ListInverse(SqList * L);
Status ListMerge(SqList *L1,SqList *L2);
Status ListCreate(SqList * L);
Status GetList(SqList * L);
void SetElem(ElemType *elem);
int main(void)
{
	SqList L1,L2;
	ElemType del,find;
	int num;
	InitList(&L1);InitList(&L2);
	ListCreate(&L1);getchar();ListCreate(&L2);
	ListInverse(&L1);printf("�����˳���Ϊ��\n");GetList(&L1);
	ListInverse(&L1);  //����Ϊ����ǵݼ� 
	ListMerge(&L1,&L2);	printf("�ϲ���˳���Ϊ��\n");GetList(&L1);
	getchar();  //��ȡ��������ͣ�͵�q�ַ� 
	printf("������Ҫɾ����Ԫ����ţ�");scanf("%d",&num);ListDelete(&L1,num,&del); GetList(&L1);
	printf("ɾ��Ԫ��Ϊ��%d\n",del);
	printf("������Ҫ���ҵ�Ԫ��ֵ��");
	SetElem(&find);
	if(FindElem(&L1,find))
		printf("��Ԫ��λ�ã�%d\n",FindElem(&L1,find));  //����Ԫ�� 
	else printf("δ�ҵ�����\n");
	return 0;
}
void SetElem(ElemType *elem)
{
	scanf("%d",elem);
}
Status GetList(SqList * L)
{
	int i;
	if(L->length==0)  return ERROR;
	for(i=0;i<L->length;i++)
	{
		printf("%d\t",L->elem[i]);
	}
	printf("\n");
	return OK;
}
Status ListCreate(SqList * L)  //���ݲ��뺯��ѭ������һ������˳��� 
{
	ElemType elem;
	printf("����˳�����,q�뿪���룺\n");
	while(scanf("%d",&elem))
	{
		ListInsert(L,elem);
	}
	return OK;
}
Bool compare(ElemType elem1,ElemType elem2)
{
	return elem1>elem2;
} 
Status InitList(SqList * L)  //��ʼ��˳���Ϊ˳�������ڴ�ռ估���ɻ���ַ 
{
	L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem)
		return ERROR;
	L->length=0;
	L->listSize=LIST_INIT_SIZE;
	return OK;
}
int FindElem(SqList * L,ElemType elem)
{
	int i;
	for(i=0;i<L->length;i++)
	{
		if(L->elem[i]==elem)
			return i+1;
	}
	return -1; 
}
Status ListInsert(SqList * L,ElemType add)
{
	ElemType *newBase;
	int i,num;
	if(L->length>L->listSize)
	{
		newBase=(ElemType*)realloc(L->elem,(L->listSize+LISTINCREMENT)*sizeof(ElemType));
		if(!newBase)  return OVERFLOW;
		L->elem=newBase;
		L->listSize+=LISTINCREMENT;
	}
	if(L->length==0)  //������ʱ
	{
		L->elem[0]=add;
		L->length++;
		return OK;
	} 
	else
	{
		if(!compare(L->elem[L->length-1],add)) 
		{
			L->elem[L->length]=add;
			L->length++;
			return OK;
		}
		else
			for(i=0;i<L->length;i++)
			{
				if(compare(L->elem[i],add))
				{
					num=i;
					break;
				}
			}
		for(i=L->length-1;i>=num;i--)
		{
			L->elem[i+1]=L->elem[i];
		}
		L->elem[num]=add;
		L->length++;
	}
	return OK;
}
Status ListDelete(SqList * L,int num,ElemType *delPt) 
{
	int i;
	if(L->length==0||num<1||num>L->length)
		return ERROR;
	*delPt=L->elem[num-1];
	for(i=num-1;i<L->length;i++)
	{
		L->elem[i]=L->elem[i+1]; 
	}
	L->length--;
	return OK;
}
Status ListInverse(SqList * L)
{
	int i;
	ElemType temp;
	if(L->length==0)
		return ERROR;
	for(i=0;i<L->length/2;i++)
	{
		temp=L->elem[L->length-i-1];
		L->elem[L->length-1-i]=L->elem[i];
		L->elem[i]=temp;
	}
	return OK;
}
Status ListMerge(SqList *L1,SqList *L2)  //�����ǵݼ�˳��������ϲ� 
{
	int i;
	if(L1->length==0&&L2->length==0)  return ERROR;
	for(i=0;i<L2->length;i++)
	{
		ListInsert(L1,L2->elem[i]);
	}
	return OK;
}


