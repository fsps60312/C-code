#include<cstdio>
int GRID[1002][1002];
int N,M;
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)scanf("%d",&GRID[i][j]);
	for(int i=1;i<=N;i++)GRID[i][0]=GRID[i][M+1]=0;
	for(int i=1;i<=M;i++)GRID[0][i]=GRID[N+1][i]=0;
	int ans=0;
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
	{
		const int g=GRID[i][j];
		if(GRID[i-1][j]<g&&GRID[i][j-1]<g&&GRID[i+1][j]<g&&GRID[i][j+1]<g)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
