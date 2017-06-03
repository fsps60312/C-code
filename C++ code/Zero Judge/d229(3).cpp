#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
int NOW[11],ANS[11],RECORD;
bool VIS[11][11][4084];
int BOUND[11][11];
int N,M;
void Update(bool *from,bool *to,const int item)
{
	for(int i=4083-item;i>=0;i--)to[i+item]|=from[i];
}
void Dfs(const int dep)
{
	if(dep==M)
	{
		int record;
		for(record=NOW[M-1];VIS[M-1][N][record+1];record++);
		if(record>RECORD)
		{
			RECORD=record;
			for(int i=0;i<M;i++)ANS[i]=NOW[i];
		}
		return;
	}
	for(int &v=NOW[dep]=NOW[dep-1]+1;;v++)
	{
		for(int n=0;n<=N;n++)
		{
			for(int i=0;i<=4083;i++)VIS[dep][n][i]=VIS[dep-1][n][i];
			for(int i=1;i<=n;i++)Update(VIS[dep-1][n-i],VIS[dep][n],i*v);
		}
//		for(int n=0;n<=N;n++)for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)Update(VIS[dep-1][i],VIS[dep][n],j*v);
		Dfs(dep+1);
		if(!VIS[dep-1][N][v])break;
	}
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		NOW[0]=1,RECORD=-1;
		for(int i=0;i<M;i++)for(int j=0;j<=N;j++)for(int k=0;k<=4083;k++)VIS[i][j][k]=false;
		for(int i=0;i<=N;i++)for(int j=0;j<=i;j++)VIS[0][i][j]=true;
		Dfs(1);
		printf("%d\n",RECORD);
		for(int i=0;i<M;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
