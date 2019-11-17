/* multiSMatrix.cpp -- �������߼����ӵ�˳�������ʾϡ������Ա������� */
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define MAXRC 20 
#define MAXCC 20 
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct{
	int row;  //����� 
	int col;  //����� 
	int value;  //Ԫ��ֵ 
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];
	int rpos[MAXRC+1];
	int rows,cols,nzeros;
}RLSMatrix;
Status CreateRLSMatrix(RLSMatrix &M);
Status PrintRLSMatrix(RLSMatrix M);
Status MultiSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &dst);
int main(void)
{
	RLSMatrix M,N,multi;
	CreateRLSMatrix(M);
	CreateRLSMatrix(N);
	MultiSMatrix(M,N,multi);
	PrintRLSMatrix(multi); 
	return 0;
}
Status CreateRLSMatrix(RLSMatrix &M)
{
	int i,j,elem,count=1,num[MAXRC+1]={0};
	M.rpos[1]=1;
	printf("������Ҫ�����ľ��������������:");
	scanf("%d %d",&M.rows,&M.cols);
	for(i=1;i<=M.rows;i++)
	{
		if(i>1)
		{
			M.rpos[i]=M.rpos[i-1]+num[i-1];
		}
		for(j=1;j<=M.cols;j++)
		{
			scanf("%d",&elem);
			if(elem!=0)
			{
				M.data[count].row=i;
				M.data[count].col=j;
				M.data[count].value=elem;
				count++;
				num[i]++;
			}
		}
	}
	M.nzeros=count-1;
	return OK;
}
Status PrintRLSMatrix(RLSMatrix M)
{
	int i,j,count=1;
	for(i=1;i<=M.rows;i++)
	{
		for(j=1;j<=M.cols;j++)
		{
			if(M.data[count].row==i&&M.data[count].col==j)
			{
				printf("%d\t",M.data[count].value);
				count++;
			}
			else
			{
				printf("0\t");
			}
		}
		printf("\n");
	}
	return OK;
}
Status MultiSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &dst)
{
	int sum[MAXCC+1]={0},row,subrow,col,cols,subcols,i,j;  //������˻������ÿһ�е� 
	if(M.cols!=N.rows)  return ERROR;
	dst.rows=M.rows;dst.cols=N.cols;dst.nzeros=0;
	if(M.nzeros*N.nzeros!=0)
	{
		for(row=1;row<=M.rows;row++)   //���ھ���M��ÿһ�н���ѭ�� 
		{
			for(col=1;col<=MAXCC;col++)  //�ۼ����鸳ֵΪ0 
				sum[col]=0;
			dst.rpos[row]=dst.nzeros+1;
			if(M.rows>row) 
				cols=M.rpos[row+1];
			else 
				cols=M.nzeros+1;
			for(i=M.rpos[row];i<cols;i++)  //����Mÿһ�еķ���Ԫ����ѭ�� 
			{
				subrow=M.data[i].col;
				if(N.rows>subrow)
					subcols=N.rpos[subrow+1];
				else
					subcols=N.nzeros+1;
				for(j=N.rpos[subrow];j<subcols;j++)  //����N��ÿM�����������Ӧ�����з���Ԫ����ѭ�� 
				{
					col=N.data[j].col;
					sum[col]+=M.data[i].value*N.data[j].value;  //dst�е�ÿ����ÿ�е�ֵ�����������ѭ���ֿ�����ӺͶ��� 
				}
			}
			for(col=1;col<=dst.cols;col++)  //���кš��кš�Ԫ��ֵ���dst������ 
			{
				if(sum[col])
				{
					if(dst.nzeros+1>MAXSIZE)  return ERROR;
					dst.data[dst.nzeros+1].row=row;
					dst.data[dst.nzeros+1].col=col;
					dst.data[dst.nzeros+1].value=sum[col];
					dst.nzeros++;
				}
			} 
		}
	}
	return OK;
}
