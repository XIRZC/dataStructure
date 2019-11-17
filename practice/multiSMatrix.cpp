/* multiSMatrix.cpp -- 利用行逻辑链接的顺序表来表示稀疏矩阵以便矩阵相乘 */
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define MAXRC 20 
#define MAXCC 20 
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct{
	int row;  //行序号 
	int col;  //列序号 
	int value;  //元素值 
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
	printf("请输入要创建的矩阵的行数和列数:");
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
	int sum[MAXCC+1]={0},row,subrow,col,cols,subcols,i,j;  //用来存乘积矩阵的每一行的 
	if(M.cols!=N.rows)  return ERROR;
	dst.rows=M.rows;dst.cols=N.cols;dst.nzeros=0;
	if(M.nzeros*N.nzeros!=0)
	{
		for(row=1;row<=M.rows;row++)   //对于矩阵M的每一行进行循环 
		{
			for(col=1;col<=MAXCC;col++)  //累加数组赋值为0 
				sum[col]=0;
			dst.rpos[row]=dst.nzeros+1;
			if(M.rows>row) 
				cols=M.rpos[row+1];
			else 
				cols=M.nzeros+1;
			for(i=M.rpos[row];i<cols;i++)  //对于M每一行的非零元进行循环 
			{
				subrow=M.data[i].col;
				if(N.rows>subrow)
					subcols=N.rpos[subrow+1];
				else
					subcols=N.nzeros+1;
				for(j=N.rpos[subrow];j<subcols;j++)  //对于N的每M的列序号所对应的行中非零元进行循环 
				{
					col=N.data[j].col;
					sum[col]+=M.data[i].value*N.data[j].value;  //dst中的每行中每列的值是由这个两层循环分开求积加和而得 
				}
			}
			for(col=1;col<=dst.cols;col++)  //将行号、列号、元素值存进dst矩阵里 
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
