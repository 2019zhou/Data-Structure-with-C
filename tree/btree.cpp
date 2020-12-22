//二叉树的基本运算算法
#include <stdio.h>
#include <string>
#include <malloc.h>
using namespace std;
#define MaxSize 100
typedef char ElemType;

struct node {	
	ElemType data;			//数据元素
	node * lchild;	//指向左孩子节点
	node * rchild;	//指向右孩子节点
};

void CreateBTree(node *& b, char *str)	//创建二叉树
{
	node * St[MaxSize],*p=NULL;
	int top=-1,k,j=0;  
	char ch;
	b=NULL;				//建立的二叉树初始时为空
	ch=str[j];
	while (ch!='\0')  	//str未扫描完时循环
	{
   	   	switch(ch) 
		{
		case '(':top++;St[top]=p;k=1; break;		//为左孩子节点
		case ')':top--;break;
		case ',':k=2; break;                      		//为孩子节点右节点
		default:{
			p=(node *)malloc(sizeof(node));
			p->data=ch;p->lchild=p->rchild=NULL;
			if (b==NULL)                    	 	//*p为二叉树的根节点
				b=p;
			else  								//已建立二叉树根节点
			{	
				switch(k) 
				{
				case 1:St[top]->lchild=p;break;
				case 2:St[top]->rchild=p;break;
				}
			}
			}
		}
		j++;
		ch=str[j];
	}
}

void DestroyBTree(node *b)
{	if (b!=NULL)
	{	DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
node *FindNode(node *b,ElemType x) 
{
	node *p;
	if (b==NULL)
		return NULL;
	else if (b->data==x)
		return b;
	else  
	{
		p=FindNode(b->lchild,x);
		if (p!=NULL) 
			return p;
		else 
			return FindNode(b->rchild,x);
	}
}

node *LchildNode(node *p)
{
    return p->lchild;
}

node *RchildNode(node *p)
{
    return p->rchild;
}

int BTHeight(node *b) 
{
   	int lchildh,rchildh;
   	if (b==NULL) return(0); 				//空树的高度为0
   	else  
	{
		lchildh=BTHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh=BTHeight(b->rchild);	//求右子树的高度为rchildh
		return (lchildh>rchildh)? (lchildh+1):(rchildh+1);
   	}
}
void DispBTree(node *b) 
{
	if (b!=NULL)
	{	printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{	printf("(");						//有孩子节点时才输出(
			DispBTree(b->lchild);				//递归处理左子树
			if (b->rchild!=NULL) printf(",");	//有右孩子节点时才输出,
			DispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子节点时才输出)
		}
	}
}

// int main()
// {
// 	node *b;
// 	CreateBTree(b,"A(B(D,E),C(,F))");
// 	DispBTree(b);
// 	printf("\n");
// }
