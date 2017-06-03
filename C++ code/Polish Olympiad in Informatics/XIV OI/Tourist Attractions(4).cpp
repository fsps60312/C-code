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
	priority_queue<Pq>q;q.push(Pq(start,dist[start]=0));
	while(!q.empty())
	{
		const Pq p=q.top();q.pop();
		if(p.DIST>dist[p.U])continue;
		for(int i=0;i<(int)ET[p.U].size();i++)
		{
			const Edge &e=EDGE[ET[p.U][i]];
			const int nxt=(p.U==e.A?e.B:e.A),nxt_dist=p.DIST+e.DIST;
			if(nxt_dist<dist[nxt])q.push(Pq(nxt,dist[nxt]=nxt_dist));
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
vector<bool>VIS[20];
inline int Id(const int u,const int s){return (s&((1<<u)-1))|(s>>(u+1)<<u);}
int LOSTBIT[1<<20];
inline int Add(const int a,const int b)
{
	if(a==INF||b==INF)return INF;
	return a+b;
}
int Solve()
{
	if(K==0)return BuildDIST();
	BuildDIST();
//	assert(0);
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
		q.push((u<<K)|(1<<u));
		DP[u][0]=FROM[u];
		VIS[u][0]=true;
	}
	while(!q.empty())
	{
		const int u=q.front()>>K,s=q.front()&((1<<K)-1);
		q.pop();
		const int id=Id(u,s);
		const int dp=DP[u][id];
		for(int cur=s;;)
		{
			const int nxt=LOSTBIT[cur];
			if(nxt==INF)break;
			cur+=1<<nxt;
			const int nxt_id=Id(nxt,s|(1<<nxt));
			if(!((MUST[u]&(~s))||(CANT[u]&s)))
			{
				getmin(DP[nxt][nxt_id],dp+DIST[u][nxt]);
				if(!VIS[nxt][nxt_id])q.push((nxt<<K)|s|(1<<nxt)),VIS[nxt][nxt_id]=true;
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
		for(int s=0;s<(1<<K);s++)
		{
			LOSTBIT[s]=INF;
			for(int i=0;i<K;i++)if(!(s&(1<<i))){LOSTBIT[s]=i;break;}
		}
		printf("%d\n",Solve());
	}
	return 0;
}
