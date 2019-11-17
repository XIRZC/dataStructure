/* main.cpp */
#include"base.h"
#include"../biTree/biTree.h"
//-+a  *b  -c  d  /e  f  //���ӱ��ʽ����ǰ׺����׺����׺���ʽ 
//ǰ��-+a*b-cd/ef
//����a+b*c-d-e/f
//����abcd-*+ef/-
int main(void)
{
	int flag=-1,num;
	BiTree tree,tree1,tree2;
	order();
	printf("����������������tree\n");
	CreateBiTree(tree);getchar();  //��ȡ�����з�����Ӱ����һ���Ĵ��� 
	while(scanf("%d",&num)&&num)
	{
		switch(num)
		{
			case 1:
				PreOrderTraverse(tree,TElemOutput);
				putchar('\n');
				InOrderTraverse(tree,TElemOutput);
				putchar('\n');
				PostOrderTraverse(tree,TElemOutput);
				putchar('\n');
				break;
			case 2:
				PreOrderTraverseRe(tree,TElemOutput);
				putchar('\n');
				InOrderTraverseRe(tree,TElemOutput);
				putchar('\n');
				PostOrderTraverseRe(tree,TElemOutput);
				putchar('\n');break;
			case 3:
				printf("Ҷ�ӽڵ������%d\n",NumOfLeaves(tree)); break;
			case 4:
				printf("�ö��������Ϊ��%d\n",BiTreeDepth(tree));break;
			case 5:
				printf("����˫����������tree1��tree2\n");
				if(flag!=-1){	DestroyBiTree(tree1);DestroyBiTree(tree2);	}
				getchar();CreateBiTree(tree1);getchar();CreateBiTree(tree2);getchar();
				printf("����������%s\n",BiTreeEqual(tree1,tree2,flag)?"���":"�����");break;
			case 6:
				BiTreeExchange(tree);break;
			case 7:
				LevelOrderTraverse(tree,TElemOutput);putchar('\n');break;
			case 8:
				printf("�ö�����%s��ȫ������\n",IsCompleteBiTree(tree)?"Ϊ":"��Ϊ");break;
			case 9:
				printf("�ö�����%s��������\n",IsFullBiTree(tree)?"Ϊ":"��Ϊ");break;
		}
	}
	return 0;
}
void order(void)
{
	printf(
	"0.�˳�\n"
	"1.�ݹ�ǰ���С��������\n"
	"2.�ǵݹ�ǰ���С��������\n"
	"3.�������Ҷ�ӽ�����\n"
	"4.����������\n"
	"5.�ж����������Ƿ�����\n"
	"6.������������������\n"
	"7.�������������\n"
	"8.�ж϶������Ƿ�Ϊ��ȫ����\n"
	"9.�ж϶������Ƿ�Ϊ��������\n"
	);
}
