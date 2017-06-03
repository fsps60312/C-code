#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M,K;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
	int To(const int from)const{return from==a?b:a;}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int DIST[100000],A[100000],B[100000];
bool INQ[100000];
int DistToA(const int u){return EDGE[A[u]].cost+DIST[EDGE[A[u]].To(u)];}
int DistToB(const int u){return EDGE[B[u]].cost+DIST[EDGE[B[u]].To(u)];}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear(),DIST[i]=INF,A[i]=B[i]=-1,INQ[i]=false;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		queue<int>q;
		for(int i=0,u;i<K;i++)
		{
			scanf("%d",&u);
			DIST[u]=0;q.push(u),INQ[u]=true;
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
				if(A[nxt]!=-1&&B[nxt]!=-1&&max(DistToA(nxt),DistToB(nxt))<DIST[nxt])
				{
					DIST[nxt]=max(DistToA(nxt),DistToB(nxt));
					if(!INQ[nxt])q.push(nxt),INQ[nxt]=true;
				}
			}
		}
		printf("%d\n",DIST[0]);
	}
	return 0;
}
