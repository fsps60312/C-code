#include<cstdio>
#include<cassert>
using namespace std;
double *DP[201][201],S[201];
int N,K;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=1;i<=N;i++)scanf("%lf",&S[i]);
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)
		{
			DP[i][j]=new double[201]+100;
			for(int k=-100;k<=100;k++)DP[i][j][k]=0.0;
		}
		DP[0][0][0]=1.0;
		for(int i)
	}
	return 0;
}
