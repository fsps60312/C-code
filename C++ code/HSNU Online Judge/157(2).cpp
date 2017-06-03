#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,flow,limit;
	Edge(){}
	Edge(const int _a,const int _b,const int _f,const int _l):a(_a),b(_b),flow(_f),limit(_l){}
};
vector<Edge>EDGE;
vector<int>ET[20002];
void AddEdge(const int a,const int b,const int limit)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,0,limit));
	EDGE.push_back(Edge(b,a,limit,limit));
	ET[a].push_back(sz),ET[b].push_back(sz^1);
}
int N,M;
int LEVEL[20002];
bool Bfs(const int source,const int target)
{
	for(int i=0;i<N+M+2;i++)LEVEL[i]=INF;
	queue<int>q;
	LEVEL[source]=0,q.push(source);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			if(e.flow==e.limit||LEVEL[e.b]!=INF)continue;
			LEVEL[e.b]=LEVEL[u]+1,q.push(e.b);
		}
	}
	return LEVEL[target]!=INF;
}
int Dfs(const int u,const int target,int supply)
{
	if(!supply||u==target)return supply;
	int ans=0;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(e.flow==e.limit||LEVEL[e.a]+1!=LEVEL[e.b])continue;
		const int result=Dfs(e.b,target,min(e.limit-e.flow,supply));
		supply-=result,ans+=result;
		EDGE[ei].flow+=result,EDGE[ei^1].flow-=result;
	}
	return ans;
}
bool Solve(const int maxflow)
{
	assert((int)EDGE.size()==(M*3+N)*2);
	for(int i=0;i<N;i++)EDGE[(M*3+i)*2].limit=EDGE[(M*3+i)*2+1].limit=maxflow;
	for(int i=0;i<M*3+N;i++)EDGE[i*2].flow=0,EDGE[i*2+1].flow=EDGE[i*2+1].limit;
	int flow=0;
	while(Bfs(N+M,N+M+1))flow+=Dfs(N+M,N+M+1,INF);
	return flow==M;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N+M+2;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0;i<M;i++)AddEdge(N+M,i,1);
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		AddEdge(i,M+a,1),AddEdge(i,M+b,1);
	}
	for(int i=0;i<N;i++)AddEdge(M+i,N+M+1,0);
	int l=1,r=M;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Solve(mid))r=mid;
		else l=mid+1;
	}
	assert(Solve(r));
	printf("%d\n",r);
	for(int i=0;i<M;i++)
	{
		const Edge &ea=EDGE[(M+i*2)*2],&eb=EDGE[(M+i*2+1)*2];
		assert((ea.flow==ea.limit)!=(eb.flow==eb.limit));
		puts(ea.flow==ea.limit?"1":"0");
	}
	return 0;
}
