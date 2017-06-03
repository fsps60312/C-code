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
		for(int cnt=0;cnt<=M;cnt++)
		{
			SUM[0]=DP[cnt][0];
			if(0<cnt)SUM[0]=0;
			for(int i=2;i<=M;i++)
			{
				SUM[i]=SUM[i-2],SUM[i]+=DP[cnt][i];
				if(i<cnt)SUM[i]=0;
			}
			for(int i=0;i<=M;i+=2)
			{
				if(i>=cnt)DP[cnt+1][i]=SUM[i];
				else DP[cnt+1][i]=0;
			}
			for(int i=0;i<=M;i++)printf(" %d",DP[cnt][i]);puts("");
		}
		printf("%d\n",DP[M+1][M]);
	}
	return 0;
}
