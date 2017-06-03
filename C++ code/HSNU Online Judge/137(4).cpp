#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int N,M;
int DIST[100000],FA[100000];
struct Pq
{
	int u,fa,cost;
	Pq(){}
	Pq(const int _u,const int _f,const int _c):u(_u),fa(_f),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
void Solve()
{
	for(int i=0;i<N;i++)DIST[i]=-1,FA[i]=-1;
	priority_queue<Pq>pq;
	pq.push(Pq(0,-1,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]!=-1)continue;
		FA[p.u]=p.fa,DIST[p.u]=p.cost;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(e.a==p.u?e.b:e.a);
			pq.push(Pq(nxt,ei,p.cost+e.cost));
		}
	}
}
int GetSecond(const int u)
{
	int dist=INF;
	for(const int ei:ET[u])if(ei!=FA[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(DIST[nxt]==-1)continue;
		if(DIST[nxt]+e.cost<dist)dist=DIST[nxt]+e.cost;
	}
	if(dist==INF)return -1;
	return dist;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(2,"%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b,c;i<M;i++)
	{
		scanf(3,"%d%d%d",&a,&b,&c);
		EDGE.push_back(Edge(--a,--b,c));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	Solve();
	for(int i=1;i<N;i++)printf("%d\n",GetSecond(i));
	return 0;
}
