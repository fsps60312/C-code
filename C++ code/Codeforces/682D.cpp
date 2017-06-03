#include<cstdio>
#include<cassert>
using namespace std;
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
int N,M,K;
char A[1002],B[1002];
int DP[1001][1001][11];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		scanf("%s%s",A+1,B+1);
		A[0]=0,B[0]=1;
		for(int i=0;i<=N;i++)for(int j=0;j<=M;j++)for(int k=0;k<=K;k++)DP[i][j][k]=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=M;j++)
			{
				for(int k=1;k<=K;k++)
				{
					getmax(DP[i][j][k],DP[i][j][k-1]);
					if(A[i]==B[j])
					{
						getmax(DP[i][j][k],DP[i-1][j-1][k-1]+1);
						if(A[i-1]==B[j-1])
						{
							getmax(DP[i][j][k],DP[i-1][j-1][k]+1);
						}
					}
//					else
					{
						getmax(DP[i][j][k],DP[i-1][j][k]);
						getmax(DP[i][j][k],DP[i][j-1][k]);
					}
//					printf("(%d,%d,%d)=%d\n",i,j,k,DP[i][j][k]);
				}
			}
		}
		int ans=0;
		for(int i=0;i<=K;i++)getmax(ans,DP[N][M][i]);
		printf("%d\n",ans);
	}
	return 0;
}
