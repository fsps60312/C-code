#include<cstdio>
#include<cassert>
using namespace std;
int GRID[4001][4001],SUM0[4001][4001];//SUM0[i][j]=GRID[1][j]+GRID[2][j]+...+GRID[i][j]
//F(i,j)=GRID[i][i]+GRID[i][i+1]+GRID[i+1][i+1]+GRID[i][i+2]+GRID[i+1][i+2]+GRID[i+2][i+2]+...+GRID[i][j]+GRID[i+1][j]+...+GRID[j][j]
//=(SUM0[i][i]-SUM0[i-1][i])+(SUM0[i+1][i+1]-SUM0[i-1][i+1])+(SUM0[i+2][i+2]-SUM0[i-1][i+2])+...+(SUM0[j][j]-SUM0[i-1][j])
//=(SUM0[i][i]+SUM0[i+1][i+1]+SUM0[i+2][i+2]+...+SUM0[j][j])-(SUM0[i-1][i]+SUM0[i-1][i+1]+SUM0[i-1][i+2]+...+SUM0[i-1][j])
//=(SUM1[j]-SUM1[i-1])-(SUM2[i-1][j]-SUM2[i-1][i-1])
int SUM1[4001];//SUM1[i]=SUM0[1][1]+SUM0[2][2]+SUM0[3][3]+...+SUM0[i][i]
int SUM2[4001][4001];//SUM2[i][j]=SUM0[i][i+1]+SUM0[i][i+2]+SUM0[i][i+3]+...+SUM0[i][j];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)scanf("%d",&GRID[i][j]);
		for(int j=1;j<=N;j++)
		{
			for(int i=1;i<=j;i++)SUM0[i][j]=SUM0[i-1][j]+GRID[i][j];
		}
	}
	return 0;
}
