#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define HASH_SIZE 100
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *elem;  //˳������ʼ��ַ
	int length;
	int listSize;
}SqList;
typedef struct{
    ElemType *elem;  //����Ԫ�ػ�ַ
    int count;   //��ǰ����Ԫ�ظ���
    int SizeIndex;
}HashTable;
typedef int TElemType;
typedef struct BiTNode{  //���������ݱ�ʾ
	TElemType data;
	struct BiTNode *lChild,*rChild;  //���Һ���ָ��
}BiTNode,*BiTree;
Status CreateBiTree(BiTree &T);
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status TElemOutput(TElemType elem);
Status InitList(SqList * L);
Status ListInsert(SqList * L,ElemType add);
Status ListDelete(SqList * L,int num,ElemType *delPt);
Status ListCreate(SqList * L);
Status GetList(SqList * L);
Status compare(ElemType elem1,ElemType elem2);
int SqSearch(SqList *L,int key);
int BinarySearch(SqList *L,int key);
//�����������Ĳ��Һ��������
Status SearchBST(BiTree T,int key,BiTree f,BiTree &p);
Status InsertBST(BiTree &T,ElemType elem);
Status CreateBST(BiTree &T);
//hash��Ĵ���������Ͳ����Լ����ŵ�ַ������̽����ɢ��ȥ�����ͻ
Status InitHash(HashTable &H);
int Hash(int key);
void collision(int &pos,int &cnt);
Status SearchHash(HashTable H,ElemType key,int &pos,int &cnt);
Status CreateHash(HashTable &H);
Status InsertHash(HashTable &H,ElemType elem);
/*
�����������������룺
45 24 53 45 12 24 90 q
*/
/*
��ϣ���������룺
105 106 107 205 q
5 6 7 8 
*/ 
int main(void)
{
    int key,num,pos=0,cnt=0;
    BiTree T=NULL,p=NULL;
    HashTable H;
    /*
      //˳����˳������Լ����ֲ���
    SqList L;
    InitList(&L);
    ListCreate(&L);
    getchar();
    printf("������Ҫ���ҵ����֣�����q�뿪���룺");
    while(scanf("%d",&key))
    {
    	pos=SqSearch(&L,key);
		cnt=BinarySearch(&L,key);
		if(pos==-1)
			printf("Ϊ���ҵ�������!!\n");
		else
			printf("˳����ҽ��%d�����ֲ��ҽ��%d\n",pos+1,cnt+1);
	}
    */
      //�����������Ĵ��������롢����
    CreateBST(T);
    printf("���������������������Ϊ��\n");
    InOrderTraverse(T,TElemOutput);
    putchar('\n');
    printf("������Ҫ����Ĺؼ��֣���q���뿪���룺\n");
    while(scanf("%d",&num))
        InsertBST(T,num);
    getchar();
    printf("�������������������������Ϊ��\n");
    InOrderTraverse(T,TElemOutput);
    putchar('\n');
    printf("������Ҫ���ҵĹؼ��֣���q���뿪���룺");
    while(scanf("%d",&key))
        if(SearchBST(T,key,NULL,p))
            printf("��ǰ�����д��ڸùؼ���\n");
        else
            printf("��ǰ�����в����ڸùؼ���\n");
    
    /*
    //��ϣ��Ĵ����������Լ�����
    InitHash(H);
    CreateHash(H);
    printf("������Ҫ���ҵĹؼ��֣���q���뿪���룺");
    while(scanf("%d",&key))
        if(SearchHash(H,key,pos,cnt))
            printf("��ǰ�����д��ڸùؼ�����λ�ڵ�ַ%d\n",pos);
        else
            printf("��ǰ�����в����ڸùؼ���\n");
    */
    return 0;
}
Status InitHash(HashTable &H)
{
    int i;
    H.elem=(ElemType*)malloc(HASH_SIZE*sizeof(ElemType));
    if(!H.elem) return ERROR;
    H.count=0;
    H.SizeIndex=HASH_SIZE;
    for(i=0;i<H.SizeIndex;i++)
    {
        H.elem[i]=0;
    }
    return OK;
}
Status SearchHash(HashTable H,ElemType key,int &pos,int &cnt)
{
    pos=Hash(key);
    while(H.elem[pos]!=0&&H.elem[pos]!=key)
        collision(pos,++cnt);
    if(key==H.elem[pos])
        return SUCCESS;
    else
        return UNSUCCESS;
}
void collision(int &pos,int &cnt)
{
    pos++;
}
int Hash(ElemType key)
{
    return key%HASH_SIZE;
}
Status InsertHash(HashTable &H,ElemType elem)
{
    int pos=0,cnt=0;
    if(SearchHash(H,elem,pos,cnt))
        return DUPLICATE;
    else
    {
        H.elem[pos]=elem;
        H.count++;
        return OK;
    }
}
Status CreateHash(HashTable &H)
{
    int num;
    printf("����������������У�q���뿪���������Hash��Ĵ�����");
    while(scanf("%d",&num))
        InsertHash(H,num);
    getchar();
    return OK;
}
Status CreateBST(BiTree &T)
{
    int num;
    printf("����������������У�q���뿪��������ɶ����������Ĵ�����");
    while(scanf("%d",&num))
        InsertBST(T,num);
    getchar();
    return OK;
}
Status SearchBST(BiTree T,int key,BiTree f,BiTree &p)
{  //��T����ǰ������ָ�룬f����ǰ����ָ���˫��ָ�룬
    //�����ҳɹ�����p��������ĵ�ַ��������p���ز���·���Ϸ��ʵ����һ����㣬f��ʼֵΪ��
    if(!T)  //������Ϊ����ز��Ҳ��ɹ�
    {
        p=f;
        return FALSE;
    }
    else if(key==T->data)  //���ҳɹ�
    {
        p=T;
        return TRUE;
    }
    else if(key<T->data)   //С�ڣ����������������
        return SearchBST(T->lChild,key,T,p);
    else    //���ڣ����������������
        return SearchBST(T->rChild,key,T,p);
}
Status InsertBST(BiTree &T,ElemType elem)
{
    BiTNode *p,*f=NULL,*ins=NULL;
    if(!SearchBST(T,elem,f,p))
    {
        ins=(BiTNode*)malloc(sizeof(BiTNode));
        ins->data=elem;
        ins->lChild=ins->rChild=NULL;
        if(!p)  //��ʱ������Ϊ��
        {
            T=ins;  //ֱ�Ӳ���
        }
        else if(p->data>ins->data)  //С�������������ϲ�
            p->lChild=ins;
        else
            p->rChild=ins;
        return TRUE;
    }
    else return FALSE;
}
int SqSearch(SqList *L,int key)
{
    int i;
    for(i=0;i<L->length;i++)
    {
        if(L->elem[i]==key)
            return i;
    }
    return -1;
}
int BinarySearch(SqList *L,int key)
{
    int left=0,right=L->length,mid;
    while(left<=right)
    {
        mid=(left+right)/2;
        if(L->elem[mid]>key)
            right=mid-1;
        else if(L->elem[mid]<key)
            left=mid+1;
        else
            return mid;
    }
    return -1;
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
Status ListInsert(SqList * L,ElemType add)
{
	ElemType *newBase;
	if(L->length>L->listSize)
	{
		newBase=(ElemType*)realloc(L->elem,(L->listSize+LISTINCREMENT)*sizeof(ElemType));
		if(!newBase)  return OVERFLOW;
		L->elem=newBase;
		L->listSize+=LISTINCREMENT;
	}
	L->elem[L->length]=add;
	L->length++;
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
Status compare(ElemType elem1,ElemType elem2)
{
	return elem1>elem2;
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
Status TElemOutput(TElemType elem)
{
	if(!printf("%d\t",elem)) return ERROR;
	return OK;
}
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c",&ch);
	if(ch==' ')
	{
		T=NULL;
		return 0;
	}
	else
	{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		T->data=ch;
		CreateBiTree(T->lChild);
		CreateBiTree(T->rChild);
	}
	return OK;
}
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //����������ݹ����
{
	if(!T)  return 0;
	else
	{
		InOrderTraverse(T->lChild,visit);
		visit(T->data);
		InOrderTraverse(T->rChild,visit);
		return OK;
	}
}
