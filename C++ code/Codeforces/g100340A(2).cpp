#include<cstdio>
#include<cassert>
#include<algorithm>
#include<utility>
using namespace std;
template<class T>inline bool getmin(T&a,const T&b){if(b<a)return a=b,true;else return false;}
typedef long long LL;
const LL INF=9223372036854775807LL;
int N,M;
pair<LL,int>G[30];
LL DP[30][5001];
pair<int,int>PRE[30][5001];
LL GetDP(const int i,const int remain)
{
	LL &ans=DP[i][remain];
	pair<int,int>&pre=PRE[i][remain];
	if(remain==0)return pre=make_pair(N,0),ans=0;
	assert(0<=i&&i<N);
	if(ans!=-1)return ans;
	ans=INF;
	LL g=G[i].first;
	for(int j=i+1;j<N;j++)
	{
		const int width=N-j;
		for(int k=1;k*width<=remain;k++)
		{
			const LL val=GetDP(j,remain-k*width);
			if(val!=INF)
			{
				if(getmin(ans,val+g*width))pre=make_pair(j,remain-k*width);
			}
		}
		g+=G[j].first;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("cookies.in","r",stdin);
	freopen("cookies.out","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0,v;i<N;i++)scanf("%d",&v),G[i]=make_pair((LL)v,i);
		sort(G,G+N);
		for(int i=0;i<N;i++)for(int j=0;j<=M;j++)DP[i][j]=-1;
		LL ans=INF;
		pair<int,int>pre=make_pair(0,-1);
		int height=-1;
		for(int k=1;k*N<=M;k++)if(getmin(ans,GetDP(0,M-k*N)))pre.second=M-k*N,height=k;
		assert(ans!=INF);
		printf("%lld\n",ans);
		for(int i=0;;)
		{
			const pair<int,int>&nxt_pre=PRE[pre.first][pre.second];
			for(;i<nxt_pre.first;i++)G[i].first=height;
//			printf("(%d,%d)\n",pre.first,pre.second);
//			printf("height=%d,i=%d\n",height,i);
			if(nxt_pre.first==N)break;
			height+=(pre.second-nxt_pre.second)/(N-nxt_pre.first);
			pre=nxt_pre;
		}
		sort(G,G+N,[](pair<LL,int>a,pair<LL,int>b)->bool{return a.second<b.second;});
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%lld",G[i].first);
		}
		puts("");
	}
	return 0;
}
