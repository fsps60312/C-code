#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define N 1010
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define cl(xx,yy) memset((xx),(yy),sizeof((xx)))
 
int n,S,D,fa[N],dep[N];
vector<int>e[N];
vector<pii>Leaf;
bool color[N],leaf[N];
 
bool cmp(pii x , pii y){
	return x.second > y.second;
}
 
void dfs(int u,int par,int d){
	fa[u] = par; dep[u] = d;
	leaf[u] = true;
	for(int i = 0; i < e[u].size(); i++){
		int v = e[u][i];
		if(v == fa[u]) continue;
		leaf[u] = false;
		dfs(v,u,d+1);
	}
	if(leaf[u]) Leaf.pb(mp(u,d));
}
 
int find(int u){
	int d = D;
	while(u != S && d){
		u = fa[u]; d--;
	}
	return u;
}
 
void bfs(int rt){
	bool vis[N];
	queue<pii>que;
	cl(vis,false);
	while(!que.empty()) que.pop();
	que.push(mp(rt,0));
	while(!que.empty()){
		pii x = que.front(); que.pop();
		int u = x.first , d = x.second;
		if(leaf[u]) color[u] = true;
		for(int i = 0; i < e[u].size(); i++){
			int v = e[u][i];
			if(vis[v] || d+1 > D) continue;
			que.push(mp(v,d+1));
			vis[v] = true;
		}
	}
}
 
int main(){
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	int T;
	scanf("%d",&T);
	int kase=1;
	while(T--){
		scanf("%d%d%d",&n,&S,&D);
		for(int i = 0; i <= n; i++)
			e[i].clear();
		Leaf.clear(); 
		cl(fa,-1); cl(dep,-1); cl(color,false);
		vector<int> x,y;
		for(int i = 1; i < n; i++){
			int u,v;
			scanf("%d%d",&u,&v);
			x.pb(u);y.pb(v);
			e[u].pb(v); e[v].pb(u);
		}
		dfs(S,-1,0);
		sort(Leaf.begin(),Leaf.end(),cmp);
		//for(int i = 0; i < Leaf.size(); i++)
		//	printf("%d --- %d\n",Leaf[i].first,Leaf[i].second);
		int cnt = 0;
		for(int i = 0; i < Leaf.size(); i++){
			int x = Leaf[i].first;
			if(color[x]) continue;
			int rt = find(x);
			if(rt != S) cnt++;
			bfs(rt);
		}
		printf("%d\n",cnt);
		continue;
		if(kase++==527)
		{
			printf("%d\n%d %d\n",n,S,D);
			for(int i=1;i<n;i++)printf("%d %d\n",x[i],y[i]);
			return 0;
		}
	}
	return 0;
}

