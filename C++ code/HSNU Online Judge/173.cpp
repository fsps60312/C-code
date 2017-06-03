#include<cstdio>
typedef long long LL;
const LL MOD=10000019LL;
int N;
LL DP[100000][4];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)for(int j=0;j<4;j++)DP[i][j]=0LL;
	DP[0][0]=DP[0][2]=1LL;
	for(int i=0;i<N-1;i++)
	{
		for(int j=0;j<4;j++)
		{
			(DP[i+1][j>>1]+=DP[i][j])%=MOD;
			if(j!=3)(DP[i+1][2+(j>>1)]+=DP[i][j])%=MOD;
		}
	}
	LL ans=0LL;
	for(int i=0;i<4;i++)(ans+=DP[N-1][i])%=MOD;
	printf("%lld\n",ans);
	return 0;
}
