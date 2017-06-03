#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,cost;
	bool intree;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c),intree(false){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int N,M;
struct Pq
{
	int u,pre,cost;
	Pq(){}
	Pq(const int _u,const int _p,const int _c):u(_u),pre(_p),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int DIST[100000];
void BuildTree()
{
	for(int i=0;i<N;i++)DIST[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(0,-1,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]!=INF){assert(p.cost>DIST[p.u]);continue;}
		DIST[p.u]=p.cost;
		if(p.pre!=-1)EDGE[p.pre].intree=true;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(e.a==p.u?e.b:e.a);
			pq.push(Pq(nxt,ei,p.cost+e.cost));
		}
	}
}
int ANS[100000];
void getmin(int &a,const int b){if(b<a)a=b;}
int Dfs(const int u,const int fa)
{
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		int update=-1;
		if(e.intree)update=Dfs(nxt,ei);
		else update=DIST[nxt];
		if(update!=INF)getmin(ANS[u],e.cost+update);
	}
	return ANS[u];
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
			assert(scanf("%d%d%d",&a,&b,&c)==3);
			EDGE.push_back(Edge(--a,--b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		BuildTree();
		for(int i=0;i<N;i++)ANS[i]=INF;//,printf("dist[%d]=%d\n",i,DIST[i]);
		Dfs(0,-1);
		for(int i=1;i<N;i++)printf("%d\n",ANS[i]==INF?-1:ANS[i]);
	}
	return 0;
}
