#include<cstdio>
typedef long long LL;
LL DP[27],ALL[28];
int main()
{
	freopen("in.txt","r",stdin);
	DP[1]=1LL;
	for(int i=2;i<=26;i++)
	{
		DP[i]=0LL;
		for(int j=1;j<i;j++)DP[i]+=DP[j]*DP[i-j];
	}
	ALL[1]=0LL,ALL[2]=1LL;
	for(int i=3;i<=27;i++)
	{
		ALL[i]=0LL;
		for(int j=2;j<i;j++)ALL[i]+=(ALL[j]+1);
		printf("ALL[%d]=%lld\n",i,ALL[i]);
	}
	int n;while(scanf("%d",&n)==1)printf("%lld-%lld=%lld\n",ALL[n+1],DP[n],ALL[n+1]-DP[n]);
	return 0;
}
