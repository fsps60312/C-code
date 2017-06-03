#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,S[2000];
int CNT[5000];
double DP[3][20001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<5000;i++)CNT[i]=0;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(S[i]>S[j])CNT[S[i]-S[j]]++;
		for(int i=0;i<=20000;i++)DP[0][i]=0.0;
		for(int i=0;i<5000;i++)DP[0][10000+i]=CNT[i];
		for(int type=1;type<3;type++)
		{
			for(int i=0;i<=20000;i++)DP[type][i]=0.0;
			for(int i=0;i<=20000;i++)if(DP[type-1][i]!=0.0)
			{
				const double v=DP[type-1][i];
				for(int j=0;j<5000;j++)DP[type][i-j]+=v*CNT[j];
			}
		}
		double ans=0.0,sum=0.0;
		for(int i=0;i<=20000;i++)
		{
			sum+=DP[2][i];
			if(i>10000)ans+=DP[2][i];
		}
		printf("%.9f\n",ans/sum);
	}
	return 0;
}
