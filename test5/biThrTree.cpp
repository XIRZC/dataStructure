/* biThrTree.cpp -- 二叉树的中序线索化和线索遍历 */ 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10 
typedef int Status;
typedef char TElemType;
typedef enum { Link,Thread }PointerTag;  //Link 左右孩子指针  Thread  线索 
typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lChild,*rChild;
	PointerTag lTag,rTag;
}BiThrNode,*BiThrTree;
Status CreateBiThrTree(BiThrTree &T);
Status TElemOutput(TElemType elem);
Status InOrderThreading(BiThrNode* &Thrt,BiThrNode* T);  //普通二叉树的线索化 
void InThreading(BiThrTree p,BiThrTree &pre);
Status InOrderTraverseThr(BiThrTree T,Status(* visit)(TElemType elem));
//-+a  *b  -c  d  /e  f  //例子表达式以求前缀、中缀、后缀表达式 
//前序：-+a*b-cd/ef
//中序：a+b*c-d-e/f
//后序：abcd-*+ef/-
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
		while(p->lTag==Link)  p=p->lChild;  //遍历至左子树的最左下角 
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
Status InOrderThreading(BiThrTree &Thrt,BiThrTree T)  //线索化的大致框架，前后衔接，中间衔接调用的是递归函数 
{
	BiThrNode* pre;  //pre指向当前访问的结点的上一个结点 
	if(!(Thrt=(BiThrNode *)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);  //头指针生成 
	Thrt->lTag=Link;Thrt->rTag=Thread;  //头指针的初始化 
	Thrt->rChild=Thrt;   //右指针初始化回指 
	if(!T)  Thrt->lChild=Thrt;  //若二叉树为空，则左指针回指 
	else
	{
		Thrt->lChild=T;
		pre=Thrt;
		InThreading(T,pre);  //中序递归遍历进行中序线索化 
		pre->rChild=Thrt;pre->rTag=Thread;  //末尾链接成双向的 
		Thrt->rChild=pre; 
	}
	return OK;
}
void InThreading(BiThrNode* p,BiThrNode* &pre)  
//右孩子为空则做后继线索，左孩子为空则做前驱线索，仍按中序线索去递归遍历 
{
	if(p)
	{
		InThreading(p->lChild,pre);  //左子树线索化 
		if(!p->lChild)   //左孩子的前驱线索 
		{
			p->lTag=Thread;
			p->lChild=pre;
		}
		if(!pre->rChild)  // 右孩子的后继线索 
		{
			pre->rTag=Thread;
			pre->rChild=p;
		}
		pre=p;
		InThreading(p->rChild,pre);   //右子树线索化 
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
