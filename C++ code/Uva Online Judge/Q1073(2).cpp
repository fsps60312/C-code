#include<cstdio>
#define LL long long
int N;
int DP[1001][5][2];// L:0 R:1
int ANS[498];
LL solve()
{
	if(N<4||N%2)return 0;
	return ANS[(N-4)/2];
}
int main()
{
	for(int i=0;i<=4;i++)DP[1][i][0]=DP[1][i][1]=0;
	DP[1][0][1]=1;
	for(int l=2;l<=1000;l++)
	{
		for(int r=0;r<=4;r++)DP[l][r][0]=DP[l-1][r][1];
		for(int r=0;r<=4;r++)
		{
			DP[l][r][1]=DP[l-1][r][0];
			if(r>0)DP[l][r][1]+=DP[l-1][r-1][1];
		}
	}
	for(int i=0,l=4;i<=498;i++,l+=4)ANS[i]=DP[l][4][0]+DP[l][3][1];
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		printf("Case %d: %lld\n",kase++,solve());
	}
	return 0;
}
