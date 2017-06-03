#include<cstdio>
#include<cassert>
using namespace std;
const double EPS=1e-15;
int N;
double P,Q;
double Solve()
{
	static double a[51][51],b[51][51];//spaces, value: possibility
	for(int i=1;i<=50;i++)for(int j=1;j<=50;j++)a[i][j]=b[i][j]=0.0;
	for(int i=1;i<=50;i++)
	{
		for(int v=1;v<=50;v++)
		{
				 if(v==1)a[i][v]=P,b[i][v]=0.0;
			else if(v==2)a[i][v]=b[i][v]=Q;
			else
			{
				a[i][v]=a[i][v-1]*a[i-1][v-1];
				b[i][v]=b[i][v-1]*b[i-1][v-1];
			}
		}
	}
	for(int space=50;space>=1;space--)
	{
		for(int v=1;v<=50;v++)
		{
			a[space][v]*=1.0-a[space-1][v];
			b[space][v]*=1.0-b[space-1][v];
		}
	}
	static double dp[51][51],sum[51][51];//space, value: excepted sum
	for(int v=1;v<=50;v++)dp[50][v]=v;
	for(int space=49;space>=0;space--)
	{
		for(int v=1;v<=50;v++)
		{
			double &d=dp[space][v]=0.0;
			double &s=sum[space][v]=0.0;
			for(int pre=1;pre<=50;pre++)if(pre!=v)
			{
				if(pre==1)
				{
					d+=dp[space+1][pre]*b[space+1][v];
					s+=b[space+1][v];
				}
				else if(pre<v)
				{
					d+=dp[space+1][pre]*a[space+1][v];
					s+=a[space+1][v];
				}
			}
			d=v+d/sum;
		}
	}
	if(N<50)
	{
		
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lf",&N,&P)==2)
	{
		P/=1e9,Q=1.0-P;
		printf("%.10f\n",Solve());
	}
	return 0;
}
