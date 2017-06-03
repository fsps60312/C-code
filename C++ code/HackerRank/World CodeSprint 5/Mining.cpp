#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
int N,K,L[5000],S[5000];
LL SUM[5000][5000];
void BuildDP(const LL *pre,LL *dp,const int pl,const int pr,const int dl,const int dr)
{
	if(dl>dr)return;
	const int dmid=(dl+dr)/2;
	dp[dmid]=INF;
	int pmid=-1;
	for(int i=pl;i<=pr&&i<=dmid;i++)if(getmin(dp[dmid],pre[i]+SUM[i][dmid]))pmid=i;
	assert(pmid!=-1);
	BuildDP(pre,dp,pl,pmid,dl,dmid-1);
	BuildDP(pre,dp,pmid,pr,dmid+1,dr);
}
void BuildDP(const LL *pre,LL *dp)
{
	BuildDP(pre,dp,0,N-1,0,N-1);
}
LL DP[2][5000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&L[i],&S[i]);
		for(int l=0;l<N;l++)
		{
			LL sum=0,cnt=0;
			SUM[l][l]=0;
			for(int r=l+1;r<N;r++)
			{
				sum+=(L[r]-L[r-1])*(++cnt);
				SUM[l][r]=sum;
			}
		}
		if(true)
		{
			LL sum=0,cnt=0;
			DP[0][0]=0;
			for(int i=1;i<N;i++)
			{
				sum+=(L[i]-L[i-1])*(cnt+=S[i-1]);
				DP[0][i]=sum;
			}
		}
		int d=0;
		for(int i=2;i<=K;i++,d^=1)BuildDP(DP[d],DP[d^1]);
		if(true)
		{
			LL sum=0,cnt=0;
			DP[d^1][N-1]=0;
			for(int i=N-2;i>=0;i--)
			{
				sum+=(L[i+1]-L[i])*(cnt+=S[i+1]);
				DP[d^1][i]=sum;
			}
		}
		LL ans=INF;
		for(int i=0;i<N;i++)getmin(ans,DP[d][i]+SUM[i][N-1]);
		printf("%lld\n",ans);
	}
	return 0;
}
