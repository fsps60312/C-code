#include<cstdio>
bool VIS[102][102][4];
char GRID[102][102];
int Dfs(const int r,const int c,const int d)
{
	if(VIS[r][c][d])return -1;
	VIS[r][c][d]=true;
	if(GRID[r][c]=='B')return 0;
	static int ds[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	const int lr=r+ds[(d+3)%4][0],lc=c+ds[(d+3)%4][1];
	if(GRID[lr][lc]=='X')
	{
		const int fr=r+ds[d][0],fc=c+ds[d][1];
		if(GRID[fr][fc]=='X')return Dfs(r,c,(d+1)%4);
		else
		{
			int a=Dfs(fr,fc,d);
			return a==-1?-1:a+1;
		}
	}
	else
	{
		int a=Dfs(lr,lc,(d+3)%4);
		return a==-1?-1:a+1;
	}
}
int R,C,D;
int main()
{
	scanf("%d%d%d",&R,&C,&D),(D+=2)%=4;
	for(int i=1;i<=R;i++)scanf("%s",GRID[i]+1);
	for(int i=1;i<=R;i++)GRID[i][0]=GRID[i][C+1]='X';
	for(int i=1;i<=C;i++)GRID[0][i]=GRID[R+1][i]='X';
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)for(int d=0;d<4;d++)VIS[i][j][d]=false;
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)if(GRID[i][j]=='A'){printf("%d\n",Dfs(i,j,D));break;}
	return 0;
}
