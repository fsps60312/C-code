#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
int N,M;
bool VIS[400][400];
vector<int>ET[400];
vector<Edge>EDGE;
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _p,const int _c):u(_u*N+_p),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int Solve(const int source)
{
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)VIS[i][j]=false;
	priority_queue<Pq>pq;
	for(const int ei:ET[source])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==source?e.b:e.a);
		pq.push(Pq(nxt,source,e.cost));
	}
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		const int u=p.u/N,pre=p.u%N;
		if(VIS[u][pre])continue;
		VIS[u][pre]=true;
		if(u==source)return p.cost;
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(e.a==u?e.b:e.a);
			if(nxt==pre)continue;
			pq.push(Pq(nxt,u,p.cost+e.cost));
		}
	}
	return INF;
}
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b,c;i<M;i++)
	{
		scanf("%d%d%d",&a,&b,&c),a--,b--;
		if(a==b){M--,i--;continue;}
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	int ans=INF;
	for(int i=0;i<N;i++)getmin(ans,Solve(i));
	if(ans==INF)puts("No solution.");
	else printf("%d\n",ans);
	return 0;
}
