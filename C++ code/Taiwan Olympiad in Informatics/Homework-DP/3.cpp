#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL DP[301][301];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=300;i++)for(int j=0;j<=300;j++)DP[i][j]=0;
	DP[0][0]=1;
	for(int i=1;i<=300;i++)
	{
		for(int j=0;j<=300;j++)if(DP[i-1][j])
		{
			for(int k=1;j+k<=300;k++)DP[i][j+k]+=DP[i-1][j];
		}
	}
	int N,L1,L2;
	while(scanf("%d%d%d",&N,&L1,&L2)==3)
	{
		LL ans=0LL;
		for(int i=L1;i<=L2;i++)ans+=DP[i][N];
		printf("%lld\n",ans);
	}
	return 0;
}
