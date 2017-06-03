#include<cstdio>
#include<vector>
#include<stack>
#include<cassert>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int N,M;
int PRE[1000],PRE_CNT,LOW[1000],BCC[1000],BCC_CNT;
vector<int>TO[1000];
stack<int>STK;
struct Edge
{
	int a,b;
	bool vis;
	Edge(){}
	Edge(int a,int b):a(a),b(b),vis(false){}
	int To(int from){return from!=a?a:b;}
};
vector<Edge>EDGE;
void explore(int u)
{
	if(LOW[u]++)return;
	for(int i=0;i<TO[u].size();i++)
	{
		int j=EDGE[TO[u][i]].To(u);
		explore(j);
	}
}
void dfs(int u,int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(int i=0;i<TO[u].size();i++)
	{
		Edge &e=EDGE[TO[u][i]];
		if(e.vis)continue;
		e.vis=true;
		int j=e.To(u);
		if(!PRE[j])
		{
			dfs(j,u);
			getmin(LOW[u],LOW[j]);
		}
		else
		{
			assert(BCC[j]==-1);
			getmin(LOW[u],PRE[j]);
		}
	}
	if(fa==-1||LOW[u]==PRE[u])
	{
		while(STK.top()!=u)
		{
			BCC[STK.top()]=BCC_CNT;
			STK.pop();
		}
		BCC[u]=BCC_CNT;
		STK.pop();
		BCC_CNT++;
	}
}
void AddEdge(int a,int b)
{
	int sz=EDGE.size();
	EDGE.push_back(Edge(a,b));
	TO[a].push_back(sz);
	TO[b].push_back(sz);
}
int solve()
{
	int ans=0;
	explore(0);
	for(int i=1;i<N;i++)if(!LOW[i])
	{
		explore(i);
		AddEdge(i-1,i);
		ans++;
	}
	dfs(0,-1);
	assert(STK.empty());
	for(int i=0;i<N;i++)assert(PRE[i]);
	if(BCC_CNT==1)return 0;
	for(int i=0;i<BCC_CNT;i++)LOW[i]=0;
	for(int i=0;i<EDGE.size();i++)
	{
		Edge &e=EDGE[i];
		if(BCC[e.a]==BCC[e.b])continue;
		LOW[BCC[e.a]]++,LOW[BCC[e.b]]++;
	}
	int cnt=0;
	for(int i=0;i<BCC_CNT;i++)
	{
		assert(LOW[i]>0);
		if(LOW[i]==1)cnt++;
	}
	return ans+(cnt+1)/2;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			PRE[i]=LOW[i]=0;
			BCC[i]=-1;
		}
		EDGE.clear();
		PRE_CNT=BCC_CNT=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			if(a==b)continue;
			a--,b--;
			AddEdge(a,b);
		}
		printf("%d\n",solve());
	}
	return 0;
}
/*
1000 0

1000 1
1 1000

1000 2
1 1000 1 1000

1000 2
1 1000 1 999
*/
