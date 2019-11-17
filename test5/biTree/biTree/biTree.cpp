/* biTree.cpp -- �������Ļ�������*/ 
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
	//�����������ӣ� 124  5  36  7  //
	//�������������ӣ�124   3 5  // 
	int sum=1,i;
	for(i=1;i<BiTreeDepth(T);i++)  //Ҷ�ӽ����� 
		sum*=2;
	if(NumOfLeaves(T)==sum)  //�ж��Ƿ���� 
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
	//��ȫ���������ӣ�1248  9  5A  B  36C   7  // 
	int flag=0;
	SqQueue Q;
	InitQueue(Q);
	BiTNode *head=NULL;
	if(!T)  return 1;  //�ն���������ȫ������ 
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
			//���������ʱĳ���������Ϊ�յ���������Ϊ�գ���ز�Ϊ��ȫ������
			else if(childStatus(head)==2||childStatus(head)==0) flag=1;  
			//����ǰ���ʵĽ��ΪҶ�ӽڵ�����Ӳ�Ϊ�յ��Һ���Ϊ�յ�����������ΪҶ�ӽ�� 
			else if(flag==1&&childStatus(head)!=0)  return 0;  
			//��������ΪҶ�ӽ�㵫�ֲ����������ȫ������ 
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
Status BiTreeExchange(BiTree &T)   //���������ݹ齻�� 
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
Status BiTreeEqual(BiTree T1,BiTree T2,int &flag)  //ǰ��ݹ��жϣ���˲�����ʹ�������ñ��� 
{
	if(!T1&&!T2) flag=1;
	else if(!T1||!T2)  flag=0;
	else
	{
		if(T1->data==T2->data) flag=1;
		else { flag=0;return flag; }
		if(flag)   //��һ����ȵĻ��ż����ݹ�����ж� 
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
Status PreOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem))  // ������ǰ��ǵݹ���� 
{
	SqStack S;
	BiTNode* temp=T;
	InitStack(S);
	while(temp!=NULL||!StackEmpty(S))
	{
		while(temp!=NULL)  //���������� 
		{
			if(!visit(temp->data))  return ERROR;  //����Ϊ��ǰ�����еĸ��ڵ�ʱ����� 
			Push(S,temp);
			temp=temp->lChild; 
		} 
		//�������ڵ㣬��ʱ���ڵ��ѱ����ʹ�����ʼ������������ 
		Pop(S,temp);
		temp=temp->rChild;
	}
	return OK;
	
}
Status InOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem))  //����������ǵݹ���� 
{
	SqStack S;
	BiTNode* temp=T;
	InitStack(S);
	while(temp!=NULL||!StackEmpty(S))
	{
		while(temp!=NULL)  //��ǰҪ���ʵ��������Ľ��������ջ�������ý�� 
		{
			Push(S,temp);
			temp=temp->lChild; 
		} 
		//�������ڵ㣬��ʼ���ʸý�㣬Ȼ������������� 
		Pop(S,temp);
		if(!visit(temp->data))  return ERROR;  //����Ϊ��ǰ�����еĸ��ڵ�ʱ����� 
		temp=temp->rChild;  //��ʼ������������ 
	}
	return OK;
} 
Status PostOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem))  //����������ǵݹ���� 
{
	SqStack S;
	BiTNode *temp=T,*last=NULL,*top=NULL;
	InitStack(S);
	while (!StackEmpty(S)||temp!=NULL)//ջ��Ϊ�մ�����δ�����ʵ��Ľ���������δ�����ʵĽ����� 
	{
		while(temp!=NULL)    //��ǰҪ���ʵ��������Ľ��������ջ�������ý�� 
		{
			Push(S,temp);
			temp=temp->lChild;
		}
		GetTop(S,top);  //top����ʾ��ǰҪ���ʵĽ�� 
		if(top->rChild==NULL||last==top->rChild)  
		//���ϴη��ʵĽ��Ϊ�ý����ҽ��ʱ���ߵ�ǰ���ʵĽ����Һ���Ϊ��ʱ��ֱ�ӷ��ʸý�� 
		{
			if(!visit(top->data))  return ERROR;
			Pop(S,top);
			last=top;
		} 
		else  //����Ϊ�����������ֱ�ӷ����������� 
		{
			temp=top->rChild;
		}
	}
	return OK;
}
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  // ������ǰ��ݹ���� 
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
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //����������ݹ���� 
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
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem))  //����������ݹ���� 
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

