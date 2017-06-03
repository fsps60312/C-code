#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M,S,T;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<int>ET[1000];
vector<Edge>EDGE;
int DEGREE[1000];
vector<int>ODD;
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
void Bfs(const int source,int *dist)
{
	for(int i=0;i<N;i++)dist[i]=-1;
	priority_queue<Pq>pq;
	pq.push(Pq(source,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(dist[p.u]!=-1)continue;
		dist[p.u]=p.cost;
		for(int i=0;i<ET[p.u].size();i++)
		{
			const Edge &e=EDGE[ET[p.u][i]];
			const int nxt=(p.u==e.a?e.b:e.a);
			if(dist[nxt]==-1)pq.push(Pq(nxt,p.cost+e.cost));
		}
	}
}
int DIST[20][20];
int DP[1<<20];
int GetDP(const int s)
{
	int &dp=DP[s];
	if(dp!=-1)return dp;
	if(s==0)return dp=0;
	int source;
	for(source=0;source<ODD.size();source++)if(s&(1<<source))break;
	assert(source<ODD.size());
	dp=INF;
	for(int nxt=source+1;nxt<ODD.size();nxt++)if(s&(1<<nxt))getmin(dp,DIST[source][nxt]+GetDP(s-(1<<source)-(1<<nxt)));
	assert(dp!=INF);
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&S,&T)==4)
	{
		S--,T--;
		for(int i=0;i<N;i++)ET[i].clear(),DEGREE[i]=0;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
			DEGREE[a]++,DEGREE[b]++;
		}
		ODD.clear();
		for(int i=0;i<N;i++)if(DEGREE[i]&1)ODD.push_back(i);
		assert(ODD.size()<=20&&ODD.size()%2==0);
		long long ans=0LL;
		for(int i=0;i<ODD.size();i++)
		{
			static int dist[1000];
			Bfs(ODD[i],dist);
			for(int j=i;j<ODD.size();j++)
			{
				DIST[i][j]=DIST[j][i]=dist[ODD[j]];
				if((ODD[i]==S&&ODD[j]==T)||(ODD[j]==S&&ODD[i]==T))assert(ans==0LL),ans=-dist[j];
			}
		}
		if(ans==0LL)
		{
			static int dist[1000];
			Bfs(S,dist);
			ans+=dist[T];
		}
		for(int i=0,limit=(1<<ODD.size());i<limit;i++)DP[i]=-1;
		ans+=GetDP((1<<ODD.size())-1);
		for(const auto &e:EDGE)ans+=e.cost;
		printf("%lld\n",ans);
	}
	return 0;
}
