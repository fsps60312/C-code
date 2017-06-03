#include<cstdio>
const int INF=2147483647;
int N,GRID[100][100];
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				scanf("%d",&GRID[i][j]);
				if(i==j)GRID[i][j]=0;
			}
		}
		for(int m=0;m<N;m++)
		{
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)
				{
					if(!GRID[i][m]||!GRID[m][j])continue;
					if(!GRID[i][j]||GRID[i][m]+GRID[m][j]<GRID[i][j])GRID[i][j]=GRID[i][m]+GRID[m][j];
				}
			}
		}
		int ans=INF;
		for(int i=0;i<N;i++)if(GRID[i][i]&&GRID[i][i]<ans)ans=GRID[i][i];
		if(ans==INF)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
