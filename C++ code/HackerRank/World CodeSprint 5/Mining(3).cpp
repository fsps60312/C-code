#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
int N,K;
LL D[5000],S[5000];
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
LL R[5000][5000],L[5000];
void BuildSUM(const int id,const int l,const int r,const int bl,const int br)
{
	if(l>r)return;
	const int mid=(l+r)/2;
	int smid=-1;
	SUM[id][mid]=INF;
	for(int i=max(id,bl);i<=min(mid-1,br);i++)if(getmin(SUM[id][mid],L[i]+R[i+1][mid]))smid=i;
	assert(smid!=-1);
	BuildSUM(id,l,mid-1,bl,smid);
	BuildSUM(id,mid+1,r,smid,br);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&D[i],&S[i]);
		for(int l=0;l<N;l++)
		{
			LL sum=0,cnt=0;
			R[l][l]=0;
			for(int r=l+1;r<N;r++)
			{
				sum+=(D[r]-D[r-1])*(cnt+=S[r-1]);
				R[l][r]=sum;
			}
		}
		for(int l=0;l<N;l++)
		{
			LL sum=0;
			L[l]=0;
			for(int r=l+1;r<N;r++)
			{
				sum+=(D[r]-D[l])*S[r];
				L[r]=sum;
			}
			SUM[l][l]=0,BuildSUM(l,l+1,N-1,l,N-2);
		}
		for(int i=0;i<N;i++)DP[0][i]=R[0][i];
		int d=0;
		for(int i=2;i<=K;i++,d^=1)BuildDP(DP[d],DP[d^1]);
		LL ans=INF;
		if(true)
		{
			LL sum=0,cnt=0;
			DP[d^1][N-1]=0;
			for(int i=N-2;i>=0;i--)
			{
				sum+=(D[i+1]-D[i])*(cnt+=S[i+1]);
				DP[d^1][i]=sum;
			}
		}
		for(int i=0;i<N;i++)getmin(ans,DP[d][i]+DP[d^1][i]);
		printf("%lld\n",ans);
	}
	return 0;
}
