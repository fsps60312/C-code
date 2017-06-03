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
LL DIST[100000];
int A[100000],B[100000];
bool INQ[100000];
LL DistToA(const int u){assert(A[u]>=0&&A[u]<M&&DIST[EDGE[A[u]].To(u)]!=INF);return EDGE[A[u]].cost+DIST[EDGE[A[u]].To(u)];}
LL DistToB(const int u){assert(B[u]>=0&&B[u]<M&&DIST[EDGE[B[u]].To(u)]!=INF);return EDGE[B[u]].cost+DIST[EDGE[B[u]].To(u)];}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear(),DIST[i]=INF,A[i]=B[i]=-1,INQ[i]=false;
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			static LL c;
			scanf("%d%d%lld",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		queue<int>q;
		for(int i=0,u;i<K;i++)
		{
			scanf("%d",&u);
			DIST[u]=0LL;q.push(u),INQ[u]=true;
		}
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			INQ[u]=false;
			for(int i=0;i<ET[u].size();i++)
			{
				const Edge &e=EDGE[ET[u][i]];
				const int nxt=e.To(u);
				if(A[nxt]==-1||DistToA(nxt)>e.cost+DIST[u])B[nxt]=A[nxt],A[nxt]=ET[u][i];
				else if(B[nxt]==-1||DistToB(nxt)>e.cost+DIST[u])B[nxt]=ET[u][i];
				if(A[nxt]!=-1&&B[nxt]!=-1)
				{
					assert(DistToA(nxt)<=DistToB(nxt)&&A[nxt]!=B[nxt]);
					if(DistToB(nxt)<DIST[nxt])
					{
						DIST[nxt]=DistToB(nxt);
						if(!INQ[nxt])q.push(nxt),INQ[nxt]=true;
					}
				}
			}
		}
		assert(DIST[0]!=INF);
		printf("%lld\n",DIST[0]);
//		break;
	}
	return 0;
}
