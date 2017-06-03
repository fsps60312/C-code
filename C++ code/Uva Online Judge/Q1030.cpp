#include<cstdio>
int N;
char VIEW[6][10][10];
int DEP[6][10][10];
char CUBE[10][10][10];
void input()
{
	for(int r=0;r<N;r++)
	{
		for(int d=0;d<6;d++)
		{
			for(int c=0;c<N;c++)
			{
				char &v=VIEW[d][r][c]=getchar();
				if(!(v>='A'&&v<='Z')&&v!='.')
				{
					c--;
					continue;
				}
				DEP[d][r][c]=0;
			}
		}
	}
}
void showcube()
{
	for(int y=0;y<N;y++)
	{
		for(int z=0;z<N;z++)
		{
			for(int x=0;x<N;x++)
			{
				char &c=CUBE[x][y][z];
				printf("%c",c==0?'.':c);
			}
			printf("\n");
		}
		printf("\n");
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		input();
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				for(int k=0;k<N;k++)
				{
					CUBE[i][j][k]=-1;
				}
		int change=1;
		while(change)
		{
			change=0;
			for(int z=0;z<N;z++)
				for(int x=0;x<N;x++)
				{
					int i=x,j=z;
					int &dep=DEP[0][j][i];
					if(dep>=N)continue;
					char &view=VIEW[0][j][i],&cube=CUBE[x][dep][z];
					if(view=='.'||cube==0||(cube!=view&&cube!=-1))cube=0,dep++,change++;
					else if(cube==-1)cube=view;
				}
			for(int z=0;z<N;z++)
				for(int y=N-1;y>=0;y--)
				{
					int i=N-1-y,j=z;
					int &dep=DEP[1][j][i];
					if(dep>=N)continue;
					char &view=VIEW[1][j][i],&cube=CUBE[dep][y][z];
					if(view=='.'||cube==0||(cube!=view&&cube!=-1))cube=0,dep++,change++;
					else if(cube==-1)cube=view;
				}
			for(int z=0;z<N;z++)
				for(int x=N-1;x>=0;x--)
				{
					int i=N-1-x,j=z;
					int &dep=DEP[2][j][i];
					if(dep>=N)continue;
					char &view=VIEW[2][j][i],&cube=CUBE[x][N-1-dep][z];
					if(view=='.'||cube==0||(cube!=view&&cube!=-1))cube=0,dep++,change++;
					else if(cube==-1)cube=view;
				}
			for(int z=0;z<N;z++)
				for(int y=0;y<N;y++)
				{
					int i=y,j=z;
					int &dep=DEP[3][j][i];
					if(dep>=N)continue;
					char &view=VIEW[3][j][i],&cube=CUBE[N-1-dep][y][z];
					if(view=='.'||cube==0||(cube!=view&&cube!=-1))cube=0,dep++,change++;
					else if(cube==-1)cube=view;
				}
			for(int y=N-1;y>=0;y--)
				for(int x=0;x<N;x++)
				{
					int i=x,j=N-1-y;
					int &dep=DEP[4][j][i];
					if(dep>=N)continue;
					char &view=VIEW[4][j][i],&cube=CUBE[x][y][dep];
					if(view=='.'||cube==0||(cube!=view&&cube!=-1))cube=0,dep++,change++;
					else if(cube==-1)cube=view;
				}
			for(int y=0;y<N;y++)
				for(int x=0;x<N;x++)
				{
					int i=x,j=y;
					int &dep=DEP[5][j][i];
					if(dep>=N)continue;
					char &view=VIEW[5][j][i],&cube=CUBE[x][y][N-1-dep];
					if(view=='.'||cube==0||(cube!=view&&cube!=-1))cube=0,dep++,change++;
					else if(cube==-1)cube=view;
				}
		}
		int cnt=0;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				for(int k=0;k<N;k++)
				{
					if(CUBE[i][j][k]!=0)cnt++;
				}
		printf("Maximum weight: %d gram(s)\n",cnt);
	}
	return 0;
}
