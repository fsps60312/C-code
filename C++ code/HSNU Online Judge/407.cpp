#include<bits/stdc++.h>
using namespace std;
const int MOD=1000000007;
int N,L,DP[100][100][100];
char GRID[100][101],S[101];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%s",GRID[i]);
	scanf("%d%s",&L,S);
	for(int r=0;r<N;r++)
	{
		for(int c=0;c<N;c++)
		{
			DP[0][r][c]=(GRID[r][c]==S[0]?1:0);
		}
	}
	for(int i=1;i<L;i++)
	{
		for(int r=0;r<N;r++)
		{
			for(int c=0;c<N;c++)
			{
				int &dp=DP[i][r][c]=0;
				if(GRID[r][c]!=S[i]){continue;}
				static int d[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
				for(int j=0;j<8;j++)
				{
					int a=r+d[j][0],b=c+d[j][1];
					if(a>=0&&b>=0&&a<N&&b<N)dp+=DP[i-1][a][b],dp%=MOD;
				}
//				printf(" %d",DP[i][r][c]);
			}
//			puts("");
		}
	}
	int ans=0;
	for(int r=0;r<N;r++)
	{
		for(int c=0;c<N;c++)
		{
			ans+=DP[L-1][r][c],ans%=MOD;
		}
	}
	printf("%d\n",ans);
	return 0;
}
