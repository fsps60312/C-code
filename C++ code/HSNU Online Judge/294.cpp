#include<cstdio>
char GRID[100][101];
int N,X;
void swap(char &a,char &b){static char c;c=a,a=b,b=c;}
int Simulate(int r,int c)
{
	int ans=0;
	bool click=false;
	for(int counter=10000000;counter--;)
	{
		switch(GRID[r][c])
		{
			case'^':
			{
				if(--r<0)goto do_break;
				if(GRID[r][c]=='.')swap(GRID[r][c],GRID[r+1][c]),click=true;
				else if(click)ans++,click=false;
			}break;
			case'v':
			{
				if(++r>=N)goto do_break;
				if(GRID[r][c]=='.')swap(GRID[r][c],GRID[r-1][c]),click=true;
				else if(click)ans++,click=false;
			}break;
			case'<':
			{
				if(--c<0)goto do_break;
				if(GRID[r][c]=='.')swap(GRID[r][c],GRID[r][c+1]),click=true;
				else if(click)ans++,click=false;
			}break;
			case'>':
			{
				if(++c>=N)goto do_break;
				if(GRID[r][c]=='.')swap(GRID[r][c],GRID[r][c-1]),click=true;
				else if(click)ans++,click=false;
			}break;
		}
	}
	do_break:;
	return ans;
}
int main()
{
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&X)==2)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)GRID[i][j]='.';
			GRID[i][N]='\0';
			const int cnt=N/3;
			if(i&1)
			{
				int col=0;
				for(int j=0;j<cnt;j++)GRID[i][col++]='>';
				for(int j=0;j<cnt;j++)GRID[i][col++]='.',GRID[i][col++]='>';
				GRID[i][col-1]='^';
			}
			else
			{
				int col=0;
				for(int j=0;j<cnt;j++)GRID[i][col++]='<',GRID[i][col++]='.';
				for(int j=0;j<cnt;j++)GRID[i][col++]='<';
				GRID[i][0]='v';
			}
		}
//		for(int i=0;i<N;i++)puts(GRID[i]);
//		puts("1 1");
//		printf("%d\n",Simulate(0,0));
		for(int i=0;i<N;i++)puts(GRID[i]);
		puts("1 1");
		break;
	}
	return 0;
}
