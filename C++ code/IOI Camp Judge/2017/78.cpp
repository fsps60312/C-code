#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
typedef long long LL;
const int MAX_N=10000,INF=2147483647;
struct Edge
{
	int a,b;
	LL c;
	Edge(){}
	Edge(const int _a,const int _b,const LL _c):a(_a),b(_b),c(_c){}
};
int N,M,K,LOC[MAX_N];
vector<Edge>EDGE;
vector<int>ET[MAX_N];
namespace QDist
{
	int DEPTH[MAX_N];
	vector<int>PA[MAX_N];
	LL DIST[MAX_N];
	void Dfs(const int u,const int pa,const LL dist,const int depth)
	{
		DIST[u]=dist;
		DEPTH[u]=depth;
		PA[u].clear();
		if(pa!=-1)
		{
			for(int cur=pa,i=0;;cur=PA[cur][i++])
			{
				PA[u].push_back(cur);
				if(i>=(int)PA[cur].size())break;
			}
		}
		for(const int i:ET[u])
		{
			const Edge &e=EDGE[i];
			const int nxt=(u==e.a?e.b:e.a);
			if(nxt==pa)continue;
			Dfs(nxt,u,dist+e.c,depth+1);
		}
	}
	int QueryLCA(int a,int b)
	{
		if(DEPTH[a]<DEPTH[b])swap(a,b);
		assert(DEPTH[a]>=DEPTH[b]);
		for(int dis=DEPTH[a]-DEPTH[b],i=0;(1<<i)<=dis;i++)if(dis&(1<<i))a=PA[a][i];
		assert(DEPTH[a]==DEPTH[b]);
		if(a==b)return a;
		for(int i=30;i>=0;i--)if(i<(int)PA[a].size()&&PA[a][i]!=PA[b][i])a=PA[a][i],b=PA[b][i];
		assert(PA[a][0]==PA[b][0]);
		return PA[a][0];
	}
	LL Get(const int a,const int b)
	{
		return DIST[a]+DIST[b]-2*DIST[QueryLCA(a,b)];
	}
	void Build()
	{
		Dfs(0,-1,0,0);
	}
};
namespace CMPart
{
	bool VIS[MAX_N];
	int PA[MAX_N],CNT[MAX_N];
	LL ANS[MAX_N];
	int DfsGetCM(const int u,const int pa,int &ansu,int &ansn,const int n)
	{
		if(VIS[u])return 0;
		int ans=1;
		int pasz=n-1,mxsz=0;
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(u==e.a?e.b:e.a);
			if(nxt==pa)continue;
			const int chsz=DfsGetCM(nxt,u,ansu,ansn,n);
			ans+=chsz;
			getmax(mxsz,chsz);
			pasz-=chsz;
		}
		getmax(mxsz,pasz);
		if(n>0&&mxsz<ansn)ansn=mxsz,ansu=u;
		return ans;
	}
	int GetCM(const int u)
	{
		int ansu=-1,ansn=INF;
		const int n=DfsGetCM(u,-1,ansu,ansn,0);
		assert(n>0);
		assert(DfsGetCM(u,-1,ansu,ansn,n)==n);
		assert(ansu!=-1&&ansn<=n/2);
		return ansu;
	}
	void DfsBuild(const int u,const int pa)
	{
		assert(!VIS[u]);
		VIS[u]=true;
		PA[u]=pa;
		for(const int ei:ET[u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(u==e.a?e.b:e.a);
			if(!VIS[nxt])DfsBuild(nxt,u);
		}
	}
	void Build()
	{
		for(int i=0;i<N;i++)VIS[i]=false;
		DfsBuild(GetCM(0),-1);
		QDist::Build();
		for(int i=0;i<N;i++)CNT[i]=0,ANS[i]=0;
	}
	LL Get(const int u)
	{
		LL ans=ANS[u];
		for(int cur=PA[u],pre=u;cur!=-1;cur=PA[cur])
		{
			ans+=(ANS[cur]-ANS[pre]-CNT[pre]*QDist::Get(cur,pre))+(CNT[cur]-CNT[pre])*QDist::Get(cur,u);
		}
		return ans;
	}
	void Update(const int u,const int cnt)
	{
		for(int cur=u;cur!=-1;cur=PA[cur])CNT[cur]+=cnt,ANS[cur]+=cnt*QDist::Get(u,cur);
	}
};
int main()
{
	freopen("data.in","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&M,&K);
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<N-1;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i);
			ET[b].push_back(i);
		}
		CMPart::Build();
		for(int i=0;i<M;i++)LOC[i]=0;
		CMPart::Update(0,M);
		for(int i=0,s,x;i<K;i++)
		{
			scanf("%d%d",&s,&x),--s,--x;
			CMPart::Update(LOC[s],-1);
			LOC[s]=x;
			CMPart::Update(LOC[s],1);
			printf("%lld\n",CMPart::Get(LOC[0]));
		}
//		for(int i=0;i<M;i++)CMPart::Update(LOC[i],-1);
//		for(int i=0;i<N;i++)assert(CMPart::Get(i)==0);
	}
	return 0;
}
