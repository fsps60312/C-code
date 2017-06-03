#include<cstdio>
#include<cassert>
using namespace std;
int H,W;
char GRID[500][500];
int SUMV[500][500],SUMH[500][500];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&H,&W)==2)
	{
		for(int i=0;i<H;i++)for(int j=0;j<W;j++)
		{
			char &g=GRID[i][j];
			do{scanf("%c",&g);}while(g!='.'&&g!='#');
		}
		for(int i=1;i<H;i++)SUMV[i][0]=SUMV[i-1][0]+(GRID[i-1][0]=='.'&&GRID[i][0]=='.'?1:0);
		for(int i=1;i<W;i++)SUMH[0][i]=SUMH[0][i-1]+(GRID[0][i-1]=='.'&&GRID[0][i]=='.'?1:0);
		for(int i=1;i<H;i++)for(int j=1;j<W;j++)
		{
			SUMV[i][j]=SUMV[i-1][j]+SUMV[i][j-1]-SUMV[i-1][j-1]+(GRID[i-1][j]=='.'&&GRID[i][j]=='.'?1:0);
			SUMH[i][j]=SUMH[i-1][j]+SUMH[i][j-1]-SUMH[i-1][j-1]+(GRID[i][j-1]=='.'&&GRID[i][j]=='.'?1:0);
		}
		static int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			static int r1,c1,r2,c2;
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			r1--,c1--,r2--,c2--;
			printf("%d\n",SUMV[r2][c2]-SUMV[r1][c2]+(c1==0?0:-SUMV[r2][c1-1]+SUMV[r1][c1-1])+SUMH[r2][c2]-SUMH[r2][c1]+(r1==0?0:-SUMH[r1-1][c2]+SUMH[r1-1][c1]));
		}
		break;
	}
	return 0;
}
