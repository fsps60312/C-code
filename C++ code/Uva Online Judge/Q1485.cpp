#include<cstdio>
#define LL long long
const LL MOD=1000000007LL;
LL N,K,DP[1001][1001];
int main()
{
	for(N=1LL;N<=1000LL;N++)
	{
		DP[N][0]=1LL;
		for(K=1LL;K<N;K++)
		{
			//DP[N-1LL][K]*K: swap with that K numbers or put back(not change)
			//DP[N-1LL][K-1LL]*(N-K+1LL): swap with that N-K numbers(+=1)
			DP[N][K]=DP[N-1LL][K]*(K+1LL)+DP[N-1LL][K-1LL]*(N-K);
			DP[N][K]%=MOD;
		}
		DP[N][N]=0LL;
	}
	while(scanf("%lld%lld",&N,&K)==2)
	{
		printf("%lld\n",DP[N][K]);
	}
	return 0;
}
