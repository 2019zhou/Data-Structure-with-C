// implement double linked list
#include <stdio.h>
#include <malloc.h>

struct Node{
	int data;
	struct Node * pre;
	struct Node * next;
};

// 头插法
Node* CreateListFront(int a[], int n){
	Node * node;
	node = NULL;
	head = (Node*) malloc(sizeof(Node));
	head->pre = head->next = NULL;
	for(int i = 0;i < n;i++){
		node = (Node *)malloc(sizeof(Node));
		node->data = a[i];
		node->next = head->next;
		if(head->next != NULL){
			head->next->pre = node;
		}
		head->next = node;
		node->pre = head;
	}
	return head;
}


// 尾插法
Node* CreateListBack(int a[], int n){
	Node * node;
	node = NULL;
	head = (Node*) malloc(sizeof(Node)); // 这里的head会发生变化
	head->pre = head->next = NULL;
	for(int i = 0;i < n;i++){
		node = (Node *)malloc(sizeof(Node));
		node->data = a[i];
		head->next = node;
		node->pre = head;
		head = node;
	}
}

void DestroyList(Node * head){
	Node * pre = head;
	Node * p = pre->next;
	while(p!= NULL){
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}

bool ListEmpty(Node * head){
	return head->next==NULL;
}

int ListLength(Node * head){
	Node * p = head;
	int i = 0;
	while(p->next != NULL){
		i++;
		p = p->next;
	}
	return i;
}

int PrintList(Node * head){
	Node * p = head->next;
	while(p!= NULL){
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}

bool ListInsert(Node * head, int position, int data){
	Node* p = head;
	if(position <= 0) return false;
	for(int j = 0;j < position - 1 && p!= NULL;j++){
		p = p->next;
	}
	if(p == NULL)
		return false;
	else{
		Node * node = (Node *)malloc(sizeof(Node));
		node->data = data;
		node->next = p->next;
		if(p->next != NULL){
			p->next->pre = node;
		}
		node->pre = p;
		p->next = node;
		return true;
	}
}

bool ListDelete(Node * head, int position){
	Node * p = head;
	if(position <= 0)
		return false;
	for(int j = 0;j < position - 1 && p!= NULL;j++){
		p = p->next;
	}
	if(p == NULL){
		return false;
	}else{
		Node * q = p->next;
		if(q== NULL)
			return false; // 表明不存在第i个结点
		p->next = q->next;
		if(p->next!= NULL)
			p->next->pre = p;
		free(q);
		return true;
	}
}