/* HuffmanTree.cpp -- Ӣ�Ķ��Ĺ����������Լ����� */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
typedef char ElemType;
typedef struct{
	ElemType data;
	unsigned int weight;
	unsigned int parent,lChild,rChild;
}HTNode,*HuffmanTree;  //��̬��������洢�շ���������֪Ҷ�ӽ�����
typedef char** HuffmanCode;  //��̬��������洢�շ������룬��֪Ҷ�ӽڽ������ÿ�������ַ�����
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *weigh,char *map2char,int n);  //weigh�����Ԫ��Ҫ����ֵΪ0
void select(HuffmanTree &HT,int n,int &min1,int &min2);
void count(int *weigh,int *map2num,char *map2char,int &num);
void PassageRead(void); 
void PassageEncoding(HuffmanCode &HC,int *map2num);
void CodeOutput(HuffmanTree HT,int num,HuffmanCode HC); 
void PassageDecoding(HuffmanTree &HT,int m);
int main(void)
{
	int weigh[260]={0},num=0,map2num[260]={0};
	char map2char[260]={'\0'};
	//map2num�����ʾ��ǰ�ַ�����Ӧ�Ľ�����ӳ�䣬����ͨ��ֱ����ǰ�ַ��ҹ��������� 
	//map2char�����ʾ��ǰ��Ŷ�Ӧ���ַ�ӳ�䣬����Ϊ��������Ҷ�ӽ���data��ֵ�Ա������� 
	HuffmanTree HT;
	HuffmanCode HC;
	PassageRead();
	count(weigh,map2num,map2char,num);
	HuffmanCoding(HT,HC,weigh,map2char,num);  //�����������������й��������� 
	CodeOutput(HT,num,HC);  //������ַ���Ӧ�Ĺ��������룬�ո�ͻ��з����μӱ��룬�����ַ����ɲ������ 
	PassageEncoding(HC,map2num);  //ΪӢ�Ķ��Ľ��б��� 
	PassageDecoding(HT,2*num-1);  
	//Ϊ�����ı�����н��룬����˼·Ϊһ��һ�����ַ���Ȼ��Ӹ��ڵ㿪ʼ��
	//����0�������ߣ�����1���Һ����ߣ�ֱ��Ҷ�ӽ��Ȼ�������
	//Ȼ�����´Ӹ���㿪ʼִ����ͬ����ֱ���ַ����� 
	return 0;
}
void PassageRead(void)
{
	char ch;
	FILE *fpt=NULL;
	printf("������Ӣ����ģ����������ENTER����Ȼ��CTRL+Z��ENTER��������������\n");
	printf("��ʼ��ȡӢ����ġ���\n");
	fpt=fopen("Passage.txt","w");
	while((ch=getchar())!=EOF)
	{
		fputc(ch,fpt);
	}
	fclose(fpt);
	printf("�Ѵ����ļ�Passage.txt�ļ���\n");
}
void CodeOutput(HuffmanTree HT,int num,HuffmanCode HC)
{
	int i=0;
	printf("���ַ�����������Ϊ��\n");
	for(i=1;i<=num;i++)
	{
		printf("%c:\t%s\n",HT[i].data,HC[i]);
	}
}
void PassageDecoding(HuffmanTree &HT,int m)
{
	char ch;
	int i,key,root;
	FILE *fptR,*fptW;
	printf("��ʼ���롭��\n");
	fptR=fopen("PassageEnCoding.txt","r");
	fptW=fopen("PassageDecoding.txt","w");
	for(i=1;i<=m;i++)  //�ҵ������ 
	{
		if(HT[i].parent==0)
			root=i;  
	}
	key=root;
	ch=fgetc(fptR);
	while(!feof(fptR))
	{
		key=root;  //���´Ӹ���㿪ʼ 
		while((HT[key].lChild!=0||HT[key].rChild!=0)&&!feof(fptR))
		{
			if(ch=='0')  //����
			{
				key=HT[key].lChild;
			}
			else if(ch=='1') //�Һ���
			{
				key=HT[key].rChild;
			}
			else  //Ϊ�ո�ͻ��з�ʱֱ����� 
            {
                fputc(ch,fptW);
            }
			ch=fgetc(fptR);
		}
		fputc(HT[key].data,fptW);
	}
	fclose(fptR);
	fclose(fptW);
	printf("�����Ѵ���PassageDecoding.txt�ļ���\n");
	printf("�����������\n");
}
void PassageEncoding(HuffmanCode &HC,int *map2num)
{
	FILE *fptR,*fptW;
	char ch;
	printf("��ʼ���롭��\n");
	fptR=fopen("Passage.txt","r");
	fptW=fopen("PassageEncoding.txt","w");
	ch=fgetc(fptR);
	while(!feof(fptR))
	{
	    if(ch==' '||ch=='\n')  //Ϊ�ո�ͻ��з�ֱ����� 
            fputc(ch,fptW); 
        else
            fprintf(fptW,"%s",HC[map2num[ch]]);  //������ַ���Ӧ�Ĺ��������� 
		ch=fgetc(fptR);
	}
	fclose(fptR);
	fclose(fptW);
	printf("�����Ѵ���PassageEncoding.txt�ļ���\n");
	printf("�����������\n");
}
void count(int *weigh,int *map2num,char *map2char,int &num)
{
    int i=0;
	char ch;
	num=0;
	FILE *fpt=fopen("Passage.txt","r");
	ch=fgetc(fpt);
	while(!feof(fpt))
	{
		if(ch!=' '&&ch!='\n')  //��Ϊ�ո�ͻ��з����� 
        	weigh[ch]++;
		ch=fgetc(fpt);
	}
	for(i=0;i<256;i++)
	{
		if(weigh[i])
		{
			weigh[num]=weigh[i];
			weigh[i]=0;
			map2num[i]=num+1;   //����ĸ-���ӳ��
			map2char[num+1]=i;  //�����-��ĸӳ��
			num++;
		}
	}
	fclose(fpt);
}
void select(HuffmanTree &HT,int n,int &min1,int &min2)
{
	int i,temp;
	min1=min2=0;
	//select��������˼�룺
	//�ȴ�1-n���ҵ�parentΪ0��������㣬
	//���ұ�֤min1Ϊ��ǰ�������Ľ������С�ģ�min2Ϊ�������Ľ���д�С�� 
	//��һֱ�Ƚ�min1��֮��ÿ������ֵ������min1��С����min1��ֵΪ�ý�����ţ�
	//min2��ֵΪmin1����ţ��������Ϊmin1��С��min2��С 
	for(i=1;i<=n;i++)  
	{
		if(HT[i].parent==0)
		{
			if(min1)
			{
				min2=i;
				break;
			}
			min1=i;
		}
	}
	if(HT[min1].weight>HT[min2].weight)
	{
		temp=min1;min1=min2;min2=temp;
	}
	for(i=(min1>min2?min1:min2)+1;i<=n;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<=HT[min1].weight)
			{
				temp=min1;min1=i;min2=temp;
			}
		}
	}
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *weigh,char *map2char,int n)
{
	int m,i,min1,min2,pre,now,start;
	HTNode * p;
	char *tempCh;  //��ʱ�Ĵ洢һ��Ҷ�ӽڽ���ַ������ַ�����
	if(n<=1)  return;
	m=2*n-1;  //�ܽ�����
	HT=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));  //0�ŵ�Ԫδ��
	for(p=HT+1,i=1;i<=n;i++,p++)   //�����ֽ��ֿ���ʼ��
	{
		p->data=map2char[i];  //��Ҷ�ӽ�����ĸֵ
		p->weight=weigh[i-1];
		p->parent=p->lChild=p->rChild=0;
	}
	for(;i<=m;i++,p++)
	{
		p->weight=p->parent=p->lChild=p->rChild=0;
		p->data='\0';
	}
	for(i=n+1;i<=m;i++)
	{
		select(HT,i-1,min1,min2);  //�����д�1��i-1��������ҵ�parentΪ0����С���������
		HT[min1].parent=HT[min2].parent=i;
		HT[i].lChild=min1;
		HT[i].rChild=min2;
		HT[i].weight=HT[min1].weight+HT[min2].weight;
	}
	//��ʼ���ݹ���������Ҷ�ӵ���������ÿ���ַ��Ĺ���������
	HC=(HuffmanCode)malloc(sizeof(char*)*(n+1));
	tempCh=(char *)malloc(sizeof(char)*(n));
	tempCh[n-1]='\0';
	for(i=1;i<=n;i++)
	{
		start=n-1;
		for(pre=i,now=HT[i].parent;now!=0;pre=now,now=HT[now].parent)
		{
			if(HT[now].lChild==pre)
				tempCh[--start]='0';
			else
				tempCh[--start]='1';
		}
		HC[i]=(char *)malloc(sizeof(char)*(n-start));
		strcpy(HC[i],&tempCh[start]);  //�ӵ�start���ַ�����и�ֵ
	}
	free(tempCh);
}
