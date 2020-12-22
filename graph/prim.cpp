// 实现最小生成树
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXV = 1000;
const int INF = 100000000;

int n, m, G[MAXV][MAXV]; //n为顶点数，MAXV为最大顶点数
int d[MAXV]; // 顶点与集合S的最短距离
bool vis[MAXV] = {false}; // vis[i] = true表示已经访问

int prim(){
	fill(d, d+MAXV, INF);  
	d[0] = 0;  //  0号节点到集合S的距离为0，其余全为INF
	int ans = 0;  // 存放最小生成树的边权之和
	for(int i = 0;i < n;i++){
		int u = -1, MIN = INF;
		for(int j = 0;j < n;j++){
			if(vis[j] == false && d[j] < MIN){
				u = j;
				MIN = d[j];
			}
		}
		if(u == -1) return -1;
		vis[u] = true;
		ans += d[u];
		for(int v = 0; v < n;v++){
			if(vis[v] == false && G[u][v] != INF && G[u][v] < d[v]) //v未访问，u能够到达v，以u为中介点使得v离集合S更近
				d[v] = G[u][v];
		}
	}
	return ans;
}



int main(){
	int u, v, w;
	scanf("%d%d", &n, &m);
	fill(G[0], G[0] + MAXV*MAXV, INF);
	for(int i = 0;i < m;i++){
		scanf("%d%d%d", &u, &v, &w);
		G[u][v] = G[v][u] = w;
	}
	cout << prim() << endl;
	return 0;
}
