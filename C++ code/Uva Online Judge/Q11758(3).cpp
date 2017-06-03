#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int T,N,K,D;
LL C[10001][101],ANS;
LL CNT[16];
LL DP[16][10001];
void Dfs(const LL &now,const int dep)
{
	if(dep==16)
	{
		LL ta=C[N-K-now+K/2LL][K/2LL];
		for(int i=0;i<16;i++)
		{
			(ta*=C[K/2LL][CNT[i]])%=MOD;
			if(i==15)assert(CNT[i]==0LL);
		}
		(((ANS-=ta)%=MOD)+=MOD)%=MOD;
		return;
	}
	for(LL &cnt=CNT[dep]=0LL;cnt<=K/2&&now+cnt*(1LL<<dep)<=N-K;cnt+=(D+1LL))
	{
		Dfs(now+cnt*(1LL<<dep),dep+1);
	}
}
LL Solve()
{
	ANS=C[N][K];
	for(int i=0;i<16;i++)for(int j=0;j<=N-K;j++)DP[i][j]=0LL;
	for(int cnt=0;cnt<=K/2&&cnt*(1<<0)<=N-K;cnt+=(D+1))DP[0][cnt]=C[K/2][cnt];
	for(int d=1;d<16;d++)
	{
		for(int i=0;i<=N-K;i+=(D+1))if(DP[d-1][i])
		{
			for(int cnt=0;cnt<=K/2&&i+cnt*(1<<d)<=N-K;cnt+=(D+1))
			{
				(DP[d][i+cnt*(1<<d)]+=DP[d-1][i]*C[K/2][cnt])%=MOD;
			}
		}
	}
	LL ta=0LL;
	for(int i=0;i<=N-K;i+=(D+1))(ta+=DP[15][i]*C[N-K-i+K/2][K/2])%=MOD;
	return (((ANS-=ta)%=MOD)+=MOD)%=MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=10000;i++)
	{
		C[i][0]=1LL;
		if(i<=100)C[i][i]=1LL;
		for(int j=1;j<=100&&j<i;j++)((C[i][j]=C[i-1][j-1])+=C[i-1][j])%=MOD;
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&K,&D);
		printf("%lld\n",Solve());
	}
}
