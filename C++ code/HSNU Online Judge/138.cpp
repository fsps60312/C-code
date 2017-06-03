#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[50000];
int N,M;
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int Solve()
{
	static bool vis[50000];
	for(int i=0;i<N;i++)vis[i]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(vis[p.u])continue;
		vis[p.u]=true;
		if(p.u==N-1)return p.cost;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(e.a==p.u?e.b:e.a);
			pq.push(Pq(nxt,p.cost+e.cost));
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0;i<M;i++)
	{
		static int a,b,c;scanf("%d%d%d",&a,&b,&c),a--,b--;
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(i);//,ET[b].push_back(i);
	}
	printf("%d\n",Solve());
	return 0;
}
