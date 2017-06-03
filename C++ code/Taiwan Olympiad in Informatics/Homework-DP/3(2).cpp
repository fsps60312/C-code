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
		for(int j=300;j>=0;j--)for(int k=0;k+i<=300;k++)if(DP[j][k])
		{
			for(int l=1;k+i*l<=300&&j+l<=300;l++)DP[j+l][k+i*l]+=DP[j][k];
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
