#include<cstdio>
//#include<cassert>
#include<vector>
#include<queue>
#define int long long
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=9223372036854775807LL;
struct Edge
{
	int flow;
	const int a,b,cost,limit;
	Edge():a(),b(),cost(),limit(){}
	Edge(const int _a,const int _b,const int _cost,const int _flow,const int _limit):flow(_flow),a(_a),b(_b),cost(_cost),limit(_limit){}
};
vector<Edge>EDGE;
vector<int>ET[500];
int V,E,K;
void AddEdge(const int a,const int b,const int cost)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,cost,0,1));
	EDGE.push_back(Edge(b,a,-cost,1,1));
	ET[a].push_back(sz),ET[b].push_back(sz+1);
}
int DIST[500],LEVEL[500];
int Bfs()
{
	for(int i=0;i<V;i++)DIST[i]=INF;
	bool *inq=new bool[V];
	for(int i=0;i<V;i++)inq[i]=false;
	queue<int>q;q.push(0),DIST[0]=0,LEVEL[0]=0,inq[0]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		inq[u]=false;
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			if(e.flow==e.limit)continue;
			if(DIST[u]+e.cost<DIST[e.b]||(DIST[u]+e.cost==DIST[e.b]&&LEVEL[u]+1<LEVEL[e.b]))
			{
				DIST[e.b]=DIST[u]+e.cost,LEVEL[e.b]=LEVEL[u]+1;
				if(!inq[e.b])q.push(e.b),inq[e.b]=true;
			}
		}
	}
	delete[]inq;
	return DIST[V-1];
}
int Dfs(const int u,int flow)
{
	if(u==V-1)return flow;
	int ans=0;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(e.flow<e.limit&&DIST[u]+e.cost==DIST[e.b]&&LEVEL[u]+1==LEVEL[e.b])
		{
			const int tflow=Dfs(e.b,min(flow,e.limit-e.flow));
			flow-=tflow;
			ans+=tflow;
			EDGE[ei].flow+=tflow;
			EDGE[ei^1].flow-=tflow;
			if(flow==0)break;
		}
	}
	return ans;
}
int Solve()
{
	int ans=0;
	for(;;)
	{
		const int cost=Bfs();
		if(cost>K)return ans;
		const int flow=Dfs(0,INF);
		ans+=flow;
		K-=cost;
	}
}
main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%lld",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld%lld",&V,&E,&K);
		for(int i=0;i<V;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<E;i++)
		{
			scanf("%lld%lld%lld",&a,&b,&c),a--,b--;
			AddEdge(a,b,0);
			AddEdge(b,a,c);
		}
		printf("%lld\n",Solve());
	}
	return 0;
}
