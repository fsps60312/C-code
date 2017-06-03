#include<cstdio>
int N;
double P,DP[501][501],T[501];
int main()
{
	while(scanf("%d%lf",&N,&P)==2&&N)
	{
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)DP[i][j]=-1.0;
		T[0]=1.0,DP[0][0]=1.0;
		for(int i=1;i<=N;i++)
		{
			DP[0][i]=1.0;
			T[i]=T[i-1]*P;
		}
		for(int n=1;n<=N;n++)
		{
			for(int i=0;i<=N;i++)
			{
				DP[n][i]=DP[n-1][i];
				if(n==i+1)DP[n][i]-=T[n];
				else if(n>i+1)DP[n][i]-=DP[n-i-2][i]*(1.0-P)*T[i+1];
			}
		}
		double ans=0.0;
		for(int i=1;i<=N;i++)
		{
			ans+=i*(DP[N][i]-(i?DP[N][i-1]:0.0));
		}
		printf("%.9lf\n",ans);
	}
	return 0;
}
