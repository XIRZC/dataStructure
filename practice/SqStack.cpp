/* bracketsMatch.cpp  检测一个表达式字符串中括号是否匹配 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef char ElemType;
typedef int Status;
typedef struct SqStack{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack; 
int order[7][7]={ 1,1,-1,-1,-1,1,1,
				   1,1,-1,-1,-1,1,1,
				   1,1,1,1,-1,1,1,
				   1,1,1,1,-1,1,1,
				   -1,-1,-1,-1,-1,0,-2,
				   1,1,1,1,-2,1,1,
				   -1,-1,-1,-1,-1,-2,0};
Status InitStack(SqStack &S);
Status Pop(SqStack &S,ElemType &del);
Status Push(SqStack &S,ElemType add);
Status StackEmpty(SqStack &S);
ElemType GetTop(SqStack &S); 
int StackLength(SqStack &S);
Status bracketsMatch(char *str);
void conversion(void);
ElemType evaluateExpression(void);
int precede(char oper1,char oper2);
char operate(char num1,char oper,char num2);
int oper2num(char oper);
Status reverseReco(void);
void Order(void);
int main(void)
{
	char str[30];
	int num;
	ElemType result;
	while(scanf("%d",&num)&&num!=0)
	{
		getchar();
		switch(num)
		{
			case 1:
				printf("请输入表达式：\n");
				gets(str);
				if(bracketsMatch(str))
					printf("括号匹配\n");
				else
					printf("括号不匹配\n");
				break;
			case 2:
				conversion();
				break;
			case 3:
				printf("请输入要计算的表达式\n");
				result=evaluateExpression();
				printf("结果为：%d\n",result);
				break;
			case 4:
				if(reverseReco())  printf("该字符串符合题意\n");
				else printf("该字符串不符合题意\n");
				break;
			default:
				printf("输入选项序号错误!!!\n"); 
				break;
		}
		Order();
	}
	return 0;
}
void Order(void)
{
	printf(
	"0.退出程序\n"
	"1.括号匹配\n"
	"2.数制转换\n"
	"3.表达式求值\n"
	"4.判断字符串是否为st1&逆str1@的形式\n");
}
Status reverseReco(void)
{
	char ch;
	int flag=0;
	ElemType del;
	SqStack S;
	InitStack(S);
	while((ch=getchar())!='@')
	{
		if(ch!='&')
		{
			if(flag==0)
				Push(S,ch);
			else
			{
				Pop(S,del);
				if(del!=ch) return 0;
			}
		}
		else flag=1;
	}
	if(!StackEmpty(S))  return 0;
	return 1;
}
ElemType evaluateExpression(void)
{
	SqStack OPTR,OPND;
	ElemType delOper,delNum1,delNum2,top;
	char ch;
	int num;
	InitStack(OPTR);Push(OPTR,'#');
	InitStack(OPND);ch=getchar();
	while(ch!='#'||GetTop(OPTR)!='#')
	{
		num=oper2num(ch);
		if(num<=6)
		{
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
			Push(OPND,ch-'0');ch=getchar();
		}
	}
	Pop(OPTR,delOper);
	if(StackLength(OPTR)!=0)  printf("输入表达式有误！！！\n");
	return GetTop(OPND); 
}
int precede(char oper1,char oper2)
{
	int num1=oper2num(oper1),num2=oper2num(oper2);
	return order[num1][num2];
}
char operate(char num1,char oper,char num2)
{
	switch(oper)
	{
		case '+':return num1+num2;
		case '-':return num1-num2;
		case '*':return num1*num2;
		case '/':return num1/num2;
	}
}
int oper2num(char oper)
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
void conversion(void)
{
	int num,len,i;
	SqStack S;
	ElemType del;
	InitStack(S);
	printf("请输入一个十进制数\n");
	scanf("%d",&num);
		while(num!=0)
		{
			Push(S,num%8);
			num/=8;
		}
		len=StackLength(S);
		for(i=0;i<len;i++)
		{
			Pop(S,del);
			printf("%d",del);
		}
		printf("\n");
	return;
}
Status bracketsMatch(char *str)
{
	int i,len;
	SqStack S;
	ElemType del;
	InitStack(S);
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]=='('||str[i]=='['||str[i]=='{')
			Push(S,str[i]);
		else if(str[i]==')'||str[i]==']'||str[i]=='}')
		{
			Pop(S,del);
			if(abs(str[i]-del)>2)  //不匹配， 通过ASCAII码看出若左右括号匹配，则两字符相差值的绝对值为2以内 
			{
				Push(S,del);
				return FALSE;
			}	 
		}
	}
	if(!StackEmpty(S))
		return FALSE;
	else
		return TRUE;
}
Status InitStack(SqStack &S)
{
	S.base=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base)  exit(ERROR);
	S.stackSize=STACK_INIT_SIZE;
	S.top=S.base;
	return OK;
}
Status Pop(SqStack &S,ElemType &del)
{
	if(S.top==S.base)  exit(ERROR);
	del=*--S.top;
	return OK;
}
Status Push(SqStack &S,ElemType add)
{
	if(S.top-S.base>=S.stackSize)
	{
		S.base=(ElemType *)realloc(S.base,(S.stackSize+STACKINCREMENT)*sizeof(ElemType));
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
ElemType GetTop(SqStack &S)
{
	return *(S.top-1);
}
int StackLength(SqStack &S)
{
	return S.top-S.base;
}

