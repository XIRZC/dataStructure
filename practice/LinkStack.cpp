Status InitStack(LinkStack &S)  //建立带头结点的单链表栈 
{
	SNode *headNode;
	headNode=(SNode *)malloc(sizeof(SNode));
	S=headNode;
	S->next=NULL;
	return OK;
}
Status StackEmpty(LinkStack &S)
{
	return S->next==NULL;
}
Status Pop(LinkStack &S,SElemType &del)
{
	SNode *temp=S,*pre;
	if(StackEmpty(S)) return ERROR;
	while(temp->next!=NULL)
	{
		pre=temp;
		temp=temp->next;
	}
	del=temp->data;
	pre->next=temp->next;
	free((SNode *)temp);
	return OK;
} 
Status Push(LinkStack &S,SElemType add)
{
	SNode *temp=S,*ins=NULL;
	while(temp->next!=NULL)
	{
		temp=temp->next;
	} 
	ins=(SNode *)malloc(sizeof(SNode));
	ins->data=add;
	temp->next=ins;
	ins->next=NULL;
	return OK;
}
SElemType GetTop(LinkStack &S)
{
	SNode *temp=S;
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}
	return temp->data;
}
