#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	LL cost;
	Edge(){}
	Edge(const int _a,const int _b,const LL &_cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
int N,M;
vector<int>ET[100000];
LL DIST[400000];
bool VIS[400000];
set<LL>PQ;
void Insert(const LL &ei,const LL &cost)
{
	if(cost>=DIST[ei]||VIS[ei])return;
	PQ.erase(DIST[ei]*(M*2LL)+ei);
	DIST[ei]=cost;
	PQ.insert(cost*(M*2LL)+ei);
	assert((int)PQ.size()<=M*2&&ei<M*2);
}
LL Solve()
{
	for(int i=0;i<M*2;i++)VIS[i]=false,DIST[i]=N*2000000LL;
	PQ.clear();
	for(int i=0;i<(int)ET[0].size();i++)Insert(ET[0][i],EDGE[ET[0][i]>>1].cost);
	while(!PQ.empty())
	{
		const LL u=*PQ.begin();PQ.erase(PQ.begin());
		const int ei=u%(M*2LL);
		const LL &cost=u/(M*2LL);
		assert(!VIS[ei]);
		VIS[ei]=true;
		const Edge &e=EDGE[ei>>1];
		const int to=(ei&1?e.a:e.b);
		if((ei&1?e.b:e.a)==N-1)return cost;
		for(int i=0;i<(int)ET[to].size();i++)
		{
			const int nxtei=ET[to][i];
			const Edge &nxte=EDGE[nxtei>>1];
			Insert(nxtei,cost+max(e.cost,nxte.cost));
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
			ET[a].push_back(i*2),ET[b].push_back(i*2+1);
		}
		printf("%lld\n",Solve());
		break;
	}
	return 0;
}
