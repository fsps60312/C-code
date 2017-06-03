#include<cstdio>
int N;
double DP[34];
double GetDP(const int remain)
{
	double &dp=DP[remain];
	if(dp!=-1.0)return dp;
	//DP[i]==1+i/N*DP[i-1]+(N-i)/N*DP[i]
	//DP[i]*i/N==1+i/N*DP[i-1]
	//DP[i]==N/i+DP[i-1]
	return dp=(double)N/remain+GetDP(remain-1);
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		DP[0]=0.0;
		for(int i=1;i<=N;i++)DP[i]=-1.0;
		double ans=GetDP(N);
		printf("%lf\n",ans);
	}
	return 0;
}
