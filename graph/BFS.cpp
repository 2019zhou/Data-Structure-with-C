void BFS(node* root){
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node* now = q.front();
		q.pop();
		printf("%d", now->data);
		num++;
		if(num < n) printf(" ");
		if(now->lchild != NULL) q.push(now->lchild);
		if(now->rchild != NULL) q.push(now->rchild);
	}
}
