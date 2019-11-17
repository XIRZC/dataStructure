/* addTSMatrix.cpp -- 三元组顺序表稀疏矩阵的相加 */ 
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define MAXRC 20
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct{
	int row;
	int col;
	int value; 
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];
	int rows,cols,nzeros;
}TSMatrix;
Status CreateTSMatrix(TSMatrix &M);
Status PrintTSMatrix(TSMatrix &M);
Status AddTSMatrix(TSMatrix sub1,TSMatrix sub2,TSMatrix &sum);
int main(void)
{
	TSMatrix sub1,sub2,sum;
	CreateTSMatrix(sub1);
	CreateTSMatrix(sub2);
	AddTSMatrix(sub1,sub2,sum);
	PrintTSMatrix(sum);
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
Status AddTSMatrix(TSMatrix sub1,TSMatrix sub2,TSMatrix &sum)
{
	int i,j,p1=1,p2=1,p=1,temp;
	sum.cols=sub1.cols;sum.rows=sub1.rows;sum.nzeros=0;
	for(i=1;i<=sum.rows;i++)
	{
		while(sub1.data[p1].row<i) p1++;
		while(sub2.data[p2].row<i) p2++;
		while(sub1.data[p1].row==i && sub2.data[p2].row==i)
		{
			if(sub1.data[p1].col==sub2.data[p2].col)
			{
				temp=sub1.data[p1].value+sub2.data[p2].value;
				if(temp)
				{
					sum.data[p].value=temp;
					sum.data[p].row=sub1.data[p1].row;
					sum.data[p].row=sub1.data[p1].col;
					p1++;p2++;p++;
				}
			}
			else if(sub1.data[p1].col>sub2.data[p2].col)
			{
				sum.data[p]=sub2.data[p2];
				p2++;p++;
			}
			else
			{
				sum.data[p]=sub1.data[p1];
				p1++;p++;
			}
		}
		while(sub1.data[p1].row==i)
		{
			sum.data[p]=sub1.data[p1];
			p++;p1++;
		}
		while(sub2.data[p2].row==i)
		{
			sum.data[p]=sub2.data[p2];
			p++;p2++;
		}
	}
	sum.nzeros=p-1;
	return OK;
}
