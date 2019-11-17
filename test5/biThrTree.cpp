/* biThrTree.cpp -- ���������������������������� */ 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10 
typedef int Status;
typedef char TElemType;
typedef enum { Link,Thread }PointerTag;  //Link ���Һ���ָ��  Thread  ���� 
typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lChild,*rChild;
	PointerTag lTag,rTag;
}BiThrNode,*BiThrTree;
Status CreateBiThrTree(BiThrTree &T);
Status TElemOutput(TElemType elem);
Status InOrderThreading(BiThrNode* &Thrt,BiThrNode* T);  //��ͨ�������������� 
void InThreading(BiThrTree p,BiThrTree &pre);
Status InOrderTraverseThr(BiThrTree T,Status(* visit)(TElemType elem));
//-+a  *b  -c  d  /e  f  //���ӱ��ʽ����ǰ׺����׺����׺���ʽ 
//ǰ��-+a*b-cd/ef
//����a+b*c-d-e/f
//����abcd-*+ef/-
int main(void)
{
	BiThrTree tree;
	CreateBiThrTree(tree);
	InOrderThreading(tree,tree);
	InOrderTraverseThr(tree,TElemOutput);
	return 0;
}
Status InOrderTraverseThr(BiThrTree T,Status(* visit)(TElemType elem))
{
	BiThrNode* p;
	p=T->lChild;
	while(p!=T)
	{
		while(p->lTag==Link)  p=p->lChild;  //�������������������½� 
		if(!visit(p->data))  return ERROR;
		while(p->rTag==Thread&&p->rChild!=T)  
		{
			p=p->rChild;
			if(!visit(p->data))  return ERROR;
		}
		p=p->rChild;
	} 
	return OK;
}
Status InOrderThreading(BiThrTree &Thrt,BiThrTree T)  //�������Ĵ��¿�ܣ�ǰ���νӣ��м��νӵ��õ��ǵݹ麯�� 
{
	BiThrNode* pre;  //preָ��ǰ���ʵĽ�����һ����� 
	if(!(Thrt=(BiThrNode *)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);  //ͷָ������ 
	Thrt->lTag=Link;Thrt->rTag=Thread;  //ͷָ��ĳ�ʼ�� 
	Thrt->rChild=Thrt;   //��ָ���ʼ����ָ 
	if(!T)  Thrt->lChild=Thrt;  //��������Ϊ�գ�����ָ���ָ 
	else
	{
		Thrt->lChild=T;
		pre=Thrt;
		InThreading(T,pre);  //����ݹ������������������ 
		pre->rChild=Thrt;pre->rTag=Thread;  //ĩβ���ӳ�˫��� 
		Thrt->rChild=pre; 
	}
	return OK;
}
void InThreading(BiThrNode* p,BiThrNode* &pre)  
//�Һ���Ϊ�������������������Ϊ������ǰ���������԰���������ȥ�ݹ���� 
{
	if(p)
	{
		InThreading(p->lChild,pre);  //������������ 
		if(!p->lChild)   //���ӵ�ǰ������ 
		{
			p->lTag=Thread;
			p->lChild=pre;
		}
		if(!pre->rChild)  // �Һ��ӵĺ������ 
		{
			pre->rTag=Thread;
			pre->rChild=p;
		}
		pre=p;
		InThreading(p->rChild,pre);   //������������ 
	} 
}
Status TElemOutput(TElemType elem)
{
	if(!printf("%c",elem)) return ERROR;
	return OK;
}
Status CreateBiThrTree(BiThrTree &T)
{
	char ch;
	scanf("%c",&ch);
	if(ch==' ') 
	{
		T=NULL;
		return NULL;
	}
	else
	{
		T=(BiThrNode *)malloc(sizeof(BiThrNode));
		T->data=ch;
		CreateBiThrTree(T->lChild);
		CreateBiThrTree(T->rChild);
	}
	return OK; 
}
