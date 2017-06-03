#include<cstdio>
#define LL long long 
int N;
LL DP[503][5][2];//R, R pairs, left is 0:L 1:R
LL ANS[499];
LL solve()
{
	if(N<4||N%2)return 0;
	return ANS[(N-4)/2];
}
int main()
{
	for(int i=0;i<=4;i++)DP[1][i][0]=DP[1][i][1]=0LL;
	DP[1][0][1]=1LL;//R
	DP[1][0][0]=1LL;//OR
	for(int r=2;r<=502;r++)
	{
		for(int p=0;p<=4;p++)
		{
			DP[r][p][0]=DP[r-1][p][0],DP[r][p][1]=DP[r-1][p][1];//OR
			if(p>0)DP[r][p][0]+=DP[r-1][p-1][0],DP[r][p][1]+=DP[r-1][p-1][1];//R
		}
	}
	for(int i=0,l=4;i<=498;i++,l++)ANS[i]=DP[l][4][0]+DP[l][3][1]+DP[l][4][1];
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		printf("Case %d: %lld\n",kase++,solve());
	}
	return 0;
}
