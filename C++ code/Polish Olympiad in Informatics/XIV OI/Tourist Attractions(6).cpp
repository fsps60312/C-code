#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
int HEAD[20003],NEXT[400003],VAL[400003],EDGE_LENGTH[400003],NSZ;
inline void AddEdge(const int a,const int b,const int l)
{
	VAL[NSZ]=b;
	EDGE_LENGTH[NSZ]=l;
	NEXT[NSZ]=HEAD[a];
	HEAD[a]=NSZ;
	++NSZ;
}
int N,M,K;
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
		for(int cur=HEAD[p.U];cur!=-1;cur=NEXT[cur])
		{
			const int nxt=VAL[cur],nxt_dist=p.DIST+EDGE_LENGTH[cur];
			if(nxt_dist<dist[nxt])q.push(Pq(nxt,dist[nxt]=nxt_dist));
		}
	}
}
int DIST[23][23],FROM[23],ONTO[23];
int BuildDIST()
{
	static int dist[20003];
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
int MUST[23],CANT[23],DP[20*(1<<19)+1];
vector<bool>VIS;
int ALL[23];
inline int Id(const int u,const int s){return (s&ALL[u])|(s>>u>>1<<u);}
int LOSTBIT[(1<<20)+1];
int Solve()
{
	if(K==0)return BuildDIST();
	BuildDIST();
//	assert(0);
	const int k1=K-1;
	for(int i=0;i<K;i++)
	{
		for(int j=0;j<(1<<(K-1));j++)DP[(i<<k1)|j]=INF;
	}
	VIS.clear(),VIS.resize((K<<k1),false);
	queue<int>q;
	for(int u=0;u<K;u++)if(!((MUST[u]&(~(1<<u)))||(CANT[u]&(1<<u))))
	{
		q.push((u<<K)|(1<<u));
		DP[u<<k1]=FROM[u];
		VIS[u<<k1]=true;
	}
	while(!q.empty())
	{
		const int qfront=q.front();q.pop();
		const int u=qfront>>K,s=qfront&ALL[K];
		const int id=Id(u,s);
		const int dp=DP[(u<<k1)|id];
		const int *dist=DIST[u];
		for(int cur=s,nxt;(nxt=LOSTBIT[cur])!=INF;)
		{
			cur|=1<<nxt;
			const int nxt_id=Id(nxt,s|(1<<nxt));
			if(!((MUST[u]&(~s))||(CANT[u]&s)))
			{
				const int nxtloc=(nxt<<k1)|nxt_id;
				getmin(DP[nxtloc],dp+dist[nxt]);
				if(!VIS[nxtloc])q.push((nxt<<K)|s|(1<<nxt)),VIS[nxtloc]=true;
			}
		}
	}
	int ans=INF;
	for(int i=0;i<K;i++)if(DP[(i<<k1)|ALL[K-1]]!=INF)getmin(ans,DP[(i<<k1)|ALL[K-1]]+ONTO[i]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)HEAD[i]=-1;
		NSZ=0;
		for(int i=0,a,b,l;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&l),--a,--b;
			AddEdge(a,b,l);
			AddEdge(b,a,l);
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
		for(int i=0;i<=K;i++)ALL[i]=(1<<i)-1;
		printf("%d\n",Solve());
	}
	return 0;
}
