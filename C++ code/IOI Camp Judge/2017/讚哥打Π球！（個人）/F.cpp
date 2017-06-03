#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,M,A[1003];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)scanf("%d",&A[i]);
		A[0]=A[N+1]=0;
		static int dp[1002][1001][2];
		for(int i=0;i<N+2;i++)for(int j=0;j<M+1;j++)for(int k=0;k<2;k++)dp[i][j][k]=0;
		for(int i=1;i<N+2;i++)
		{
//			printf("dp[%d][%d]=%d\n",i,M,dp[i][M]);
			for(int j=0;j<M+1;j++)
			{
				getmax(dp[i][j][0],dp[i-1][j][0]+A[i]);
				getmax(dp[i][j][0],dp[i-1][j][1]+A[i]);
				if(j>=1)
				{
					getmax(dp[i][j][1],dp[i-1][j-1][0]+A[i-1]+A[i]*2);
					getmax(dp[i][j][1],dp[i-1][j-1][1]+A[i-1]*2+A[i]*2);
				}
			}
//			printf("dp[%d][%d]=%d\n",i,M,dp[i][M]);
		}
		printf("%d\n",max(dp[N+1][M][0],dp[N+1][M][1]));
	}
	return 0;
}
