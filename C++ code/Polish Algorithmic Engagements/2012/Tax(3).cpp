#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
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
int N,M;
vector<int>ET[100000];
LL DIST[400000];
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
		static bool inq[400000];
		for(int i=0;i<M*2;i++)DIST[i]=INF,inq[i]=false;
		queue<int>q;
		for(int i=0;i<(int)ET[0].size();i++)
		{
			q.push(ET[0][i]),getmin(DIST[ET[0][i]],EDGE[ET[0][i]>>1].cost),inq[ET[0][i]]=true;
		}
		LL ans=INF;
		while(!q.empty())
		{
			const int p=q.front();q.pop(),inq[p]=false;
			const Edge &e=EDGE[p>>1];
			const int u=(p&1?e.a:e.b);
			if(u==N-1){getmin(ans,DIST[p]+e.cost);continue;}
			for(int i=0;i<(int)ET[u].size();i++)
			{
				const int ei=ET[u][i];
				const Edge &nxte=EDGE[ei>>1];
				const LL &cost=DIST[p]+max(e.cost,nxte.cost);
				if(cost<DIST[ei])
				{
					DIST[ei]=cost;
					if(!inq[ei])q.push(ei),inq[ei]=true;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
