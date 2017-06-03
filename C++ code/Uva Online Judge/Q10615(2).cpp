#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');}
char GRID[100][101];
struct Hungary
{
	int N,DA[100],DB[100],MATCH[100],C;
	bool VA[100],VB[100];
	int EDGE[100][100];
	void AddEdge(const int a,const int b){EDGE[a][b]++;C=max(C,max(++DA[a],++DB[b]));}
	void Build()
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=0;
		for(int i=0;i<N;i++)DA[i]=DB[i]=0;
		C=0;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			if(GRID[i][j]=='*')AddEdge(i,j);
			else assert(GRID[i][j]=='.');
		}
		for(int i=0;i<N;i++)for(int j=0;j<N&&DA[i]<C;j++)while(DA[i]<C&&DB[j]<C)AddEdge(i,j);
		for(int i=0;i<N;i++)assert(DA[i]==C&&DB[i]==C);
	}
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(EDGE[u][nxt])
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
		return false;
	}
	int ANS[100][100];
	void Solve()
	{
		for(int i=0;i<N*N;i++)ANS[i/N][i%N]=0;
		for(int color=1;color<=C;color++)
		{
			for(int i=0;i<N;i++)MATCH[i]=-1;
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)VA[j]=VB[j]=false;
				assert(Match(i));
			}
			for(int b=0;b<N;b++)
			{
				const int a=MATCH[b];
				if(a==-1)continue;
				assert(a!=-1);
				ANS[a][b]=color;
				EDGE[a][b]--;
			}
		}
	}
}HUNGARY;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d",&N)==1);
		for(int i=0;i<N;i++)assert(scanf("%s",GRID[i])==1);
		HUNGARY.N=N;
		HUNGARY.Build();
		HUNGARY.Solve();
		printf("%d\n",HUNGARY.C);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(j)putchar(' ');
				if(GRID[i][j]=='.')putchar('0');
				else printf("%d",HUNGARY.ANS[i][j]);
			}
			puts("");
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
