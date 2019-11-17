/* biTree.cpp -- 二叉树的基本操作 */ 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10 
typedef int Status;
typedef char TElemType;
typedef struct BiTNode{  //二叉树数据表示 
	TElemType data; 
	struct BiTNode *lChild,*rChild;  //左右孩子指针 
}BiTNode,*BiTree;
typedef BiTree SElemType;
typedef struct SqStack{  //栈数据表示 
	SElemType *base;
	SElemType *top;
	int stackSize;
}SqStack; 
//二叉树基本操作 
Status CreateBiTree(BiTree &T);
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status LevelOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status TElemOutput(TElemType elem);
int NumOfLeaves(BiTree T); 
int BiTreeDepth(BiTree T);
Status BiTreeEqual(BiTree T1,BiTree T2,int &flag);
Status BiTreeCopy(BiTree src,BiTree &dst);
Status BiTreeExchange(BiTree &T);
//栈基本操作 
Status InitStack(SqStack &S);
Status Pop(SqStack &S,SElemType &del);
Status Push(SqStack &S,SElemType add);
Status StackEmpty(SqStack &S);
Status GetTop(SqStack &S,SElemType &top);
int StackLength(SqStack &S);
//-+a  *b  -c  d  /e  f  //例子表达式以求前缀、中缀、后缀表达式 
//前序：-+a*b-cd/ef
//中序：a+b*c-d-e/f
//后序：abcd-*+ef/-
int main(void)
{
	int flag;
	BiTree tree,tree1,tree2;
	//CreateBiTree(tree1);
	//getchar();  //读取掉缓冲区内的换行符，以防止影响下一个创建 
	//CreateBiTree(tree2);
	//BiTreeCopy(tree1,tree2);
	//printf("两个二叉树%s",BiTreeEqual(tree1,tree2,flag)?"相等":"不相等");
	CreateBiTree(tree);
	//BiTreeExchange(tree);
	
	//printf("该二叉树深度为：%d",BiTreeDepth(tree));
	//printf("叶子节点个数：%d",NumOfLeaves(tree)); 
	//PreOrderTraverse(tree,TElemOutput);
	//putchar('\n');
	//InOrderTraverse(tree,TElemOutput);
	//putchar('\n');
	//PostOrderTraverse(tree,TElemOutput);
	//putchar('\n');
	LevelOrderTraverse(tree,TElemOutput);
	return 0;
}
Status LevelOrderTraverse(BiTree T,Status(* visit)(TElemType elem))
{
	if(!T)  return OK;
	else
	{
		if(!visit(T->data))  return ERROR;
		LevelOrderTraverse(T->lChild,visit);
		LevelOrderTraverse(T->rChild,visit); 
	}
	return OK;
}
Status BiTreeExchange(BiTree &T)   //左右子树递归交换 
{
	BiTNode *temp;
	if(!T)  return OK;
	else
	{
		temp=T->lChild;
		T->lChild=T->rChild;
		T->rChild=temp;
		BiTreeExchange(T->lChild);
		BiTreeExchange(T->rChild);
	}
	return OK;
}
Status BiTreeCopy(BiTree src,BiTree &dst)
{
	if(!src)  dst=NULL;
	else
	{
		dst=(BiTNode *)malloc(sizeof(BiTNode));
		if(!dst) return ERROR;
		dst->data=src->data;dst->lChild=src->lChild;dst->rChild=src->rChild; 
		BiTreeCopy(dst->lChild,src->lChild);
		BiTreeCopy(dst->rChild,src->rChild);
	}
	return OK;
}
Status BiTreeEqual(BiTree T1,BiTree T2,int &flag)  //前序递归判断，因此参数里使用了引用变量 
{
	if(!T1&&!T2) flag=1;
	else if(!T1||!T2)  flag=0;
	else
	{
		if(T1->data==T2->data) flag=1;
		else { flag=0;return flag; }
		if(flag)
		{
			BiTreeEqual(T1->lChild,T2->lChild,flag);
			BiTreeEqual(T1->rChild,T2->rChild,flag);
		}
	}
	return flag;
}
int BiTreeDepth(BiTree T)
{
	int lDepth=0,rDepth=0;
	if(!T)  return 0;
	lDepth=BiTreeDepth(T->lChild);
	rDepth=BiTreeDepth(T->rChild);
	return lDepth>rDepth?(lDepth+1):(rDepth+1);
}
int NumOfLeaves(BiTree T)
{
	if(!T) return 0;
	if(!T->rChild&&!T->lChild) return 1;
	else return NumOfLeaves(T->lChild)+NumOfLeaves(T->rChild);
}
Status TElemOutput(TElemType elem)
{
	if(!printf("%c",elem)) return ERROR;
	return OK;
}
Status CreateBiTree(BiTree &T)
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
		T=(BiTNode *)malloc(sizeof(BiTNode));
		T->data=ch;
		CreateBiTree(T->lChild);
		CreateBiTree(T->rChild);
	}
}
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  // 二叉树前序非递归遍历 
{
	SqStack S;
	BiTNode* temp=T;
	InitStack(S);
	while(temp ||!StackEmpty(S))
	{
		if(temp)  //遍历左子树 
		{
			if(!visit(temp->data))  return ERROR;  //均作为当前子树中的根节点时输出的 
			Push(S,temp);
			temp=temp->lChild; 
		} 
		else  //推出根节点，遍历右子树 
		{
			Pop(S,temp);
			temp=temp->rChild;
		}
	}
	return OK;
	
}
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //二叉树中序非递归遍历 
{
	SqStack S;
	BiTNode* temp=T;
	InitStack(S);
	while(temp ||!StackEmpty(S))
	{
		if(temp)  //遍历左子树 
		{
			Push(S,temp);
			temp=temp->lChild; 
		} 
		else  //推出根节点，遍历右子树 
		{
			Pop(S,temp);
			if(!visit(temp->data))  return ERROR;  //均作为当前子树中的根节点时输出的 
			temp=temp->rChild;
		}
	}
	return OK;
} 
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //二叉树后序非递归遍历 
{
	SqStack S;
	BiTNode* temp=T,*last=NULL;
	InitStack(S);
	Push(S,T);
	while (!StackEmpty(S))//栈不为空
	{
		GetTop(S, temp);
		if ((temp->lChild == NULL && temp->rChild == NULL) || (last == temp->lChild || last == temp->rChild))//
		{
			if(!visit(temp->data))  return ERROR;  //均作为当前子树中的根节点时输出的 
			Pop(S, temp);
			last = temp;
		}
		else 
		{
			if (temp->rChild != NULL)
				Push(S, temp->rChild);
			if (temp->lChild != NULL)
				Push(S, temp->lChild);
		}
	}
	return OK;
}
/*
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  // 二叉树前序递归遍历 
{
	if(!T)  return NULL;
	else
	{
		visit(T->data);
		PreOrderTraverse(T->lChild);
		PreOrderTraverse(T->rChild);
		return OK;
	}
}
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //二叉树中序递归遍历 
{
	if(!T)  return NULL;
	else
	{
		InOrderTraverse(T->lChild);
		visit(T->data);
		InOrderTraverse(T->rChild);
		return OK;
	}
} 
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //二叉树后序递归遍历 
{
	if(!T)  return NULL;
	else
	{
		PostOrderTraverse(T->lChild);
		PostOrderTraverse(T->rChild);
		visit(T->data);
		return OK;
	}
}*/
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
Status GetTop(SqStack &S,SElemType &top)
{
	if(StackEmpty(S)) return ERROR;
	top=*(S.top-1);
	return OK;
}
int StackLength(SqStack &S)
{
	return S.top-S.base;
}
