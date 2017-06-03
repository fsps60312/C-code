#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N,M,K;
struct Edge
{
	int a,b;
	LL cost;
	Edge(){}
	Edge(const int _a,const int _b,const LL _c):a(_a),b(_b),cost(_c){}
	int To(const int from)const{return from==a?b:a;}
};
vector<Edge>EDGE;
vector<int>ET[100000];
LL D1[100000],D2[100000];
struct Pq
{
	int u;
	LL cost;
	Pq(){}
	Pq(const int _u,const LL _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear(),D1[i]=D2[i]=INF;
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			static LL c;
			scanf("%d%d%lld",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		priority_queue<Pq>pq;
		for(int i=0,u;i<K;i++)
		{
			scanf("%d",&u);
			pq.push(Pq(u,0LL)),pq.push(Pq(u,0LL));
		}
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(D1[p.u]==INF)D1[p.u]=p.cost;
			else if(D2[p.u]==INF)D2[p.u]=p.cost;
			else continue;
			assert(D1[p.u]<=D2[p.u]);
			if(D2[p.u]==INF)continue;
			for(int i=0;i<ET[p.u].size();i++)
			{
				const Edge &e=EDGE[ET[p.u][i]];
				const int nxt=e.To(p.u);
				pq.push(Pq(nxt,D2[p.u]+e.cost));
			}
		}
		assert(D2[0]!=INF);
		printf("%lld\n",D2[0]);
		break;
	}
	return 0;
}
