#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
LL DP[100001][51];
LL GetDP(const int n,const int k)
{
	if(n<k*2)return 0LL;
	assert(2<=n&&n<=100000&&1<=k&&k<=50);
	LL &ans=DP[n][k];
	if(ans!=-1)return ans;
	ans=0LL;
	(ans+=GetDP(n-1,k)*(((LL)n*(n-1LL)/2LL)*2LL%MOD))%=MOD;
	if(k>1)(ans+=GetDP(n-2,k-1)*(((LL)n*(n-1LL)/2LL)%MOD*(n-1LL)%MOD))%=MOD;
	return ans;
}
int N,K;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=2;i<=100000;i++)for(int j=1;j<=50;j++)DP[i][j]=-1LL;
	DP[2][1]=1;
//	DP[4][2]=1*3*(4*3)/2*(2*1)/2;
	//DP[2k][k]=1*3*...*2k-1*k!/2^(k/2)
	for(int k=2;k<=50;k++)DP[2*k][k]=(DP[2*(k-1)][k-1]*(2LL*k-1LL)%MOD*((2LL*k*(2LL*k-1LL))/2LL)%MOD);
//	for(int i=1;i<=5;i++)printf("%lld ",DP[i*2][i]);puts("");
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		static int kase=1;
		printf("Case %d: %lld\n",kase++,GetDP(N,K));
	}
	return 0;
}
