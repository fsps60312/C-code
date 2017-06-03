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
int MUST[23],CANT[23],DP[2][184756*20+1];
int ALL[23];
int LOSTBIT[(1<<20)+1];
bool VALID[184756*20+1];
inline bool Valid(const int &u,const int &s){return !((MUST[u]&(~s))||(CANT[u]&s));}
int Solve()
{
	if(K==0)return BuildDIST();
	BuildDIST();
	static vector<int>sets[21];
	for(int i=0;i<=K;i++)sets[i].clear();
	static int id[1<<20];
	for(int s=1;s<(1<<K);s++)
	{
		int cnt=0;
		for(int i=0;i<K;i++)if(s&(1<<i))++cnt;
		id[s]=(int)sets[cnt].size();
		sets[cnt].push_back(s);
	}
	assert((int)sets[1].size()==K);
	for(int i=0;i<K*K;i++)DP[0][i]=INF;
	for(int u=0;u<K;u++)if(Valid(u,1<<u))DP[0][u*K+id[1<<u]]=FROM[u];
	int d=0;
	for(int depth=1;depth<K;depth++,d^=1)
	{
		const vector<int>&now_set=sets[depth],&nxt_set=sets[depth+1];
		const int *now_dp=DP[d];
		int *nxt_dp=DP[d^1];
		const int m=(int)nxt_set.size();
		for(int u=0,loc=0;u<K;u++)for(int idx=0;idx<m;idx++,loc++)
		{
			nxt_dp[loc]=INF;
			VALID[loc]=Valid(u,nxt_set[idx]);
		}
		const int n=(int)now_set.size();
		for(int u=0,now_loc=0;u<K;u++)
		{
			const int *dist=DIST[u];
			for(int idx=0;idx<n;idx++,now_loc++)if(now_dp[now_loc]!=INF)
			{
//				assert(Valid(u,now_set[idx]));
				const int dp=now_dp[now_loc];
				const int s=now_set[idx];
				for(int cur=s,nxt;(nxt=LOSTBIT[cur])!=INF;)
				{
					cur|=1<<nxt;
					const int nxt_loc=nxt*m+id[s|(1<<nxt)];
					if(VALID[nxt_loc])getmin(nxt_dp[nxt_loc],dp+dist[nxt]);
				}
			}
		}
	}
	assert((int)sets[K].size()==1);
	int ans=INF;
	for(int i=0;i<K;i++)if(DP[d][i]!=INF)getmin(ans,DP[d][i]+ONTO[i]);
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
