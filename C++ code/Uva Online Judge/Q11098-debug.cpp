#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<math.h>
using namespace std;
#define eps 1e-8
#define LL long long
const int maxn = 300+5;

struct Bomb
{
	int x , y , r , e;
	int index;
}bomb[maxn];
inline bool operator < (const Bomb & b1 , const Bomb & b2)
{
	if (b1.e==b2.e) 
	return b1.index < b2.index;
	return b1.e < b2.e;
}

struct Ans
{
	Ans(int dh,int ct,int ix,int no) : depth(dh) , cost(ct) , index(ix) , sccno(no) { }
	int depth;
	int cost;
	int index;
	int sccno;
};

inline bool cmp_cost(const Ans & a1,const Ans & a2)
{
	if (a1.cost==a2.cost) return a1.index < a2.index;
	return a1.cost < a2.cost;
}

inline bool cmp_depth(const Ans & a1,const Ans & a2)
{
	if (a1.depth==a2.depth) return a1.index < a2.index;
	return a1.depth > a2.depth;
}

int n , dfn , scc_cnt , sccno[maxn] , pre[maxn] , low[maxn];
int ind[maxn];  //入度（用于拓扑排序）
bool vis[maxn];
vector<int> G1[maxn];   //原?
vector<int> G2[maxn];   //???
stack<int> S;
vector<Bomb> scc[maxn];  //??通分量的?

inline LL sqr(LL x) { return x*x; }
inline LL dist(int i,int j) { return sqr(bomb[i].x-bomb[j].x)+sqr(bomb[i].y-bomb[j].y); }

inline bool connect(int i,int j)
{
	return dist(i,j)  <= sqr(bomb[i].r+bomb[j].r+bomb[i].e);
}

void input()
{
	for (int i = 0 ; i < n ; ++i) G1[i].clear();
	for (int i = 0 ; i < n ; ++i)
	{
		scanf("%d%d%d%d",&bomb[i].x,&bomb[i].y,&bomb[i].r,&bomb[i].e);
		bomb[i].index = i;
	}
	for (int i = 0 ; i < n ; ++i) {
		for (int j = 0 ; j < n ; ++j) if (i!=j && connect(i,j)) 
		{
			G1[i].push_back(j);
		}
	}
}

void dfs(int u)
{
	pre[u] = low[u] = ++dfn;
	S.push(u);
	for (int i = 0 ; i < G1[u].size() ; ++i)
	{
		int v = G1[u][i];
		if (!pre[v])
		{
			dfs(v);
			low[u] = min(low[u],low[v]);
		} else if (!sccno[v])
			low[u] = min(low[u],pre[v]);
	}
	if (pre[u]==low[u]) {
		++scc_cnt;
		scc[scc_cnt].clear();
		G2[scc_cnt].clear();
		while (true)
		{
			int x = S.top(); S.pop();
			sccno[x] = scc_cnt;
			scc[scc_cnt].push_back(bomb[x]);
			if (x==u) break;
		}
	}
}

//找??通分量并??构?
void find_scc()
{
	dfn = scc_cnt = 0;
	memset(pre,0,sizeof(pre));
	memset(low,0,sizeof(low));
	memset(sccno,0,sizeof(sccno));
	for (int i = 0 ; i < n ; ++i) if (!pre[i])
		dfs(i);
	memset(ind,0,sizeof(ind));
	for (int i = 1 ; i <= scc_cnt ; ++i)
	{
		memset(vis,0,sizeof(vis));
		vis[i] = true;
		for (int j = 0 ; j < scc[i].size() ; ++j) {
			int u = scc[i][j].index;
			for (int k = 0 ; k < G1[u].size() ; ++k) {
				int v = G1[u][k];
				printf("u=%d,v=%d\n",u,v);
				if (vis[sccno[v]]) continue;
				printf("pass\n");
				vis[sccno[v]] = true;
				G2[sccno[u]].push_back(sccno[v]);
				++ind[sccno[v]];
			}
		}
	}
	for(int i=1;i<=scc_cnt;i++){printf("from %d:",i-1);for(const auto v:G2[i])printf(" %d",v-1);puts("");}
}



void solve()
{
	find_scc();
	memset(vis,0,sizeof(vis));
	vector<Ans> ans1;
	for (int i = 1 ; i <= scc_cnt ; ++i)
	{
		sort(scc[i].begin(),scc[i].end());
//		for(const auto v:scc[i])printf(" %d",v.index);puts("");
	}
	stack<int> out;
	int sum = 0;
	int cnt = 0;
	queue<Ans> q;
	vector<Ans> ans2;
	for (int i = 1 ; i <= scc_cnt ; ++i) 
	{
		if (ind[i]==0) { 
			sum += scc[i][0].e;
			++cnt;
			q.push(Ans(0,scc[i][0].e,scc[i][0].index,i));
//			out.push(scc[i][0].index); 
			ans2.push_back(Ans(0,-1,scc[i][0].index,-1));
		}
	}
	while (q.size())
	{
		Ans tmp = q.front(); q.pop();
		printf("u=%d\n",tmp.index);
		if (tmp.depth) ans1.push_back(tmp);
		int u = tmp.sccno;
		for (int i = 0 ; i < G2[u].size() ; ++i)
		{
			int v = G2[u][i];
			--ind[v];
			if (ind[v]==0) q.push(Ans(tmp.depth+1,scc[v][0].e,scc[v][0].index,v));
		}
	}
	sort(ans1.begin(),ans1.end(),cmp_cost);
	for (int i = 0 ; i < ans1.size() ; ++i)
	{
		if (sum > cnt * ans1[i].cost)
		{
			sum += ans1[i].cost;
			++cnt;
			ans2.push_back(ans1[i]);
		}
	}
	sort(ans2.begin(),ans2.end(),cmp_depth);
//	for(const auto a:ans2)printf("(%d,%d)\n",a.depth,a.index);
	for (int i = ans2.size()-1 ; i >= 0 ; --i) out.push(ans2[i].index);
	static int kase=1;
	printf("Case #%d:",kase++);
	while (out.size())
	{
		printf(" %d",out.top());
		out.pop();
	}
	cout << endl;
}

int main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	int T; cin>>T;
//	int k = 0;
	while (T--)
	{
//		++k;
		scanf("%d",&n);
		input();
		solve();
	}
}
