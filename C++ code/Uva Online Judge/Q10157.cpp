#include<cstdio>
typedef long long LL;
LL N,D;
LL DP[300][151][2];
LL Solve()
{
	if((N&1LL)==1LL)return 0LL;
	for(int i=0;i<=D;i++)DP[0][i][0]=DP[0][i][1]=0LL;
	DP[0][1][D==1?1:0]=1LL;
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<D;j++)
		{
			DP[i][j][0]=0LL;
			if(j+1<D)DP[i][j][0]+=DP[i-1][j+1][0];
			if(j-1>=0)DP[i][j][0]+=DP[i-1][j-1][0];
		}
		for(int j=0;j<=D;j++)
		{
			DP[i][j][1]=0LL;
			if(j+1<=D)DP[i][j][1]+=DP[i-1][j+1][1];
			if(j-1>=0)DP[i][j][1]+=DP[i-1][j-1][1];
		}
		DP[i][D][1]+=DP[i-1][D-1][0];
	}
	return DP[N-1][0][1];
}
int main()
{
	while(scanf("%lld%lld",&N,&D)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}
