/* SqList.c-- 顺序表的基本操作 */
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
	ElemType *elem;  //顺序表的起始地址 
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
	ListInverse(&L1);printf("反序后顺序表为：\n");GetList(&L1);
	ListInverse(&L1);  //逆序为有序非递减 
	ListMerge(&L1,&L2);	printf("合并后顺序表为：\n");GetList(&L1);
	getchar();  //读取缓冲区内停滞的q字符 
	printf("请输入要删除的元素序号：");scanf("%d",&num);ListDelete(&L1,num,&del); GetList(&L1);
	printf("删除元素为：%d\n",del);
	printf("请输入要查找的元素值：");
	SetElem(&find);
	if(FindElem(&L1,find))
		printf("该元素位置：%d\n",FindElem(&L1,find));  //查找元素 
	else printf("未找到！！\n");
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
Status ListCreate(SqList * L)  //根据插入函数循环生成一个有序顺序表 
{
	ElemType elem;
	printf("创建顺序表中,q离开输入：\n");
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
Status InitList(SqList * L)  //初始化顺序表，为顺序表分配内存空间及生成基地址 
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
	if(L->length==0)  //空链表时
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
Status ListMerge(SqList *L1,SqList *L2)  //两个非递减顺序表的有序合并 
{
	int i;
	if(L1->length==0&&L2->length==0)  return ERROR;
	for(i=0;i<L2->length;i++)
	{
		ListInsert(L1,L2->elem[i]);
	}
	return OK;
}


