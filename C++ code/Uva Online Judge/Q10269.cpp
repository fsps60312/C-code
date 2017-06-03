#include<cstdio>
#include<vector>
using namespace std;
int INF=(1<<30)-1;
int T,A,B,M,L,K,N;
int AD[100][100];
int DP[11][100][100];
void solve()
{
	for(int k=0;k<=K;k++)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(k==0)DP[k][i][j]=AD[i][j];
				else if(k==1)DP[k][i][j]=AD[i][j]<=L?0:INF;
				else DP[k][i][j]=INF;
			}
		}
	}
	for(int i=0;i<N;i++)
	{
		for(int m=0;m<N;m++)
		{
			for(int j=0;j<N;j++)
			{
				if(AD[m][j]==INF)continue;
				for(int k=0;k<=K;k++)
				{
					getmin(DP[k][i][j],DP[k][i][m]+AD[m][j]);
					if(m<A&&AD[m][j]<=L)
				}
			}
		}
	}
}
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d%d%d",&A,&B,&M,&L,&K);
			N=A+B;
			for(int i=0;i<N;i++)for(int j=0;j<N;j++)AD[i][j]=INF;
			for(int i=0;i<M;i++)
			{
				static int a,b,l;scanf("%d%d%d",&a,&b,&l);
				a--,b--;
				AD[a][b]=AD[b][a]=l;
			}
			solve();
			int ans=INF;
			for(int i=0;i<K;i++)getmin(ans,DP[i][0][N-1]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
