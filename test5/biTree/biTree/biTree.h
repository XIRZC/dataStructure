/* biTree.h */ 
#ifndef BITREE_H  //为防止多次包含头文件导致双定义，因此加了头文件宏定义来解决这个问题 
#define BITREE_H 
#include"../proj/base.h"
//二叉树递归操作函数特点：先对该级二叉树作基本处理，然后左右子树递归调用 
typedef char TElemType;
typedef struct BiTNode{  //二叉树数据表示 
	TElemType data; 
	struct BiTNode *lChild,*rChild;  //左右孩子指针 
}BiTNode,*BiTree;
Status CreateBiTree(BiTree &T);  //递归创建二叉树 
Status DestroyBiTree(BiTree &T);  //递归释放二叉树 
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status PreOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem));
Status InOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem));
Status PostOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem));
Status LevelOrderTraverse(BiTree T,Status(* visit)(TElemType elem));  //层序遍历 
Status TElemOutput(TElemType elem);
int NumOfLeaves(BiTree T);   //求二叉树的叶子结点个数 
int BiTreeDepth(BiTree T);   //求二叉树的深度 
Status BiTreeEqual(BiTree T1,BiTree T2,int &flag);   //判断两个二叉树是否相等 
Status BiTreeCopy(BiTree src,BiTree &dst);   //二叉树的复制 
Status BiTreeExchange(BiTree &T);   //左右子树互换 
Status IsCompleteBiTree(BiTree T);  //判断是否是完全二叉树 
int childStatus(BiTree T);  //根据一个结点的左右孩子的是否为空的状况返回不同值以分辨
Status IsFullBiTree(BiTree T); 
#endif
