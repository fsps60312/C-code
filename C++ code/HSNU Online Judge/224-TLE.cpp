#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
int N,M,A,B;
int VIEW[30*30];
int GRID[30*30];
int ANS;
void Dfs(const int dep)
{
	if(dep==N*M)
	{
		for(int i=0;i<N*M;i++)assert(GRID[i]==-1||GRID[i]==1);
		int ans=0;
		for(int i=0;i+A<N;i++)for(int j=0;j<M;j++)
		{
			if(j-B>=0&&GRID[i*M+j]!=GRID[(i+A)*M+j-B])ans++;
			if(j+B<M&&GRID[i*M+j]!=GRID[(i+A)*M+j+B])ans++;
		}
		if(ans>ANS)
		{
			ANS=ans;
			for(int i=0;i<N*M;i++)VIEW[i]=GRID[i];
		}
		return;
	}
	if(GRID[dep]!=0){Dfs(dep+1);return;}
	GRID[dep]=-1;
	Dfs(dep+1);
	GRID[dep]=1;
	Dfs(dep+1);
	GRID[dep]=0;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d%d",&N,&M,&A,&B);
		for(int i=0;i<N*M;i++)scanf("%d",&GRID[i]);
		ANS=0;
		Dfs(0);
		printf("%d\n",ANS);
		continue;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)printf("%c ",VIEW[i*M+j]==-1?'n':'p');
			puts("");
		}
	}
	return 0;
}
