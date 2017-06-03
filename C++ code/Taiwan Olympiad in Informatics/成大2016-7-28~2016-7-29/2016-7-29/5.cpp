#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
//struct Fraction
//{
//	LL UPON,DOWN;
//	Fraction(){}
//};
int N,S[5];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int SUM=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),SUM+=S[i];
		double ans=0.0;
		for(int color=0;color<N;color++)
		{
			static double dp[251][51];
			for(int i=0;i<=SUM;i++)for(int j=0;j<=S[color];j++)dp[i][j]=0.0;
			dp[SUM][S[color]]=1.0;
			for(int i=SUM;i>=1;i--)
			{
				for(int remain=1;remain<=S[color];remain++)if(dp[i][remain]>0.0)
				{
					const double &d=dp[i][remain];
					if(i==remain)ans+=(SUM-remain)*d;
					else
					{
						dp[i-1][remain]+=d*(i-remain)/i;
						dp[i-1][remain-1]+=d*remain/i;
					}
				}
			}
		}
		printf("%.10f\n",ans);
	}
	return 0;
}
