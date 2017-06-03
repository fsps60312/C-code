#include<iostream>
#include<string.h>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn =3005;
const int maxm = maxn*maxn/2;
int n , m , q , mstcost;

bool inmst[maxn][maxn];
int weight[maxn][maxn];
bool vis[maxn];
int f[maxn][maxn];
int p[maxn];

int find(int x)
{
	if (x==p[x]) return x;
	return p[x] = find(p[x]);
}

struct Edge
{
	int u , v , cost;
	Edge(int uu,int vv,int c) : u(uu) , v(vv) , cost(c) { }
	Edge() { }
	bool operator<(const Edge&e) const { return cost < e.cost; }
}edge[maxm],uprise[10010];

vector<int> adj[maxn];
vector<Edge> G[maxn];
vector<int> spt;
vector<Edge> mst;

void input()
{
	int u , v , w;
	for (int i = 0 ; i < n ; ++i) G[i].clear();
	for (int i = 0 ; i < m ; ++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		edge[i] = Edge(u,v,w);
		weight[u][v] = weight[v][u] = w;
		G[u].push_back(Edge(u,v,w));
		G[v].push_back(Edge(v,u,w));
	}
	scanf("%d",&q);
	for (int i = 0 ; i < q ; ++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		uprise[i] = Edge(u,v,w);
	}
	for (int i = 0 ; i < n ; ++i) sort(G[i].begin(),G[i].end());
}

void dfs(int x,int fa,int z)
{
	if (vis[x] || x==z) return;
	spt.push_back(x);
	vis[x] = true;
	for (int i = 0 ; i < adj[x].size() ; ++i)
		if (adj[x][i]!=fa) dfs(adj[x][i],x,z);
}

void Kruskal()
{
	sort(edge,edge+m);
	for (int i = 0 ; i < n ; ++i) {
		p[i] = i;
		adj[i].clear();
	}
	int rest = n-1;
	memset(inmst,0,sizeof(inmst));
	mst.clear();
	mstcost = 0;
	for (int i = 0 ; i < m && rest ; ++i)
	{
		int u = find(edge[i].u);
		int v = find(edge[i].v);
		if (u==v) continue;
		--rest;
		p[u] = v;
		u = edge[i].u , v = edge[i].v;
		inmst[u][v] = inmst[v][u] = true;
		mstcost += edge[i].cost;
		adj[u].push_back(v);
		adj[v].push_back(u);
		mst.push_back(edge[i]);
	}
	memset(f,0x3f,sizeof(f));
	for (int i = 0 ; i < mst.size() ; ++i)
	{
		int x = mst[i].u , y = mst[i].v;
		spt.clear();
		memset(vis,0,sizeof(vis));
		dfs(mst[i].u,-1,mst[i].v);
		for (int i = 0 ; i < spt.size() ; ++i)
		{
			int u = spt[i];
			for (int j = 0 ; j < G[u].size() ; ++j)
			{
				int v = G[u][j].v , cost = G[u][j].cost;
				if (u==x && v==y) continue;
				if (u==y && v==x) continue;
				if (vis[v]) continue;
				f[x][y] = f[y][x] = min(f[y][x],cost);
				break;
			}
		}
	}
}

void solve()
{
	Kruskal();
	int sum = 0;
	for (int i = 0 ; i < q ; ++i)
	{
		int x = uprise[i].u , y = uprise[i].v;
		if (!inmst[x][y]) 
			sum += mstcost;
		else 
			sum += min(mstcost-weight[x][y]+uprise[i].cost,mstcost-weight[x][y]+f[x][y]);
	}
	printf("%.4lf\n",(double)sum/q);
}

int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		if (n+m==0) break;
		input();
		solve();
	}
	return 0;
}
