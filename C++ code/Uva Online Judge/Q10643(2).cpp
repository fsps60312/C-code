#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int DP[502][501],SUM[501];
int T,M;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&M);
		assert(M%2==0);
		for(int i=0;i<=M;i++)DP[0][i]=0;
		DP[0][0]=1;
		for(int i=0;i<=M;i++)DP[1][i]=0;
		for(int i=0;i<=M;i+=2)DP[1][i]=1;
		for(int cnt=1;cnt<=M;cnt++)
		{
			for(int i=0;i<=M;i+=2)
			{
				DP[cnt+1][i]=0;
				if(i-2>=cnt)DP[cnt+1][i]+=DP[cnt][i-2];
				if(i>=cnt)DP[cnt+1][i]+=DP[cnt][i];
			}
//			for(int i=0;i<=M;i++)printf(" %d",DP[cnt+1][i]);puts("");
		}
		static int kase=1;
		printf("Case %d: %d\n",kase++,DP[M+1][M]);
	}
	return 0;
}
