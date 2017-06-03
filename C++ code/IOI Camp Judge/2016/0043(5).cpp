#include<cstdio>
//#include<cassert>
#include<vector>
#include<queue>
#define int long long
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
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
	EDGE.push_back(Edge(a,b,0,0,1));
	EDGE.push_back(Edge(b,a,cost,0,1));
	ET[a].push_back(sz),ET[b].push_back(sz+1);
}
struct Pq
{
	int u,cost,level;
	Pq():u(),cost(),level(){}
	Pq(const int _u,const int _cost,const int _level):u(_u),cost(_cost),level(_level){}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost>p.cost:level>p.level;}
};
int DIST[500],LEVEL[500];
int Bfs()
{
	for(int i=0;i<V;i++)DIST[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]!=INF)continue;
		DIST[p.u]=p.cost,LEVEL[p.u]=p.level;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			if(e.flow==e.limit)continue;
			pq.push(Pq(e.b,p.cost+e.cost,p.level+1));
		}
	}
//	printf("Bfs()=%lld\n",DIST[V-1]);
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
		const int flow=min(Dfs(0,INF),cost==0?INF:K/cost);
		ans+=flow;
		K-=cost*flow;
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
			AddEdge(a,b,c);
		}
		printf("%lld\n",Solve());
	}
	return 0;
}
