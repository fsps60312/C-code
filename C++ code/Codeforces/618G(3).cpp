#include<cstdio>
#include<cassert>
using namespace std;
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
		if(N<50)
		{
			static double DP[2][51];
			for(int i=1;i<=N;i++)DP[0][i]=i*(A[i]+B[i]);
			DP[0][N+1]=(N+1)*B[N+1];
			int d=0;
			for(int i=2;i<=N;i++,d^=1)
			{
				const int remain=N-i+1;
				for(int j=1;j<=remain;j++)
				{
					DP[d^1][j]=j;
					for(int k=1;k<=remain+2;k++)if(k>j)DP[d^1][j]+=DP[d][k];
					DP[d^1][j]*=A[j]+B[j];
					if(j==2)DP[d^1][j]+=(DP[d][1]+2.0)*Q;
				}
				DP[d^1][remain+1]=remain+1;
				for(int k=1;k<=remain+2;k++)if(k>remain+1)DP[d^1][remain+1]+=DP[d][k];
				if(remain+1==2)DP[d^1][remain+1]+=DP[d][1];
				DP[d^1][remain+1]*=B[remain+1];
			}
			printf("%.10f\n",DP[d][1]+DP[d][2]);
		}
		else
		{
			puts("not implemented");
		}
	}
	return 0;
}
