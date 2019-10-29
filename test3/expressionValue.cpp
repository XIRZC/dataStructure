/* expressionValue.cpp -- ���ʽ��ֵ����ջ */
//���б��ʽ�������ӡ������ˡ����Լ���������С����,�ó���ֻ�����������λ������ 
//��������ջ  OPTRջ���������  OPNDջ�� ��������������� 
#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1 
#define OVERFLOW -2
int order[7][7]={ 1,1,-1,-1,-1,1,1,
				   1,1,-1,-1,-1,1,1,
				   1,1,1,1,-1,1,1,
				   1,1,1,1,-1,1,1,
				   -1,-1,-1,-1,-1,0,-2,
				   1,1,1,1,-2,1,1,
				   -1,-1,-1,-1,-1,-2,0};
typedef int Status;
typedef int ElemType;  //����int��Ϊ������Ԫ�����ͣ�������������ķ�Χ���Կ���������ȡ�ַ� 
typedef struct SqStack{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack;
Status InitStack(SqStack &S);
Status StackLength(SqStack &S);
Status Push(SqStack &S,ElemType add);
Status Pop(SqStack &S,ElemType &del);
ElemType GetTop(SqStack &S);
ElemType evaluateExpression(void);
int precede(int oper1,int oper2);
int operate(int num1,int oper,int num2);
int oper2num(int oper);
int main(void)
{
	ElemType result;
	while(1)
	{
		printf("������Ҫ����ı��ʽ��CTRL+C�˳�ѭ��\n");
		result=evaluateExpression();
		printf("���Ϊ��%d\n",result);
		getchar();
	}
	return 0;
}
ElemType evaluateExpression(void)  //���ʽ��ֵ���� 
{
	SqStack OPTR,OPND;
	ElemType delOper,delNum1,delNum2,top;
	int ch,sum=0;
	int num,flag=0;
	InitStack(OPTR);Push(OPTR,'#');
	InitStack(OPND);ch=getchar();
	while(ch!='#'||GetTop(OPTR)!='#')
	{
		num=oper2num(ch);
		if(num<=6)
		{
			if(flag==1)
			{
				Push(OPND,sum);sum=0;  //�����滹�������ʱ����ö�λ���Ѽ������ 
			}
			flag=0;
			if(precede(GetTop(OPTR),ch)<0)
			{
				Push(OPTR,ch);ch=getchar();
			}
			else if(precede(GetTop(OPTR),ch)==0)
			{
				Pop(OPTR,delOper);ch=getchar();
			}
			else
			{
				Pop(OPTR,delOper);Pop(OPND,delNum1);Pop(OPND,delNum2);
				Push(OPND,operate(delNum2,delOper,delNum1));
			}
		}
		else
		{
			flag=1;
			sum=sum*10+ch-'0';ch=getchar();  //Ϊ��ʹ��λ��Ҳ�ܲ�����㣬��˿�ʼ�ۺ��������õļ����� 
			if(ch=='#'&&GetTop(OPTR)=='#')  Push(OPND,sum);  //��ֻ�и���ʱ��ֱ��Push 
		}
	}
	Pop(OPTR,delOper);
	if(StackLength(OPTR)!=0)  printf("������ʽ���󣡣���\n");
	return GetTop(OPND); 
}
int precede(int oper1,int oper2)  //�Ƚ���������������ȼ� 
{
	int num1=oper2num(oper1),num2=oper2num(oper2);
	return order[num1][num2];
}
int operate(int num1,int oper,int num2)  //�����������������������������ؽ�� 
{
	switch(oper)
	{
		case '+':return num1+num2;
		case '-':return num1-num2;
		case '*':return num1*num2;
		case '/':return num1/num2;
	}
}
int oper2num(int oper)  //ͨ���ַ��õ������±������������Щ�ַ������� 
{
	switch(oper)
	{
		case '+':return 0;
		case '-':return 1;
		case '*':return 2;
		case '/':return 3;
		case '(':return 4;
		case ')':return 5;
		case '#':return 6;
		default: return 7;
	}
}
Status InitStack(SqStack &S)
{
	S.base=(ElemType*)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
	if(!S.base)  exit(OVERFLOW);
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
	return OK;
}
Status StackLength(SqStack &S)
{
	return S.top-S.base;
}
Status Push(SqStack &S,ElemType add)
{
	if(S.top-S.base>=S.stackSize)
	{
		if(!(S.base=(ElemType*)realloc(S.base,sizeof(ElemType)*(S.stackSize+STACKINCREMENT))))
			exit(OVERFLOW);
		S.top=S.base+S.stackSize;
		S.stackSize+=STACKINCREMENT;
	}
	*(S.top++)=add;
	return OK;
}
Status Pop(SqStack &S,ElemType &del)
{
	if(StackLength(S)==0)  return ERROR;
	del=*(--S.top);
	return OK;
}
ElemType GetTop(SqStack &S)
{
	return *(S.top-1);
}
