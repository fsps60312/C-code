#include<cstdio>
typedef unsigned long long LL;
int K;
LL N;
LL DP[101][64];
int get_ANS()
{
	for(int ty=0;ty<=63;ty++)
	{
		if(DP[K][ty]>=N)return ty;
	}
	return -1;
}
int main()
{
	for(int i=0;i<=63;i++)DP[0][i]=0;
	for(int i=0;i<=100;i++)DP[i][0]=0;
	for(int b=1;b<=100;b++)
	{
		for(int ty=1;ty<=63;ty++)
		{
			DP[b][ty]=DP[b-1][ty-1]+1+DP[b][ty-1];
		}
	}
	//freopen("in.txt","r",stdin);
	while(scanf("%d%llu",&K,&N)==2&&K)
	{
		int ans=get_ANS();
		if(ans==-1)printf("More than 63 trials needed.\n");
		else printf("%d\n",ans);
	}
}
