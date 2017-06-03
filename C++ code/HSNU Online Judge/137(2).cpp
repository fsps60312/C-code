#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
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
int DIST[100000];
set<int>TYPE[100000];
struct Pq
{
	int u,type,cost;
	Pq(){}
	Pq(const int _u,const int _t,const int _c):u(_u),type(_t),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
void Solve()
{
	for(int i=1;i<N;i++)DIST[i]=-1,TYPE[i].clear();
	priority_queue<Pq>pq;
	for(const int ei:ET[0])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==0?e.b:e.a);
		pq.push(Pq(nxt,ei,e.cost));
	}
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(TYPE[p.u].find(p.type)!=TYPE[p.u].end())continue;
		TYPE[p.u].insert(p.type);
		if((int)TYPE[p.u].size()==2)DIST[p.u]=p.cost;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(p.u==e.a?e.b:e.a);
			pq.push(Pq(nxt,ei,p.cost+e.cost));
		}
	}
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
	for(int i=1;i<N;i++)printf("%d\n",DIST[i]);
	return 0;
}
