#include<cstdio>
#include<vector>
#include<queue>
#include<set> 
using namespace std;
const int INF=2147483647;
int N,M;
vector<int>ET[1000],EI[1000];
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(int _a,int _b,int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
void RemoveUnnecessaryEdge()
{
	static int color[1000];
	for(int i=0;i<N;i++)color[i]=-1;
	queue<int>q;
	color[0]=0;q.push(0);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(color[nxt]!=-1)continue;
			color[nxt]=color[u]^1;
			q.push(nxt);
		}
	}
	vector<Edge>edge;
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		if(color[e.a]!=color[e.b])continue;
		edge.push_back(e);
	}
	EDGE.swap(edge);
	for(int i=0;i<N;i++)EI[i].clear();
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		EI[e.a].push_back(i),EI[e.b].push_back(i);
	}
}
int BRANCH[1000];
void MarkBRANCH(const int u,const int fa,const int branch)
{
	BRANCH[u]=branch;
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt==fa)continue;
		MarkBRANCH(nxt,u,branch);
	}
}
int DP[1000][1<<10],MX[1000];
int CNT[1000];
void Dfs(const int u,const int fa)
{
	CNT[u]=0;
	for(int i=0;i<ET[u].size();i++)if(ET[u][i]!=fa)Dfs(ET[u][i],u),CNT[u]++;
	int &dp=DP[u];
	for(int i=0;i<(1<<CNT[u]);i++)dp[i]=-INF;
	dp[0]=0;
	for(int i=0;i<ET[u].size();i++)if(ET[u][i]!=fa)dp[0]+=MX[ET[u][i]];
	MX[u]=dp[0];
	BRANCH[u]=-1;
	for(int i=0;i<ET[u].size();i++)
	{
		if(ET[u][i]!=fa)MarkBRANCH(ET[u][i],u,i);
		else MarkBRANCH(fa,u,-1);
	}
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		if(BRANCH[e.a]==-1||BRANCH[e.b]==-1||BRANCH[e.a]==BRANCH[e.b])continue;
	}
}
int Solve()
{
	RemoveUnnecessaryEdge();
	Dfs(0,-1);
	return MX[0];
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			if(c==0)ET[a].push_back(b),ET[b].push_back(a);
			else EDGE.push_back(Edge(a,b,c));
		}
		printf("%d\n",Solve());
	}
	return 0;
}
