/* biTree.h */ 
#ifndef BITREE_H  //Ϊ��ֹ��ΰ���ͷ�ļ�����˫���壬��˼���ͷ�ļ��궨�������������� 
#define BITREE_H 
#include"../proj/base.h"
//�������ݹ���������ص㣺�ȶԸü�����������������Ȼ�����������ݹ���� 
typedef char TElemType;
typedef struct BiTNode{  //���������ݱ�ʾ 
	TElemType data; 
	struct BiTNode *lChild,*rChild;  //���Һ���ָ�� 
}BiTNode,*BiTree;
Status CreateBiTree(BiTree &T);  //�ݹ鴴�������� 
Status DestroyBiTree(BiTree &T);  //�ݹ��ͷŶ����� 
Status PreOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status InOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status PostOrderTraverse(BiTree T,Status(* visit)(TElemType elem));
Status PreOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem));
Status InOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem));
Status PostOrderTraverseRe(BiTree T,Status(* visit)(TElemType elem));
Status LevelOrderTraverse(BiTree T,Status(* visit)(TElemType elem));  //������� 
Status TElemOutput(TElemType elem);
int NumOfLeaves(BiTree T);   //���������Ҷ�ӽ����� 
int BiTreeDepth(BiTree T);   //������������ 
Status BiTreeEqual(BiTree T1,BiTree T2,int &flag);   //�ж������������Ƿ���� 
Status BiTreeCopy(BiTree src,BiTree &dst);   //�������ĸ��� 
Status BiTreeExchange(BiTree &T);   //������������ 
Status IsCompleteBiTree(BiTree T);  //�ж��Ƿ�����ȫ������ 
int childStatus(BiTree T);  //����һ���������Һ��ӵ��Ƿ�Ϊ�յ�״�����ز�ֵͬ�Էֱ�
Status IsFullBiTree(BiTree T); 
#endif
