#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
int NOW[10],ANS[10],RECORD;
bool VIS[10][4084];
int N,M;
void Dfs(const int dep)
{
	if(dep==N)
	{
		int record;
		for(record=NOW[dep-1];VIS[dep-1][record+1];record++);
		if(record>RECORD)
		{
			RECORD=record;
			for(int i=0;i<N;i++)ANS[i]=NOW[i];
		}
		return;
	}
	for(int &v=NOW[dep]=NOW[dep-1]+1;;v++)
	{
		for(int i=0;i<=4083;i++)VIS[dep][i]=VIS[dep-1][i];
		for(int i=0;i+v<=4083;i++)VIS[dep][i+v]|=VIS[dep-1][i];
		Dfs(dep+1);
		if(!VIS[dep-1][v])break;
	}
}
int main()
{
	while(scanf("%d%d",&M,&N)==2)
	{
		NOW[0]=1,RECORD=-1;
		for(int i=0;i<N;i++)for(int j=0;j<=4083;j++)VIS[i][j]=false;
		for(int i=0;i<=N;i++)VIS[0][i]=true;
		Dfs(1);
		printf("%d\n",RECORD);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
