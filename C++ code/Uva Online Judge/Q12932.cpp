#include<cstdio>
int N,M,GRID[501][501],SUM[501][501];
void BuildSum()
{
	for(int i=0;i<=M;i++)SUM[0][i]=0;
	for(int i=0;i<=N;i++)SUM[i][0]=0;
	for(int i=1;i<=N;i++)
	{
		for(int j=0;j<=M;j++)
		{
			SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+GRID[i][j];
		}
	}
}
int Area(int a,int b,int c,int d){a--,b--;return SUM[c][d]-SUM[a][d]-SUM[c][b]+SUM[a][b];}
int Wrong()
{
	int asum=0,bsum=0,a,b;
	for(int i=1;i<=N;i++)if(Area(i,1,i,M)>asum)asum=Area(i,1,i,M),a=i;
	for(int i=1;i<=M;i++)if(Area(1,i,N,i)>bsum)bsum=Area(1,i,N,i),b=i;
	return asum+bsum-GRID[a][b];
}
int Correct()
{
	int mn=2147483647;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
		{
			int v=Area(1,1,i-1,j-1)+Area(i+1,j+1,N,M)+Area(1,j+1,i-1,M)+Area(i+1,1,N,j-1);
			if(v<mn)mn=v;
		}
	}
	return Area(1,1,N,M)-mn;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=M;j++)
			{
				scanf("%d",&GRID[i][j]);
			}
		}
		BuildSum();
		int a=Wrong(),b=Correct();
//		printf("a=%d b=%d\n",a,b);
		static int kase=1;
		printf("Case %d: %s\n",kase++,a==b?"Weak":"Strong");
	}
	return 0;
}
