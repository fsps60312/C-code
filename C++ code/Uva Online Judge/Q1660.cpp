#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<queue>
using namespace std;
const int INF=1000;
int N,M;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b,flow,limit;
	Edge(){}
	Edge(const int _a,const int _b,const int _f,const int _l):a(_a),b(_b),flow(_f),limit(_l){}
};
vector<Edge>OEDGE,EDGE;
vector<int>ET[100];
int DIST[100];
bool Bfs(const int source,const int target)
{
	for(int i=0;i<N*2;i++)DIST[i]=N*2;
	queue<int>q;
	q.push(source);
	DIST[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const auto i:ET[u])
		{
			const Edge &e=EDGE[i];
			if(e.flow==e.limit)continue;
			if(DIST[e.b]>DIST[u]+1)DIST[e.b]=DIST[u]+1,q.push(e.b);
		}
	}
	return DIST[target]<N*2;
}
int CUR[100];
int Dfs(const int u,const int target,int supply)
{
	if(supply==0)return 0;
	if(u==target)return supply;
	int ans=0;
	for(int &i=CUR[u];i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		if(DIST[e.b]!=DIST[e.a]+1||e.flow==e.limit)continue;
		int flow=Dfs(e.b,target,min(supply,e.limit-e.flow));
		EDGE[ET[u][i]].flow+=flow;
		EDGE[ET[u][i]^1].flow-=flow;
		ans+=flow;
		supply-=flow;
		if(!supply)break;
	}
	return ans;
}
int Solve(const int source,const int target)
{
	EDGE=OEDGE;
	int ans=0;
	while(Bfs(source,target))
	{
		for(int i=0;i<N*2;i++)CUR[i]=0;
		ans+=Dfs(source,target,INF);
	}
	return ans;
}
void AddEdge(const int a,const int b,const int limit)
{
	int sz=OEDGE.size();
	OEDGE.push_back(Edge(a,b,0,limit));
	ET[a].push_back(sz++);
	OEDGE.push_back(Edge(b,a,limit,limit));
	ET[b].push_back(sz++);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N*2;i++)ET[i].clear();
		OEDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf(" (%d,%d)",&a,&b);
			AddEdge(a*2,b*2+1,INF);
			AddEdge(b*2,a*2+1,INF);
		}
		for(int u=0,i=EDGE.size();u<N;u++)AddEdge(u*2+1,u*2,1);
		int ans=N;
		for(int a=0;a<N;a++)for(int b=a+1;b<N;b++)getmin(ans,Solve(a*2,b*2+1));
		printf("%d\n",ans);
	}
	return 0;
}
