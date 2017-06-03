#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,flow,limit;
	Edge(){}
	Edge(const int _a,const int _b,const int _flow,const int _limit):a(_a),b(_b),flow(_flow),limit(_limit){}
};
vector<Edge>EDGE;
vector<int>ET[1802];
void AddEdge(const int a,const int b,const int limit)
{
	const int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,0,limit));
	EDGE.push_back(Edge(b,a,limit,limit));
	ET[a].push_back(sz);
	ET[b].push_back(sz+1);
}
int FLOOR[1802];
bool Bfs(const int source,const int target)
{
	for(int i=0;i<1802;i++)FLOOR[i]=INF;
	queue<int>q;
	q.push(source);
	FLOOR[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int &ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			if(FLOOR[e.b]!=INF||e.flow==e.limit)continue;
			FLOOR[e.b]=FLOOR[u]+1;
			q.push(e.b);
		}
	}
//	printf("dist=%d\n",FLOOR[target]);
	return FLOOR[target]!=INF;
}
int Dfs(const int u,const int target,int supply)
{
	if(!supply||u==target)return supply;
	int ans=0;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(FLOOR[u]+1==FLOOR[e.b]&&e.flow<e.limit)
		{
			const int flow=Dfs(e.b,target,min(supply,e.limit-e.flow));
			supply-=flow;
			ans+=flow;
			EDGE[ei].flow+=flow;
			EDGE[ei^1].flow-=flow;
			if(!supply)break;
		}
	}
	return ans;
}
int MaxFlow(const int source,const int target)
{
	int flow=0;
	while(Bfs(source,target))flow+=Dfs(source,target,INF);
	return flow;
}
int R,C,P;
char GRID[30][31];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&R,&C,&P)==3)
	{
		for(int i=0;i<R*C*2+2;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<R;i++)scanf("%s",GRID[i]);
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)
		{
			const int loc=i*C+j;
			switch(GRID[i][j])
			{
				case'*':AddEdge(R*C+R*C,R*C+loc,1);break;
				case'~':break;
				case'.':AddEdge(loc,R*C+loc,1);break;
				case'@':AddEdge(loc,R*C+loc,INF);break;
				case'#':AddEdge(loc,R*C+R*C+1,P),AddEdge(loc,R*C+loc,INF);break;
				default:assert(0);break;
			}
		}
		for(int i=1;i<R;i++)for(int j=0;j<C;j++)
		{
			AddEdge(R*C+(i*C+j),(i-1)*C+j,INF);
			AddEdge(R*C+((i-1)*C+j),i*C+j,INF);
		}
		for(int i=0;i<R;i++)for(int j=1;j<C;j++)
		{
			AddEdge(R*C+(i*C+j),i*C+(j-1),INF);
			AddEdge(R*C+(i*C+(j-1)),i*C+j,INF);
		}
		printf("%d\n",MaxFlow(R*C+R*C,R*C+R*C+1));
	}
	return 0;
}
