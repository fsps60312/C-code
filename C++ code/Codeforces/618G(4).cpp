#include<cstdio>
#include<cassert>
using namespace std;
const double EPS=1e-15;
int N;
double P,Q,A[51],B[51];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lf",&N,&P)==2)
	{
		P/=1e9;
		Q=1.0-P;
		A[1]=P,B[1]=0.0;
		A[2]=P*P,B[2]=Q;
		for(int i=3;i<=50;i++)
		{
			A[i]=(A[i-1]+B[i-1])*A[i-1];
			B[i]=(A[i-1]+B[i-1])*B[i-1];
		}
		for(int i=1;i<=50;i++)printf("(%.10f,%.10f)\n",A[i],B[i]);
		assert(A[50]<EPS),assert(B[50]<EPS);
		if(N<50)
		{
			static double dp[2][51],ab[2][51];
			for(int i=1;i<=N;i++)dp[0][i]=i,ab[0][i]=A[i]+B[i];
			dp[0][N+1]=N+1,ab[0][N+1]=B[N+1];
			int d=0;
			for(int i=2;i<=N;i++,d^=1)
			{
				const int remain=N-i+1;
				for(int j=1;j<=remain;j++)
				{
					dp[d^1][j]=0.0,ab[d^1][j]=0.0;
					for(int k=1;k<=remain+2;k++)if(k>j)dp[d^1][j]+=(dp[d][k]+j)*ab[d][k],ab[d^1][j]+=ab[d][k]*(A[j]+B[j]);
					if(j==2)dp[d^1][j]+=(dp[d][1]+2.0)*ab[d][1],ab[d^1][j]+=ab[d][1]*Q;
				}
				dp[d^1][remain+1]=0.0,ab[d^1][remain+1]=0.0;
				for(int k=1;k<=remain+2;k++)if(k>remain+1)dp[d^1][remain+1]+=(dp[d][k]+(remain+1))*ab[d][k],ab[d^1][remain+1]+=ab[d][k]*B[remain+1];
				if(remain+1==2)dp[d^1][remain+1]+=(dp[d][1]+2.0)*ab[d][1],ab[d^1][remain+1]+=ab[d][1]*Q;
			}
			printf("%.10f\n",dp[d][1]*ab[d][1]+dp[d][2]*ab[d][2]);
		}
		else
		{
			puts("not implemented");
		}
	}
	return 0;
}
