#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue> 
using namespace std;
const int INF=2147483647;
int min(const int a,const int b,const int c,const int d){return min(min(a,b),min(c,d));}
struct Edge
{
	int a,b,cost,flow,limit;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost,const int _flow,const int _limit):a(_a),b(_b),cost(_cost),flow(_flow),limit(_limit){}
};
vector<Edge>EDGE;
vector<int>ET[42];
void AddEdge(const int a,const int b,const int cost)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,cost,0,1));
	EDGE.push_back(Edge(b,a,-cost,1,1));
	ET[a].push_back(sz),ET[b].push_back(sz+1);
}
int N,DIST[42],LEVEL[42];
int Bfs(const int source,const int target)
{
	static bool inq[42];
	for(int i=0;i<N*2+2;i++)DIST[i]=INF,inq[i]=false;
	queue<int>q;
	q.push(source),DIST[source]=0,LEVEL[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		inq[u]=false;
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			if(e.flow==e.limit)continue;
			if(DIST[e.a]+e.cost<DIST[e.b]||(DIST[e.a]+e.cost==DIST[e.b]&&LEVEL[e.a]+1<LEVEL[e.b]))
			{
				DIST[e.b]=DIST[e.a]+e.cost,LEVEL[e.b]=LEVEL[e.a]+1;
				if(!inq[e.b])q.push(e.b),inq[e.b]=true;
			}
		}
	}
	return DIST[target];
}
int Dfs(const int u,const int target,int flow)
{
	if(flow==0||u==target)return flow;
	int ans=0;
	for(const int ei:ET[u])
	{
		if(!flow)break;
		const Edge &e=EDGE[ei];
		if(e.flow<e.limit&&DIST[e.b]==DIST[e.a]+e.cost&&LEVEL[e.b]==LEVEL[e.a]+1)
		{
			const int tflow=Dfs(e.b,target,min(flow,e.limit-e.flow));
			ans+=tflow,flow-=tflow;
			EDGE[ei].flow+=tflow;
			EDGE[ei^1].flow-=tflow;
		}
	}
	return ans;
}
int Solve(const int source,const int target)
{
	int ans=0;
	for(;;)
	{
		const int cost=Bfs(source,target);
		if(cost==INF)break;
		const int ta=cost*Dfs(source,target,INF);
		assert(ta%2==0);
		ans+=ta/2;
	}
	return ans;
}
int R,C;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&R,&C,&N);
		static int r[20],c[20];
		for(int i=0;i<N;i++)scanf("%d%d",&r[i],&c[i]);
		EDGE.clear();
		for(int i=0;i<(N+1)/2*4+2;i++)ET[i].clear();
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(i!=j)
		{
			AddEdge(i,(N+1)/2*2+j,abs(r[i]-r[j])+abs(c[i]-c[j]));
		}
		if(N&1)//one of the point connect outside
		{
			N++;
			for(int i=0;i<N-1;i++)
			{
				const int cost=min(r[i],R+1-r[i],c[i],C+1-c[i]);
				AddEdge(i,N+N-1,cost),AddEdge(N-1,N+i,cost);
			}
		}
		for(int i=0;i<N;i++)AddEdge(N*2,i,0),AddEdge(N+i,N*2+1,0);
		printf("%d\n",Solve(N*2,N*2+1));
	}
	return 0;
}
