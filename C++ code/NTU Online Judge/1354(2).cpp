#include<cstdio>
#include<cassert>
using namespace std;
const int MOD=10056;
int N,DP[1002],C[1001][1001];
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
		DP[0]=1;
		for(int n=1;n<=N+1;n++)
		{
			int &dp=DP[n]=DP[n-1]*(N-n+1)%MOD;
			for(int i=1;i<n-1;i++)(dp+=(DP[(n-1)-(i+1)]*C[N-((n-1)-(i+1))][i+1]%MOD)*(N-n+1))%=MOD;
		}
		int ans=DP[N];
		for(int i=1;i<N;i++)(ans+=DP[N-(i+1)]*C[N-(N-(i+1))][i+1])%=MOD;
		printf("%d\n",ans);
	}
	return 0;
}
