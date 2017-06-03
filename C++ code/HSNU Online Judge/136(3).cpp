#include<cstdio>
#include<vector>
#include<queue>
#include<set> 
using namespace std;
const int INF=2147483647;
int N,M;
vector<int>ET[1000];
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
		if(e.c!=0&&color[e.a]!=color[e.b])continue;
		edge.push_back(e);
	}
	EDGE.swap(edge);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		ET[e.a].push_back(i),ET[e.b].push_back(i);
	}
}
int BRANCH[1000];
void MarkBRANCH(const int u,const int fa,const int branch)
{
	BRANCH[u]=branch;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||e.cost!=0)continue;
		MarkBRANCH(nxt,u,branch);
	}
}
void SearchBRANCH(const int u,const int upward)
{
	BRANCH[u]=upward;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(e.cost!=0)continue;
		MarkBRANCH(nxt,u,i);
	}
}
int DP[1000][1<<10],MX[1000],UPWARD[1000],CNT[1000];
int InitDP(const int u,const int fa)
{
	const int limit=(1<<CNT[u])-1;
	for(int i=0;i<=limit;i++)DP[u][i]=-INF;
	DP[u][0]=0;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa||e.cost!=0)continue;
		DP[u][0]+=MX[nxt];
	}
	MX[u]=DP[u][0];
}
void Dfs(const int u,const int fa)
{
	int &upward=UPWARD[u]=-1;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt==fa){upward=i;continue;}
		Dfs(nxt,u);
	}
	SearchBRANCH(u,upward);
	InitDP(u,fa);
	int *dp=DP[u];
	for(int i=0;i<EDGE.size();i++)
	{
		const Edge &e=EDGE[i];
		if(BRANCH[e.a]==upward||BRANCH[e.b]==upward||BRANCH[e.a]==BRANCH[e.b])continue;
		
	}
//	for(int s=1;s<)
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
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(b),ET[b].push_back(a);
		}
		printf("%d\n",Solve());
	}
	return 0;
}
