#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
struct Edge
{
	int A,B,DIST;
	Edge(const int _A,const int _B,const int _DIST):A(_A),B(_B),DIST(_DIST){}
};
vector<Edge>EDGE;
int N,M,K;
vector<int>ET[20000];
struct Pq
{
	int U,DIST;
	Pq(){}
	Pq(const int _U,const int _DIST):U(_U),DIST(_DIST){}
};
bool operator<(const Pq &a,const Pq &b){return a.DIST>b.DIST;}
void Bfs(const int start,int *dist)
{
	for(int i=0;i<N;i++)dist[i]=INF;
	priority_queue<Pq>q;q.push(Pq(start,0));
	while(!q.empty())
	{
		const Pq p=q.top();q.pop();
		if(p.DIST>=dist[p.U])continue;
		dist[p.U]=p.DIST;
		for(int i=0;i<(int)ET[p.U].size();i++)
		{
			const Edge &e=EDGE[ET[p.U][i]];
			const int nxt=(p.U==e.A?e.B:e.A);
			q.push(Pq(nxt,p.DIST+e.DIST));
		}
	}
}
int DIST[20][20],FROM[20],ONTO[20];
int BuildDIST()
{
	static int dist[20000];
	for(int u=1;u<=K;u++)
	{
		Bfs(u,dist);
		for(int nxt=1;nxt<=K;nxt++)DIST[u-1][nxt-1]=dist[nxt];
	}
	Bfs(0,dist);
	for(int nxt=1;nxt<=K;nxt++)FROM[nxt-1]=dist[nxt];
	Bfs(N-1,dist);
	for(int nxt=1;nxt<=K;nxt++)ONTO[nxt-1]=dist[nxt];
	return dist[0];
}
int MUST[20],CANT[20],DP[20][1<<19];
inline int Add(const int a,const int b)
{
	if(a==INF||b==INF)return INF;
	return a+b;
}
int GetDP(const int u,const int s)
{
	int &dp=DP[u][(s&((1<<u)-1))|((s&(~((1<<(u+1))-1)))>>1)];
	if(dp!=-1)return dp;
	assert(s&(1<<u));
//	if(MUST[u]&CANT[u])return dp=INF;
	if(MUST[u]&(~s))return dp=INF;
	if(CANT[u]&s)return dp=INF;
	if(s==(1<<u))return dp=FROM[u];
	dp=INF;
	for(int pre=0;pre<K;pre++)if(pre!=u&&(s&(1<<pre)))
	{
		getmin(dp,Add(GetDP(pre,s-(1<<u)),DIST[pre][u]));
	}
	return dp;
}
int Solve()
{
	if(K==0)return BuildDIST();
	BuildDIST();
	for(int i=0;i<K;i++)for(int j=0;j<(1<<(K-1));j++)DP[i][j]=-1;
	int ans=INF;
	for(int i=0;i<K;i++)getmin(ans,Add(GetDP(i,(1<<K)-1),ONTO[i]));
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,l;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&l),--a,--b;
			EDGE.push_back(Edge(a,b,l));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<K;i++)MUST[i]=CANT[i]=0;
		{
			int g;scanf("%d",&g);
			for(int i=0,a,b;i<g;i++)
			{
				scanf("%d%d",&a,&b),a-=2,b-=2;
				MUST[b]|=1<<a;
				CANT[a]|=1<<b;
			}
		}
		printf("%d\n",Solve());
	}
	return 0;
}
