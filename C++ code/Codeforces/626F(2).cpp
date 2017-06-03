#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int N,K,S[201];
LL DP[2][201][1001];
void Add(LL &a,const LL &b){(a+=b)%=MOD;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		sort(S+1,S+N+1),S[0]=0;
		for(int d=0;d<2;d++)for(int i=0;i<=N;i++)for(int j=0;j<=K;j++)DP[d][i][j]=0LL;
		DP[0][0][0]=1LL;
		int d=0;
		for(int idx=1;idx<=N;idx++,d^=1)
		{
			for(int g=0;g<=N;g++)for(int i=0;i<=K;i++)DP[d^1][g][i]=0LL;
			for(int g=0;g<=N;g++)for(int i=0;i<=K;i++)if(DP[d][g][i])
			{
				const int nxti=i+g*(S[idx]-S[idx-1]);
				if(nxti>K)break;
				Add(DP[d^1][g][nxti],g*DP[d][g][i]);//Add to existing group
				Add(DP[d^1][g+1][nxti],DP[d][g][i]);//Create new group
				if(g>0)Add(DP[d^1][g-1][nxti],g*DP[d][g][i]);//Add to and close one group
				Add(DP[d^1][g][nxti],DP[d][g][i]);//Create and close new group
			}
		}
		LL ans=0LL;
		for(int i=0;i<=K;i++)Add(ans,DP[d][0][i]);
		printf("%I64d\n",ans);
	}
	return 0;
}
