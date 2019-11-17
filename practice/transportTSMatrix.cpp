/* transportTSMatrix.cpp -- 稀疏矩阵的矩阵转置 */ 
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef struct{
	int row;  //行序号 
	int col;  //列序号 
	int value; //值 
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];
	int rows,cols,nzeros;
}TSMatrix;
Status CreateTSMatrix(TSMatrix &M);
Status PrintTSMatrix(TSMatrix &M);
Status transportTSMatrix(TSMatrix src,TSMatrix &dst);
int main(void)
{
	TSMatrix M,N;
	CreateTSMatrix(M);
	transportTSMatrix(M,N);
	PrintTSMatrix(N);
	return 0;
}
Status CreateTSMatrix(TSMatrix &M)
{
	int elem,count=1,i,j;
	printf("请输入矩阵的行数和列数:");
	scanf("%d %d",&M.rows,&M.cols);
	printf("请输入各元素:\n");
	for(i=1;i<=M.rows;i++)
	{
		for(j=1;j<=M.cols;j++)
		{
			scanf("%d",&elem);
			if(elem!=0)
			{
				M.data[count].row=i;
				M.data[count].col=j;
				M.data[count].value=elem;
				count++;
			}
		}
	} 	
	M.nzeros=count-1;
	return OK;
}
Status PrintTSMatrix(TSMatrix &M)
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
Status transportTSMatrix(TSMatrix src,TSMatrix &dst)
{
	int num[11]={0};
	int cpot[11]={0},i,j=1;
	dst.cols=src.rows;dst.rows=src.cols;dst.nzeros=src.nzeros;
	//准备工作
	for(i=1;i<=src.nzeros;i++)  //num数组赋值 
	{
		num[src.data[i].col]++;
	}
	cpot[0]=1;
	for(i=1;i<=src.cols;i++)
	{
		cpot[i]=cpot[i-1]+num[i-1];
	} 
	for(i=1;i<=src.nzeros;i++)
	{
		dst.data[cpot[src.data[i].col]].col=src.data[i].row;
		dst.data[cpot[src.data[i].col]].row=src.data[i].col;
		dst.data[cpot[src.data[i].col]].value=src.data[i].value;
		cpot[src.data[i].col]++;
	}
	return OK; 
}
