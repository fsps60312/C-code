#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
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
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int DIST[500];
int Bfs()
{
	for(int i=0;i<V;i++)DIST[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]!=INF)continue;
		DIST[p.u]=p.cost;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			if(e.flow==e.limit)continue;
			pq.push(Pq(e.b,p.cost+e.cost));
		}
	}
//	printf("Bfs()=%d\n",DIST[V-1]);
	return DIST[V-1];
}
bool Dfs(const int u)
{
	if(u==V-1)return true;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(e.flow<e.limit&&DIST[u]+e.cost==DIST[e.b])
		{
			EDGE[ei].flow++,EDGE[ei^1].flow--;
			if(Dfs(e.b))return true;
			EDGE[ei].flow--,EDGE[ei^1].flow++;
		}
	}
	return false;
}
int Solve()
{
	int flow=0;
	while((K-=Bfs())>=0)flow++,assert(Dfs(0));
	return flow;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&V,&E,&K);
		for(int i=0;i<V;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<E;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			AddEdge(a,b,c);
		}
		printf("%d\n",Solve());
	}
	return 0;
}
