#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
int N,L,S[100];
LL DP[101][3][201][1001];
LL GetDP(const int one_used,const int idx,const int level,const int )
{
	LL &dp=DP[one_used][idx][level];
	if(dp!=-1LL)return dp;
	if(idx==N)
	{
		if(one_used==2&&level==0)return dp=1LL;
		else return dp=0LL;
	}
	dp=0LL;
	if(level>=2)dp+=GetDP(one_used,idx+1,level-2);
	dp+=GetDP(one_used,idx+1,level+2);
	
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&L)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		for(int i=0;i<=N;i++)for(int j=0;j<=3;j++)for(int k=0;k<=N*2;k++)for(int l=0;l<=L;l++)DP[i][j][k][l]=-1LL;
		printf("%lld\n",GetDP(0,0,0));
	}
	return 0;
}
