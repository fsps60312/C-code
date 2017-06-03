#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N,M;
LL W[50000];
struct Edge
{
	int a,b;
	LL cost;
	Edge(){}
	Edge(const int &_a,const int &_b,const LL &_c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[50000];
LL DIST[50000];
bool INQ[50000];
LL Solve()
{
	for(int i=0;i<N;i++)DIST[i]=INF,INQ[i]=false;
	DIST[0]=0;
	queue<int>q;
	q.push(0);
	INQ[0]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=EDGE[ET[u][i]];
			const int &nxt=(e.a==u?e.b:e.a);
			if(DIST[u]+e.cost<DIST[nxt])
			{
				DIST[nxt]=DIST[u]+e.cost;
				if(!INQ[nxt])
				{
					q.push(nxt);
					INQ[nxt]=true;
				}
			}
		}
	}
	LL ans=0LL;
	for(int i=1;i<N;i++)
	{
		if(DIST[i]==INF)return INF;
		ans+=DIST[i]*W[i];
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<N;i++)scanf("%lld",&W[i]);
		for(int i=0;i<M;i++)
		{
			static int a,b;
			static LL c;
			scanf("%d%d%lld",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i);
			ET[b].push_back(i);
		}
		LL ans=Solve();
		if(ans==INF)puts("No Answer");
		else printf("%lld\n",ans);
	}
	return 0;
}
