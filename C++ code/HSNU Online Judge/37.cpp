#include<cstdio>
int N,M,DP[3000];
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		int ans=1;
		for(int i=0;i<N;i++)
		{
			DP[i]=1;
			for(int j=i-M-1;j>=0;j--)DP[i]+=DP[j],DP[i]%=10000;
			ans+=DP[i],ans%=10000;
		}
		printf("%d\n",ans);
	}
	return 0;
}
