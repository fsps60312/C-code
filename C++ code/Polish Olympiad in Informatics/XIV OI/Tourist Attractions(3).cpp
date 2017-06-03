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
vector<bool>VIS[20];
inline int Id(const int u,const int s){return (s&((1<<u)-1))|((s&(~((1<<(u+1))-1)))>>1);}
int Solve()
{
	if(K==0)return BuildDIST();
	BuildDIST();
	for(int i=0;i<N;i++)vector<int>().swap(ET[i]);
	vector<Edge>().swap(EDGE);
	for(int i=0;i<K;i++)
	{
		for(int j=0;j<(1<<(K-1));j++)DP[i][j]=INF;
		VIS[i].clear(),VIS[i].resize(1<<(K-1),false);
	}
	queue<int>q;
	for(int u=0;u<K;u++)if(!((MUST[u]&(~(1<<u)))||(CANT[u]&(1<<u))))
	{
		q.push(u),q.push(1<<u);
		DP[u][0]=FROM[u];
		VIS[u][0]=true;
	}
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		const int s=q.front();q.pop();
		const int id=Id(u,s);
		const int &dp=DP[u][id];
//		assert(s&(1<<u));
//		assert(VIS[u][id]);
		for(int nxt=0;nxt<K;nxt++)if(!(s&(1<<nxt)))
		{
			const int nxt_id=Id(nxt,s|(1<<nxt));
			if(!((MUST[u]&(~s))||(CANT[u]&s)))
			{
				getmin(DP[nxt][nxt_id],Add(dp,DIST[u][nxt]));
				if(!VIS[nxt][nxt_id])q.push(nxt),q.push(s|(1<<nxt)),VIS[nxt][nxt_id]=true;
			}
		}
	}
	int ans=INF;
	for(int i=0;i<K;i++)getmin(ans,Add(DP[i][(1<<(K-1))-1],ONTO[i]));
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
