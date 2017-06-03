#include<cstdio>
#define LL long long
LL M,N;
//LL GSUM[1001][1001];
LL gcd(int a,int b){return b?gcd(b,a%b):a;}
LL Cnt3(LL a){return a*(a-1)*(a-2)/6LL;}
int main()
{
//	for(int i=0;i<=1000;i++)GSUM[0][i]=GSUM[i][0]=0;
//	for(int i=1;i<=1000;i++)
//	{
//		for(int j=1;j<=1000;j++)
//		{
//			int &g=GSUM[i][j]=GSUM[i-1][j]+GSUM[i][j-1]-GSUM[i-1][j-1];
//			int v=gcd(i,j);
//			g+=v-1;
//		}
//	}
//NOT[2][2]:8,NOT[3][3]:44
	int kase=1;
	while(scanf("%lld%lld",&M,&N)==2&&(M||N))
	{
		LL ans=Cnt3((M+1LL)*(N+1LL));
		ans-=(N+1LL)*Cnt3(M+1LL);
		ans-=(M+1LL)*Cnt3(N+1LL);
		for(int i=1;i<=M;i++)
		{
			for(int j=1;j<=N;j++)
			{
				ans-=(gcd(i,j)-1)*(M-i+1LL)*(N-j+1LL)*2LL;
			}
		}
		printf("Case %d: %lld\n",kase++,ans);
	}
	return 0;
}
