#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

struct Node{
    int data;
    int lchild;
    int rchild;
    int father;
}Nodes[11];

int n;

int findfather(Node a){
    if(a.father == 0){
        return a.data;
    }
    int t = a.data;
    while(Nodes[t].father != 0){
        t = Nodes[t].father;
    }
    return t;
}


void levelorder(int root){
    queue<int> q;
    q.push(root);
    int cnt;
    int templchild;
    int temprchild;
    cnt = 0;
    while(!q.empty()){
        int temp = q.front();
        templchild = Nodes[temp].lchild;
        temprchild = Nodes[temp].rchild;
        if(temprchild != -1)
            q.push(temprchild);
        if(templchild != -1)
            q.push(templchild);
        if(cnt == 0)
            printf("%d", Nodes[temp].data);
        else
            printf(" %d", Nodes[temp].data);
        cnt++;
        q.pop();
    }
}

int counter = 0;

void Inorder(int root){
    if(Nodes[root].rchild == -1 && Nodes[root].lchild == -1){
        counter++;
        if(counter == n)
            printf("%d", Nodes[root].data);
        else
            printf("%d ", Nodes[root].data);
        return;
    }
    if(Nodes[root].rchild != -1)
        Inorder(Nodes[root].rchild);
    counter++;
    if(counter == n)
        printf("%d", Nodes[root].data);
    else
        printf("%d ", Nodes[root].data);
    if(Nodes[root].lchild != -1)
        Inorder(Nodes[root].lchild);
}


int main(){
    cin >> n;
    char ch;
    for(int i = 0;i < n;i++){
        Nodes[i].data = i;
        cin >> ch;
        if(ch == '-'){
            Nodes[i].lchild = -1;
        }else{
            Nodes[i].lchild = ch - '0';
            Nodes[ch - '0'].father = i;
        }
        cin >> ch;
        if(ch == '-'){
            Nodes[i].rchild = -1;
        }else{
            Nodes[i].rchild = ch - '0';
            Nodes[ch-'0'].father = i;
        }
    }
    
    int root = findfather(Nodes[0]);
    
    levelorder(root);
    cout << endl;
    Inorder(root);
    cout << endl;
    
    return 0;
}