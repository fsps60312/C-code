#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(a<b)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
int N,M,ORDER[500002];
void Bfs(const vector<int>*es,int *dist)
{
	static int degree[500002];
	for(int i=0;i<N+2;i++)degree[i]=0;
	for(int i=0;i<N+2;i++)for(int j=0;j<(int)es[i].size();j++)
	{
		const Edge &e=EDGE[es[i][j]];
		const int nxt=(i==e.a?e.b:e.a);
		++degree[nxt];
	}
	queue<int>q;
	for(int i=0;i<N+2;i++)if(degree[i]==0)dist[i]=0,q.push(i);
	assert((int)q.size()==1);
	int cur=0;
	while(!q.empty())
	{
		const int u=ORDER[cur++]=q.front();q.pop();
//		printf("dist[%d]=%d\n",u,dist[u]);
		assert(degree[u]==0);
		for(int i=0;i<(int)es[u].size();i++)
		{
			const Edge &e=EDGE[es[u][i]];
			const int nxt=(u==e.a?e.b:e.a);
			dist[nxt]=dist[u]+1;
			if(!--degree[nxt])q.push(nxt);
		}
	}
//	puts("done");
//	printf("cur=%d,N+2=%d\n",cur,N+2);
	assert(cur==N+2);
}
vector<int>ET[500002],EF[500002];
void AddEdge(const int a,const int b)
{
	const int sz=(int)EDGE.size();
	EDGE.push_back(Edge(a,b));
	ET[a].push_back(sz),EF[b].push_back(sz);
}
int DT[500002],DF[500002];
//struct CmpEdge{bool operator()(const int a,const int b)const
//{
//	const int ca=EDGE[a].cost,cb=EDGE[b].cost;
//	return ca!=cb?ca>cb:a<b;
//}};
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N+2;i++)ET[i].clear(),EF[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			AddEdge(a,b);
		}
		for(int i=0;i<N;i++)AddEdge(N,i),AddEdge(i,N+1);
		Bfs(EF,DT),Bfs(ET,DF);
		for(int i=0;i<(int)EDGE.size();i++)
		{
			Edge &e=EDGE[i];
			e.cost=DF[e.a]+DT[e.b];
//			printf("Edge(%d,%d)=(%d,%d)\n",e.a+1,e.b+1,DF[e.a],DT[e.b]);
		}
		multiset<int,greater<int> >midedges;
		int uppoints=0;
		multiset<int,greater<int> >downpoints;
		for(int i=0;i<N+2;i++)downpoints.insert(DT[i]);
		int ans_dist=INF,ans_u=-1;
		for(int _u=0;_u<N+2;_u++)
		{
			const int u=ORDER[_u];
			for(int i=0;i<(int)EF[u].size();i++)midedges.erase(midedges.find(EDGE[EF[u][i]].cost));
			downpoints.erase(downpoints.find(DT[u]));
			if(u<N)
			{
				const int ta=max(midedges.empty()?0:*midedges.begin(),max(uppoints,*downpoints.begin()));
//				printf("u=%d,ta=%d\n",u+1,ta);
				if(ta<ans_dist)ans_dist=ta,ans_u=u;
			}
			for(int i=0;i<(int)ET[u].size();i++)midedges.insert(EDGE[ET[u][i]].cost);
			getmax(uppoints,DF[u]);
		}
		printf("%d %d\n",ans_u+1,ans_dist-1);
		assert(midedges.empty()),assert(downpoints.empty());
	}
	return 0;
}
