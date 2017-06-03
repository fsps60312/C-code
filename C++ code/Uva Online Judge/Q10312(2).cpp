#include<cstdio>
typedef long long LL;
LL DP[27],ALL[28];
int main()
{
//	freopen("in.txt","r",stdin);
	DP[1]=1LL;
	for(int i=2;i<=26;i++)
	{
		DP[i]=0LL;
		for(int j=1;j<i;j++)DP[i]+=DP[j]*DP[i-j];
	}
	ALL[1]=1LL,ALL[2]=2LL;
	for(int i=3;i<=27;i++)
	{
		for(int j=2;j<i;j++)ALL[i]+=(ALL[j]/2LL)*ALL[i-j];//bracketed, bracked or only one
		ALL[i]+=ALL[i-1];
		ALL[i]*=2LL;
//		printf("ALL[%d]=%lld\n",i,ALL[i]);
	}
	int n;while(scanf("%d",&n)==1)printf("%lld\n",n<=2?0LL:ALL[n]/2LL-DP[n]);
	return 0;
}
