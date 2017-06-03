#include<cstdio>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
int N,K;
int S[601][601],SUM[601][601];
int Sum(const int s1,const int s2,const int t1,const int t2){return SUM[s2][t2]-SUM[s2][t1-1]-SUM[s1-1][t2]+SUM[s1-1][t1-1];}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)S[i][j]=SUM[i][j]=0;
		for(int i=1;i<=N;i++)for(int j=i+1;j<=N;j++)scanf("%d",&S[i][j]);
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+S[i][j];
		static int dp[600][601];
		for(int i=0;i<=K;i++)for(int j=1;j<=N;j++)dp[i][j]=0;
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<K;j++)
			{
				for(int k=1;k<=i;k++)getmax(dp[j+1][i+1],dp[j][k]+Sum(k,i,i+1,N));
			}
		}
		int ans=0;
		for(int i=1;i<=N;i++)getmax(ans,dp[K][i]);
		printf("%d\n",ans);
	}
	return 0;
}
