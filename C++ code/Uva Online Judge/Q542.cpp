#include<cstdio>
#include<cassert>
using namespace std;
char NAME[16][100];
double GRID[16][16],DP[16][4];
double GetDP(const int country,const int stage)
{
	if(stage==-1)return 1.0;
	double &dp=DP[country][stage];
	if(dp!=-1.0)return dp;
	dp=0.0;
//	for(int i=0;i<(1<<stage);i++)
//	{
//		const int oppo=(country^(1<<stage))+i;
//		printf("(%d,%d)\n",country,oppo);
//	}
	for(int i=0;i<(1<<stage);i++)
	{
		const int oppo=(country&(~((1<<stage)-1))^(1<<stage))+i;
		assert((oppo&((1<<stage)-1))==i);
		dp+=GRID[country][oppo]*GetDP(oppo,stage-1);
	}
	dp*=GetDP(country,stage-1);
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<16;i++)fgets(NAME[i],100,stdin);
	for(int i=0;i<16;i++)for(int j=0;j<16;j++)scanf("%lf",&GRID[i][j]),GRID[i][j]/=100.0;
//	for(int i=0;i<16;i++)
//	{
//		for(int j=0;j<16;j++)printf(" %2.3f",GRID[i][j]);puts("");
//	}
	for(int i=0;i<16;i++)for(int j=0;j<=3;j++)DP[i][j]=-1.0;
	double sum=0.0;
	for(int c=0;c<16;c++)
	{
		char *name=NAME[c];
		for(int i=0;;i++)
		{
			if(name[i]=='\0'||name[i]=='\n')
			{
				while(i++<11)putchar(' ');
				break;
			}
			putchar(name[i]);
		}
		printf("p=%.2f%%\n",100.0*GetDP(c,3));
		sum+=GetDP(c,3);
	}
//	printf("sum=%.3f\n",sum);
//	for(int i=0;i<16;i++)
//	{
//		for(int s=0;s<=3;s++)printf(" %.3f",DP[i][s]);puts("");
//	}
	return 0;
}
