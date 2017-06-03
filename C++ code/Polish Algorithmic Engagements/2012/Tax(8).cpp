#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	LL cost;
	Edge(){}
	Edge(const int _a,const int _b,const LL &_cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
struct Pq
{
	int ei;
	LL cost;
	Pq():ei(),cost(){}
	Pq(const int _ei,const LL &_cost):ei(_ei),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int N,M;
vector<int>ET[100000];
bool CmpEdgeIdx(const int a,const int b){return EDGE[a].cost!=EDGE[b].cost?EDGE[a].cost<EDGE[b].cost:a<b;}
LL Solve()
{
	static bool vis[400000];
	static LL dist[400000];
	for(int i=0;i<M*2;i++)vis[i]=false,dist[i]=INF;
	priority_queue<Pq>pq;
	for(int i=0;i<(int)ET[0].size();i++)pq.push(Pq(ET[0][i],EDGE[ET[0][i]].cost));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(vis[p.ei])continue;
		vis[p.ei]=true;
		const Edge &e=EDGE[p.ei];
		if(e.a==N-1)return p.cost;
		for(int i=0;i<(int)ET[e.b].size();i++)
		{
			const int ei=ET[e.b][i];
			const Edge &nxte=EDGE[ei];
			const LL cost=p.cost+max(e.cost,nxte.cost);
			if(cost>=dist[ei])break;
			dist[ei]=cost;
			pq.push(Pq(ei,cost));
		}
	}
	assert(0);return -1LL;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			EDGE.push_back(Edge(a,b,c));
			EDGE.push_back(Edge(b,a,c));
			ET[a].push_back(i*2),ET[b].push_back(i*2+1);
		}
		for(int i=0;i<N;i++)sort(ET[i].begin(),ET[i].end(),CmpEdgeIdx);
		printf("%lld\n",Solve());
	}
	return 0;
}
