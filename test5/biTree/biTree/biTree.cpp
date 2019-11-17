/* biTree.cpp -- 二叉树的基本操作*/ 
#include"biTree.h"
#include"../Stack/SqStack.h"
#include"../Queue/SqQueue.h"
Status DestroyBiTree(BiTree &T)
{
	if(T==NULL)  return 0;
	else
	{
		DestroyBiTree(T->lChild);
		DestroyBiTree(T->rChild);
		free((void*)T);
	}
	return OK;
}
Status IsFullBiTree(BiTree T)
{
	//满二叉树例子： 124  5  36  7  //
	//非满二叉树例子：124   3 5  // 
	int sum=1,i;
	for(i=1;i<BiTreeDepth(T);i++)  //叶子结点个数 
		sum*=2;
	if(NumOfLeaves(T)==sum)  //判断是否相等 
		return 1;
	return 0;
}
int childStatus(BiTree T)
{
	if(!T->lChild&&!T->rChild)  return 0;
	else if(!T->lChild&&T->rChild)  return 1;
	else if(T->lChild&&!T->rChild)  return 2;
	else return 3;
} 
Status IsCompleteBiTree(BiTree T)
{
	//完全二叉树例子：1248  9  5A  B  36C   7  // 
	int flag=0;
	SqQueue Q;
	InitQueue(Q);
	BiTNode *head=NULL;
	if(!T)  return 1;  //空二叉树是完全二叉树 
	else
	{
		EnQueue(Q,T);
		while(!QueueEmpty(Q))
		{
			DeQueue(Q,head);
			if(head->lChild)  
				EnQueue(Q,head->lChild); 
			if(head->rChild)
				EnQueue(Q,head->rChild);
			if(childStatus(head)==1)  return 0;  
			//若层序遍历时某结点左子树为空但右子树不为空，则必不为完全二叉树
			else if(childStatus(head)==2||childStatus(head)==0) flag=1;  
			//若当前访问的结点为叶子节点或左孩子不为空但右孩子为空的情况则后续必为叶子结点 
			else if(flag==1&&childStatus(head)!=0)  return 0;  
			//若后续必为叶子结点但又不满足则非完全二叉树 
		}
	}
	return 1;
} 
Status LevelOrderTraverse(BiTree T,Status(* visit)(TElemType elem))
{
	SqQueue Q;
	InitQueue(Q);
	BiTNode *head=NULL;
	if(!T)  return 0;
	else
	{
		EnQueue(Q,T);
		while(!QueueEmpty(Q))
		{
			DeQueue(Q,head);
			if(head->lChild)  
				EnQueue(Q,head->lChild); 
			if(head->rChild)
				EnQueue(Q,head->rChild);
			if(!visit(head->data))  return ERROR;
		}
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
		if(flag)   //这一级相等的话才继续递归调用判断 
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
Status PreOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem))  // 二叉树前序非递归遍历 
{
	SqStack S;
	BiTNode* temp=T;
	InitStack(S);
	while(temp!=NULL||!StackEmpty(S))
	{
		while(temp!=NULL)  //遍历左子树 
		{
			if(!visit(temp->data))  return ERROR;  //均作为当前子树中的根节点时输出的 
			Push(S,temp);
			temp=temp->lChild; 
		} 
		//弹出根节点，此时根节点已被访问过，开始遍历其右子树 
		Pop(S,temp);
		temp=temp->rChild;
	}
	return OK;
	
}
Status InOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem))  //二叉树中序非递归遍历 
{
	SqStack S;
	BiTNode* temp=T;
	InitStack(S);
	while(temp!=NULL||!StackEmpty(S))
	{
		while(temp!=NULL)  //当前要访问的左子树的结点依次入栈，包括该结点 
		{
			Push(S,temp);
			temp=temp->lChild; 
		} 
		//弹出根节点，开始访问该结点，然后遍历其右子树 
		Pop(S,temp);
		if(!visit(temp->data))  return ERROR;  //均作为当前子树中的根节点时输出的 
		temp=temp->rChild;  //开始遍历其右子树 
	}
	return OK;
} 
Status PostOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem))  //二叉树后序非递归遍历 
{
	SqStack S;
	BiTNode *temp=T,*last=NULL,*top=NULL;
	InitStack(S);
	while (!StackEmpty(S)||temp!=NULL)//栈不为空代表还有未被访问到的结点和右子树未被访问的结点存在 
	{
		while(temp!=NULL)    //当前要访问的左子树的结点依次入栈，包括该结点 
		{
			Push(S,temp);
			temp=temp->lChild;
		}
		GetTop(S,top);  //top即表示当前要访问的结点 
		if(top->rChild==NULL||last==top->rChild)  
		//当上次访问的结点为该结点的右结点时或者当前访问的结点的右孩子为空时可直接访问该结点 
		{
			if(!visit(top->data))  return ERROR;
			Pop(S,top);
			last=top;
		} 
		else  //若不为上述情况，则直接访问其右子树 
		{
			temp=top->rChild;
		}
	}
	return OK;
}
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  // 二叉树前序递归遍历 
{
	if(!T)  return NULL;
	else
	{
		visit(T->data);
		PreOrderTraverse(T->lChild,visit);
		PreOrderTraverse(T->rChild,visit);
		return OK;
	}
}
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //二叉树中序递归遍历 
{
	if(!T)  return NULL;
	else
	{
		InOrderTraverse(T->lChild,visit);
		visit(T->data);
		InOrderTraverse(T->rChild,visit);
		return OK;
	}
} 
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //二叉树后序递归遍历 
{
	if(!T)  return NULL;
	else
	{
		PostOrderTraverse(T->lChild,visit);
		PostOrderTraverse(T->rChild,visit);
		visit(T->data);
		return OK;
	}
}

