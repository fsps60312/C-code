#include<cstdio>
#include<cassert>
using namespace std;
//const double EPS=1e-15;
int N;
double P,Q;
double Solve()
{
//	const int maxp=50;
	double a[50+1][50+1];
    double b[50+1][50+1];
    for(int i=0;i<=50;i++)for(int j=0;j<=50;j++)a[i][j]=b[i][j]=0;
    for (int len = 1; len <= 50; len++) { 
      for (int pow = 1; pow <= 50; pow++) {
        if (pow == 1) a[len][pow] += P;
        if (pow == 2) {
          a[len][pow] += Q;
          b[len][pow] += Q;
        }
        a[len][pow] += a[len-1][pow-1] * a[len][pow-1];
        b[len][pow] += a[len-1][pow-1] * b[len][pow-1];
      }
    }
    for (int len = 50; len >= 1; len--) {
      for (int pow = 1; pow <= 50; pow++) {
        a[len][pow] *= 1 - a[len-1][pow];
        b[len][pow] *= 1 - a[len-1][pow];
      }
    }
    
    // manually do first few cases
    double dp[50+1][50+1];
    double sum[50+1][50+1];
//    for(int i=0;i<=maxp;i++)for(int j=0;j<=maxp;j++)dp[i][j]=sum[i][j]=0;
    for (int cur = 1; cur <= 50; cur++)
      dp[1][cur] = cur;//vals[cur];
    
    // manual dp
    for (int slime = 2; slime <=50; slime++)
	{
		for (int v = 1; v <= 50; v++)
		{
			double &d=dp[slime][v]=0.0,&s=sum[slime][v]=0.0;
			for (int next = 1; next <= 50; next++) if (v != next)
			{
				if (v == 1)
				{
					d += b[slime-1][next] * dp[slime-1][next];
					s += b[slime-1][next];
				}
				else if(v>next)
				{
					d += a[slime-1][next] * dp[slime-1][next];
					s += a[slime-1][next];
				}
			}
			d=v+d/s;
		}
    }
    if (N <= 50)
	{
		double ans = 0;
		for (int i = 1; i <= 50; i++)if(a[N][i]!=0.0)ans += a[N][i] * dp[N][i];
		return ans;
    }
    return -1.0;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(double p;scanf("%d%lf",&N,&p)==2;)
	{
		P=p;
		P/=1000000000,Q=1-P;
		printf("%.10f\n",Solve());
	}
	return 0;
}
