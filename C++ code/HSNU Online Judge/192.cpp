#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,GRID[300][300],DP[2][300][300];
int GetSoap(const int i0,const int j0,const int i1,const int j1)
{
	if(i0==i1&&j0==j1)return GRID[i0][j0];
	return GRID[i0][j0]+GRID[i1][j1];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%d",&GRID[i][j]);
		for(int d=0;d<2;d++)for(int i=0;i<N;i++)for(int j=i;j<N;j++)DP[d][i][j]=-INF;
		DP[0][0][0]=GRID[0][0];
		int d=0;
		for(int sum=0;sum<(N-1)*2;sum++,d^=1)
		{
			for(int i0=0,j0;i0<=sum&&i0<N;i0++)if((j0=sum-i0)<N)
			{
				for(int i1=i0,j1;i1<=sum&&i1<N;i1++)if((j1=sum-i1)<N)
				{
					const int dp=DP[d][i0][i1];if(dp==-INF)continue;
					if(i0+1<N)
					{
						if(i1+1<N)getmax(DP[d^1][i0+1][i1+1],dp+GetSoap(i0+1,j0,i1+1,j1));
						if(j1+1<N&&i0+1<=i1)getmax(DP[d^1][i0+1][i1],dp+GetSoap(i0+1,j0,i1,j1+1));
					}
					if(j0+1<N)
					{
						if(i1+1<N)getmax(DP[d^1][i0][i1+1],dp+GetSoap(i0,j0+1,i1+1,j1));
						if(j1+1<N)getmax(DP[d^1][i0][i1],dp+GetSoap(i0,j0+1,i1,j1+1));
					}
					DP[d][i0][i1]=-INF;
				}
			}
		}
		printf("%d\n",DP[d][N-1][N-1]);
		break;
	}
	return 0;
}
