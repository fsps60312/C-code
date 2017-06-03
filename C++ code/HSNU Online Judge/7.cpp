#include<cstdio>
int DP[10000001][2],N;
int main()
{
	DP[1][0]=1,DP[1][1]=0;
	for(int i=2;i<=10000000;i++)
	{
		DP[i][0]=DP[i-1][0]+DP[i-1][1]%10;
		DP[i][1]=DP[i-1][0]%10;
	}
	while(scanf("%d",&N)==1)
	{
//		printf("(%d,%d)\n",DP[N][0],DP[N][1]);
		printf("%d\n",(DP[N][0]+DP[N][1])%10);
	}
	return 0;
}
