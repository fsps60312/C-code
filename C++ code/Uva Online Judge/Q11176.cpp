#include<cstdio>
int N;
double P,DP[501][501];
double getDP(int n,int s)
{
	double &dp=DP[n][s];
	if(dp>=0.0)return dp;
	if(!n)return dp=0.0;
	if(!s)return dp=getDP(n-1,s)*(1.0-P);
	return dp=getDP(n-1,s-1)*P+getDP(n-1,s)*(1.0-P);
}
int main()
{
	while(scanf("%d%lf",&N,&P)==2&&N)
	{
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)DP[i][j]=-1.0;
		DP[0][0]=1.0;
		double ans=0.0;
		for(int i=0;i<=N;i++)ans+=i*getDP(N,i);
		printf("%.9lf\n",ans);
	}
	return 0;
}
