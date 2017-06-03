#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
int SZ[(250000-1)*2];
vector<int>ET[250000];
int GetSZ(const int eoi)
{
	int &ans=SZ[eoi];
	if(ans!=-1)return ans;
	ans=1;
	const Edge &eo=EDGE[eoi/2];
	const int u=(eoi&1?eo.b:eo.a),parent=(eoi&1?eo.a:eo.b);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==parent)continue;
		if(nxt==e.a)ans+=GetSZ(ei*2);
		else ans+=GetSZ(ei*2+1);
	}
	return ans;
}
LL DP[(250000-1)*2];
LL GetDP(const int eoi)
{
	LL &ans=DP[eoi];
	if(ans!=-1LL)return ans;
	ans=0LL;
	const Edge &eo=EDGE[eoi/2];
	const int u=(eoi&1?eo.b:eo.a),parent=(eoi&1?eo.a:eo.b);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==parent)continue;
		if(nxt==e.a)ans+=GetDP(ei*2)+GetSZ(ei*2);
		else ans+=GetDP(ei*2+1)+GetSZ(ei*2+1);
	}
	return ans;
} 
void AddItems(bool *vis,const int n,const int weight,const int count)
{
	static int last[250000];
	for(int i=0;i<weight;i++)last[i]=-INF;
	for(int i=0;i<=n;i++)
	{
		if(vis[i])last[i%weight]=i;
		else if(last[i%weight]>=i-weight*count)vis[i]=true;
	}
}
int N;
int Solve(const int *cnt)
{
	const int bound=(N-1)/2;
	bool *vis=new bool[bound+1];
	for(int i=bound;i>=0;i--)vis[i]=false;
	vis[0]=true;
	for(int i=1;i<N;i++)if(cnt[i])AddItems(vis,bound,i,cnt[i]);
	for(int i=bound;;i--)if(vis[i]){delete[]vis;return i;}
	assert(0);return -1;
}
LL Solve(const int u)
{
	LL ans=0LL;
	static int cnt[250000];
	for(int i=1;i<N;i++)cnt[i]=0;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==e.a)ans+=GetDP(ei*2),cnt[GetSZ(ei*2)]++;
		else ans+=GetDP(ei*2+1),cnt[GetSZ(ei*2+1)]++;
	}
	const LL half=Solve(cnt);
	ans+=half*(N-1LL-half)+half+(N-1LL-half);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
			SZ[i*2]=SZ[i*2+1]=-1;
			DP[i*2]=DP[i*2+1]=-1LL;
		}
		vector<int>wp;
		for(int u=0;u<N;u++)
		{
			int mx=0;
			for(int i=0;i<(int)ET[u].size();i++)
			{
				const int ei=ET[u][i];
				const Edge &e=EDGE[ei];
				const int nxt=(u==e.a?e.b:e.a);
				getmax(mx,GetSZ(nxt==e.a?ei*2:ei*2+1));
			}
			if(mx*2<=N)wp.push_back(u);
		}
		assert(!wp.empty());
		LL ans=0LL;
		for(int i=0;i<(int)wp.size();i++)
		{
			const LL ta=Solve(wp[i]);
			if(ta>ans)ans=ta;
		}
		printf("%d %lld\n",N-1,ans);
		break;
	}
	return 0;
}
