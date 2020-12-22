//先序、中序和后序递归遍历算法
#include "btree.cpp"
void PreOrder(node *b)  		//先序遍历的递归算法
{
	if (b!=NULL)  
	{
		printf("%c ",b->data);	//访问根结点
		PreOrder(b->lchild);	//先序遍历左子树
		PreOrder(b->rchild);	//先序遍历右子树
	}
}
void InOrder(node *b)   		//中序遍历的递归算法
{
	if (b!=NULL)  
	{	
		InOrder(b->lchild);		//中序遍历左子树
		printf("%c ",b->data);	//访问根结点
		InOrder(b->rchild);		//中序遍历右子树
	}
}
void PostOrder(node *b) 		//后序遍历的递归算法
{
	if (b!=NULL)  
	{
		PostOrder(b->lchild);	//后序遍历左子树
		PostOrder(b->rchild);	//后序遍历右子树
		printf("%c ",b->data);	//访问根结点
	}
}
int main()
{
	node *b;
	char input[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(b, input);
	printf("b:");
	DispBTree(b);
	printf("\n");
	printf("先序遍历序列:");PreOrder(b);printf("\n");
	printf("中序遍历序列:");InOrder(b);printf("\n");
	printf("后序遍历序列:");PostOrder(b);printf("\n");
	DestroyBTree(b);
	return 1;
}
