#include<cstdio>
#include<algorithm>
using namespace std;
int H,W,N,GRID[1000][1000],CNT[1001][1001];
int main()
{
	while(scanf("%d%d%d",&H,&W,&N)==3)
	{
		for(int i=0;i<H;i++)
		{
			for(int j=0;j<W;j++)
			{
				CNT[i][j]=0;
				scanf("%d",&GRID[i][j]);
			}
		}
		CNT[0][0]=N-1;
		for(int i=0;i<H-1+W-1;i++)
		{
			for(int x=max(i-(H-1),0);x<=min(W-1,i);x++)
			{
				int y=i-x;
//				printf("(%d,%d)\n",x,y);
				int &cnt=CNT[y][x],&g=GRID[y][x];
				CNT[y+1][x]+=(cnt>>1)+(cnt&(1^g)),CNT[y][x+1]+=(cnt>>1)+(cnt&g);
			}
		}
		int x=0,y=0;
		while(x<W&&y<H)
		{
			if((CNT[y][x]&1)^GRID[y][x])x++;
			else y++;
		}
		printf("%d %d\n",++y,++x);
//		for(int i=0;i<H;i++)
//		{
//			for(int j=0;j<W;j++)
//			{
//				printf(" %d",CNT[i][j]);
//			}puts("");
//		}
//		for(int i=0;i<H;i++)
//		{
//			for(int j=0;j<W;j++)
//			{
//				GRID[i][j]^=CNT[i][j]&1;
//				printf("%d",GRID[i][j]);
//			}puts("");
//		}
		break;
	}
	return 0;
}
