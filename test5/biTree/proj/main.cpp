/* main.cpp */
#include"base.h"
#include"../biTree/biTree.h"
//-+a  *b  -c  d  /e  f  //例子表达式以求前缀、中缀、后缀表达式 
//前序：-+a*b-cd/ef
//中序：a+b*c-d-e/f
//后序：abcd-*+ef/-
int main(void)
{
	int flag=-1,num;
	BiTree tree,tree1,tree2;
	order();
	printf("创建单操作二叉树tree\n");
	CreateBiTree(tree);getchar();  //读取掉换行符以免影响下一个的创建 
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
				printf("叶子节点个数：%d\n",NumOfLeaves(tree)); break;
			case 4:
				printf("该二叉树深度为：%d\n",BiTreeDepth(tree));break;
			case 5:
				printf("创建双操作二叉树tree1和tree2\n");
				if(flag!=-1){	DestroyBiTree(tree1);DestroyBiTree(tree2);	}
				getchar();CreateBiTree(tree1);getchar();CreateBiTree(tree2);getchar();
				printf("两个二叉树%s\n",BiTreeEqual(tree1,tree2,flag)?"相等":"不相等");break;
			case 6:
				BiTreeExchange(tree);break;
			case 7:
				LevelOrderTraverse(tree,TElemOutput);putchar('\n');break;
			case 8:
				printf("该二叉树%s完全二叉树\n",IsCompleteBiTree(tree)?"为":"不为");break;
			case 9:
				printf("该二叉树%s满二叉树\n",IsFullBiTree(tree)?"为":"不为");break;
		}
	}
	return 0;
}
void order(void)
{
	printf(
	"0.退出\n"
	"1.递归前、中、后序遍历\n"
	"2.非递归前、中、后序遍历\n"
	"3.求二叉树叶子结点个数\n"
	"4.求二叉树深度\n"
	"5.判断两二叉树是否相似\n"
	"6.二叉树左右子树互换\n"
	"7.二叉树层序遍历\n"
	"8.判断二叉树是否为完全二树\n"
	"9.判断二叉树是否为满二叉树\n"
	);
}
