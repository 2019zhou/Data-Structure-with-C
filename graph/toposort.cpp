#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXV = 1005;

vector<int> G[MAXV];
int n, m, inDegree[MAXV] ={0};

bool topologicalSort(){
	int num = 0;
	queue<int> q;
	for(int i = 0;i < n;i++){
		if(inDegree[i] == 0){
			q.push(i);// 所有入度为0的顶点入队
		}
	}

	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = 0;i < G[u].size();i++){
			int v = G[u][i];
			inDegree[v]--;
			if(inDegree[v] == 0){
				q.push(v);
			}
		}
		G[u].clear();
		num++;
	}
	if(num == n) return true;
	else return false;
}
 



int main(){
	int u, v;
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++){
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		inDegree[v]++;
	}
	cout << topologicalSort() << endl;
}
