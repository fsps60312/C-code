#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
LL T,N/*10000*/,K/*100*/,D,C[10001][101];
LL solve()
{
	if(D>=K/2LL)return C[N][K]*2LL%MOD;
	LL d=K/2LL-D;
	LL ans=C[N-d][K-d]*2LL%MOD;
	if(d>=1)
	{
		int buffer=0,cnt=0;
		for(int i=0;i<N;i++)
	}
}
int main()
{
	for(int l=1;l<=10000;l++)
	{
		C[l][0]=1LL;if(l<=100)C[l][l]=1LL;
		for(int i=1;i<l&&i<=100;i++)
		{
			C[l][i]=C[l-1][i-1]+C[l-1][i];
			C[l][i]%=MOD;
		}
	}
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&N,&K,&D);
		print("%lld\n",solve());
	}
	return 0;
}
