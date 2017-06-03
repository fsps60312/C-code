#include<cstdio>
#include<cassert>
using namespace std;
const int MOD=10056;
int N,DP[1001][1000],C[1001][1001];
int main()
{
	freopen("in.txt","r",stdin);
	C[0][0]=1;
	for(int i=1;i<=1000;i++)
	{
		C[i][0]=1;
		for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		C[i][i]=1;
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		DP[0][0]=1;
		for(int n=1;n<=N;n++)
		{
			for(int e=0;e<n;e++)
			{
				int &dp=DP[n][e]=0;
				if(e==0)
				{
					for(int i=0;i<n;i++)(dp+=DP[n-1][i]*(N-n+1))%=MOD;
				}
				else (dp+=DP[n-(e+1)][0]*C[N-(n-(e+1))][e+1])%=MOD;
			}
			DP[n][n]=0;
		}
		int ans=0;
		for(int i=0;i<N;i++)(ans+=DP[N][i])%=MOD;
		printf("%d\n",ans);
	}
	return 0;
}
