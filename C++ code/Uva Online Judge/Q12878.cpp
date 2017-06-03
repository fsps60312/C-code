#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[10000];
int DT[10000],DF[10000];
bool INQ[10000],VIS[10000];
void Bfs(const int source,int *dist)
{
	for(int i=0;i<N;i++)dist[i]=INF;
	queue<int>q;
	q.push(source);dist[source]=0;INQ[source]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=EDGE[ET[u][i]];
			const int nxt=(u==e.a?e.b:e.a);
			if(dist[u]+e.cost<dist[nxt])
			{
				dist[nxt]=dist[u]+e.cost;
				if(!INQ[nxt])q.push(nxt),INQ[nxt]=true;
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),INQ[i]=false;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i);
			ET[b].push_back(i);
		}
		Bfs(0,DT),Bfs(N-1,DF);
		const int all=DF[0];
		int ans=0;
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			if(DT[e.a]+e.cost+DF[e.b]==all||DT[e.b]+e.cost+DF[e.a]==all)ans+=e.cost;
		}
		printf("%d\n",ans*2);
	}
	return 0;
}
