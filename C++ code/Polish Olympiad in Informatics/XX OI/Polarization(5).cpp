#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const int INF=2147483647,MAXIMUM_OF_M=(250000-1)*2;
void getmax(int &a,const int b){if(b>a)a=b;}
int HEAD[250000],NEXT[MAXIMUM_OF_M],ET[MAXIMUM_OF_M],SZ[MAXIMUM_OF_M],NSZ;
LL DP[MAXIMUM_OF_M];
void AddEdge(const int a,const int b)
{
	ET[NSZ]=b;
	SZ[NSZ]=-1,DP[NSZ]=-1LL;
	NEXT[NSZ]=HEAD[a];
	HEAD[a]=NSZ++;
}
int GetSZ(const int u,const int parent,int &ans)
{
	if(ans!=-1)return ans;
	ans=1;
	for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(ET[cur]!=parent)
	{
//				static int cnt=0;
//				if(cnt++%100000==0)printf("cnt=%d\n",cnt);
		ans+=GetSZ(ET[cur],u,SZ[cur]);
	}
	return ans;
}
LL GetDP(const int u,const int parent,LL &ans)
{
	if(ans!=-1LL)return ans;
	ans=0LL;
	for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(ET[cur]!=parent)
	{
		ans+=GetDP(ET[cur],u,DP[cur])+GetSZ(ET[cur],u,SZ[cur]);
	}
	return ans;
}
#include<bitset>
void AddItems(bitset<250000>&vis,const int weight,const int count)
{
	int remain=count;
	for(int cnt=1;cnt<=remain;cnt<<=1)vis|=vis<<(cnt*weight),remain-=cnt;
	vis|=vis<<(remain*weight);
}
int N;
int Solve(const int *cnt)
{
	const int bound=(N-1)/2;
	static bitset<250000>vis;
	vis=0LL;
	vis[0]=true;
	for(int i=1;i<N;i++)if(cnt[i])AddItems(vis,i,cnt[i]);
	for(int i=bound;;i--)if(vis[i])return i;
	assert(0);return -1;
}
LL Solve(const int u)
{
	LL ans=0LL;
	static int cnt[250000];
	for(int i=1;i<N;i++)cnt[i]=0;
	for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])
	{
		ans+=GetDP(ET[cur],u,DP[cur]);
		cnt[GetSZ(ET[cur],u,SZ[cur])]++;
	}
	const LL half=Solve(cnt);
	ans+=half*(N-1LL-half)+half+(N-1LL-half);
	return ans;
}
#include<vector>
int main()
{
//	freopen("inn.txt","r",stdin);
	freopen("pol7b.in","r",stdin);
	while(scanf("%d",&N)==1)
	{
//		printf("N=%d\n",N);
		for(int i=0;i<N;i++)HEAD[i]=-1;
		NSZ=0;
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			AddEdge(a,b),AddEdge(b,a);
		}
		assert(NSZ==(N-1)*2);
		vector<int>wp;
	puts("a");
		for(int u=0;u<N;u++)
		{
			int mx=0;
			for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])
			{
				getmax(mx,GetSZ(ET[cur],u,SZ[cur]));
			}
			if(mx*2<=N)wp.push_back(u);
		}
	puts("b");
		assert(!wp.empty()&&wp.size()<=2);
		LL ans=0LL;
		for(int i=0;i<(int)wp.size();i++)
		{
			const LL ta=Solve(wp[i]);
			if(ta>ans)ans=ta;
		}
		printf("%d %lld\n",N-1,ans);
//		break;
	}
	return 0;
}
