#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL N,POW2[300001];
LL C(const int a,const int b)
{
	LL ans=1LL;
	for(int i=b+1;i<=a;i++)(ans*=i)/=i-b;
	return ans;
}
int K;
LL Solve()
{
	if(N>K)return 0;
	static LL dp[2][300001];
	for(int i=0;i<=K;i++)dp[0][i]=0;
	dp[0][0]=1LL;
	int d=0;
	for(int i=0;i<N;i++,d^=1)
	{
		for(int j=0;j<=K;j++)dp[d^1][j]=0LL;
		for(int j=0;j<=K;j++)if(dp[d][j])for(int k=1;j+k<=K;k++)
		{
			dp[d^1][j+k]+=dp[d][j]*POW2[j]*C(K-j,k);
		}
		for(int j=0;j<=K;j++)printf(" %lld",dp[d^1][j]);puts("");
	}
	LL ans=0;
	for(int i=0;i<=K;i++)ans+=dp[d][i];
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	POW2[0]=1LL;
	for(int i=1;i<=300000;i++)POW2[i]=POW2[i-1]*2LL;
	while(scanf("%lld%d",&N,&K)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}
