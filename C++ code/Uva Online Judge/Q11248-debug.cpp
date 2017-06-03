#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn_v = 110;
const int maxn_e = 22000;
const int inf = 2100000000 ;
struct edge
{
	int from,to,cap,flow;
	edge() {}
	edge(int f,int t,int cp,int fl)
	{
		from = f;
		to = t;
		cap = cp;
		flow = fl;
	}
};
vector<edge> E;
vector<int> G[maxn_v];
vector<int> cut;
int n,m,c,s,t;
int d[maxn_v];
bool vis[maxn_v];
int cur[maxn_e];
int cmp(edge a,edge b)
{
	if(a.from == b.from) return a.to < b.to;
	else return a.from < b.from;
}

void add_e(int from,int to,int cap)
{
	E.push_back(edge(from,to,cap,0));
	E.push_back(edge(to,from,0,0));
	int e = E.size();
	G[from].push_back(e-2);
	G[to].push_back(e-1);
}
void read_graph()
{
	s = 1;
	t = n;
	for(int i = 0; i <= n; i++) G[i].clear();
	E.clear();
	for(int i = 0; i < m; i++)
	{
		int from,to,cap;
		scanf("%d%d%d",&from,&to,&cap);
		add_e(from,to,cap);
	}

}
bool bfs()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(s);
	d[s] = 0;
	vis[s] = 1;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = 0; i < G[u].size(); i++)
		{
			edge& e = E[G[u][i]];
			int v = e.to;
			if(!vis[v] && e.cap > e.flow)
			{
				vis[v] = 1;
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
	return vis[t];
}
int dfs(int u,int a)
{
	if(u == t || a == 0) return a;
	int flow = 0, f;
	for(int& i = cur[u]; i < G[u].size(); i++)
	{
		edge& e = E[G[u][i]];
		if(d[u] + 1 == d[e.to] && (f = dfs(e.to,min(a,e.cap-e.flow))) > 0)
		{
			e.flow += f;
			E[G[u][i]^1].flow -= f;
			flow += f;
			a -= f;
			if(a == 0) break;
		}
	}
	return flow;
}

int max_flow()
{
	int flow = 0;
	while(bfs())
	{
		memset(cur,0,sizeof(cur));
		flow += dfs(s,inf);
	}
	return flow;
}
void min_cut()
{
	bfs();
	cut.clear();
	for(int i = 0; i < E.size(); i++)
	{
		edge& e = E[i];
		if(vis[e.from] && !vis[e.to] && e.cap > 0) cut.push_back(i);
	}
}
void reduce()
{
	for(int i = 0; i < E.size(); i++)
		E[i].cap -= E[i].flow;
}
void clear()
{
	for(int i = 0; i < E.size(); i++) E[i].flow = 0;
}
void print()
{
	for(int i = 0; i < E.size(); i++)
		printf("%d -> %d %d\n",E[i].from,E[i].to,E[i].cap);
}
int main()
{
	int cas = 0;
	while(scanf("%d%d%d",&n,&m,&c) && n)
	{
		read_graph();
		//print();
		printf("Case %d: ",++cas);
		int maxflow = max_flow();
		if(maxflow >= c || c == 0) printf("possible\n");
		else
		{
			vector<edge> ans;
			min_cut();
			reduce();
			for(int i = 0; i < cut.size(); i++)
			{
				clear();
				edge& e = E[cut[i]];
				e.cap += c;
				if(maxflow + max_flow() >= c) ans.push_back(E[cut[i]]);
				e.cap -= c;
			}
			if(ans.empty()) printf("not possible\n");
			else
			{
				sort(ans.begin(),ans.end(),cmp);
				for(int i = 0; i < ans.size(); i++)
				{
					if(i == 0) printf("possible option:(%d,%d)",ans[i].from,ans[i].to);
					else printf(",(%d,%d)",ans[i].from,ans[i].to);
				}
				printf("\n");
			}
		}
	}
	return 0;
}

