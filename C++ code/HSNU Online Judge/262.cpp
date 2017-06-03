#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int N,M,K;
struct Edge
{
	int from,to,cost;
	Edge(){}
	Edge(const int _f,const int _t,const int _c):from(_f),to(_t),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int DIST[2000000];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int Solve()
{
	priority_queue<Pq>pq;
	for(auto i:ET[0])pq.push(Pq(i,EDGE[i].cost));
	while(!pq.empty())
	{
		const Pq &p=pq.top();pq.pop();
		const Edge &e=EDGE[p.u];
		for(auto i:ET[e.to])if(i!=(p.u^1))
		{
			
		}
	}
}
int main()
{
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			EDGE.push_back(Edge(b,a,c));
			ET[a].push_back(i*2),ET[b].push_back(i*2+1);
			DIST[i*2]=DIST[i*2+1]=INF;
		}
	}
	return 0;
}
