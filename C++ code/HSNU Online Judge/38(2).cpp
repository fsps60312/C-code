#include<cstdio>
int M,N,P;
int PRICE[50][50];
int POWER[50][50];
int DP[50][10001];
void getmax(int &a,int b){if(b>a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&M,&N,&P)==3)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<P;j++)
			{
				scanf("%d%d",&PRICE[i][j],&POWER[i][j]);
			}
		}
		for(int j=0;j<N;j++)for(int i=0;i<=M;i++)DP[j][i]=0;
		for(int i=0;i<P;i++)getmax(DP[0][PRICE[0][i]],POWER[0][i]);
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<P;j++)
			{
				for(int k=M;k>=PRICE[i][j];k--)getmax(DP[i][k],DP[i-1][k-PRICE[i][j]]+POWER[i][j]);
				for(int k=M;k>=0;k--)getmax(DP[i][k],DP[i-1][k]);
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<=M;j++)
//			{
//				if(DP[i][j]!=-1)printf("(%d,%d):%d\n",i,j,DP[i][j]);
//			}
//		}
		int ans=0;
		for(int i=0;i<=M;i++)getmax(ans,DP[N-1][i]);
		printf("%d\n",ans);
	}
	return 0;
}
