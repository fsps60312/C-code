#include<cstdio>
#include<cassert>
using namespace std;
int GRID[4001][4001],SUM[4001][4001];
//f(i,j)=GRID[i][i]+GRID[i+1][i+1]+...+GRID[j][j]+GRID[i][i+1]+GRID[i+1][i+2]+...+GRID[j-1][j]+...+GRID[i][j-1]+GRID[i+1][j]+GRID[i][j]
//=(SUM[j][0]-SUM[i-1][0])+(SUM[j-1][1]-SUM[i-1][1])+...+(SUM[i+1][i-j]-SUM[i-1][i-j])+(SUM[i][i-j+1]-SUM[i-1][i-j+1])
//=()
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
