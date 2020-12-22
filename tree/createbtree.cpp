//构造二叉树的算法
#include "btree.cpp"
node *CreateBT1(char *pre,char *in,int n)
/*pre存放先序序列,in存放中序序列,n为二叉树节点个数,
本算法执行后返回构造的二叉链的根节点指针*/
{
	node *s;
	char *p;
	int k;
	if (n<=0) return NULL;
	s=(node *)malloc(sizeof(node));		//创建二叉树节点s
	s->data=*pre;
	for (p=in;p<in+n;p++)					//在中序序列中找等于*ppos的位置k
		if (*p==*pre)						//pre指向根节点
			break;							//在in中找到后退出循环
	k=p-in;									//确定根节点在in中的位置
	s->lchild=CreateBT1(pre+1,in,k);		//递归构造左子树
	s->rchild=CreateBT1(pre+k+1,p+1,n-k-1); //递归构造右子树
	return s;
}
node *CreateBT2(char *post,char *in,int n)
/*post存放后序序列,in存放中序序列,n为二叉树节点个数,
本算法执行后返回构造的二叉链的根节点指针*/
{
	node *s;
	char r,*p;
	int k;
	if (n<=0) return NULL;
	r=*(post+n-1);							//根节点值
	s=(node *)malloc(sizeof(node));		//创建二叉树节点s
	s->data=r;
	for (p=in;p<in+n;p++)					//在in中查找根节点
		if (*p==r)
			break;
	k=p-in;									//k为根节点在in中的下标
	s->lchild=CreateBT2(post,in,k);			//递归构造左子树
	s->rchild=CreateBT2(post+k,p+1,n-k-1);	//递归构造右子树
	return s;
}
int main()
{
	ElemType pre[]="ABDGCEF",in[]="DGBAECF",post[]="GDBEFCA";
	node *b1,*b2;
	b1=CreateBT1(pre,in,7);
	printf("b1:");DispBTree(b1);printf("\n");
	b2=CreateBT2(post,in,7);
	printf("b2:");DispBTree(b2);printf("\n");
	DestroyBTree(b1);
	DestroyBTree(b2);
	return 1;
}
