#include<cstdio>
typedef long long LL;
int T,N,P,R;
LL LEVEL[13],DP[13][13];
LL Solve()
{
	if(P<=0||R<=0)return 0LL;
	LL ans=0;
	for(int i=0;i<N;i++)ans+=(LEVEL[N-1]/LEVEL[i]/LEVEL[N-i-1])*DP[i][P-1]*DP[N-i-1][R-1];
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	LEVEL[0]=1LL;
	for(int i=1;i<=12;i++)LEVEL[i]=LEVEL[i-1]*i;
	for(int i=0;i<13*13;i++)DP[i/13][i%13]=0LL;
	DP[0][0]=1LL;
	for(int i=1;i<=12;i++)
	{
		for(int j=1;j<=i;j++)
		{
			for(int k=0;k<i;k++)DP[i][j]+=LEVEL[i-1]/LEVEL[k]*DP[k][j-1];
		}
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&P,&R);
		printf("%lld\n",Solve());
	}
	return 0;
}
