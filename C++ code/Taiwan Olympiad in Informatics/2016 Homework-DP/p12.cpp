#include<cstdio>
#include<cassert>
using namespace std;
struct Matrix
{
	double S[7][7];
};
int N,R,G;
double P[1000],WIN_CHANCE[3];
double BuildWinChance()
{
	if(true)
	{
		double &v=WIN_CHANCE[0]=0.0;
		for(int i=0;i<N;i++)v+=P[i];
		v/=N;
	}
	static double dp[3][1000];
	for(int i=0;i<N;i++)dp[0][0]=P[i];
	for(int i=1;i<3;i++)
	{
		double v=0.0;
		for(int j=0;j<N;j++)
		{
			if(dp[i-1][j]<WIN_CHANCE[0])dp[i][j]=
		}
	}
	if(true)
	{
		double &v=WIN_CHANCE[1]=0.0;
		
	}
}
double Solve()
{
	
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&R,&G)==3)
	{
		for(int i=0;i<N;i++)scanf("%lf",&P[i]);
		printf("%.9f\n",Solve());
	}
	return 0;
}
