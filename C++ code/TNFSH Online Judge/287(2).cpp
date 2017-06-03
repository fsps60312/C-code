#include<cstdio>
#include<cassert>
using namespace std;
struct Hungary
{
	bool VA[200],VB[200],EDGE[200][200];
	int N,MATCH[200];
	void Build(const int n,const int m)
	{
		N=n;
		for(int i=0;i<N*N;i++)EDGE[i/N][i%N]=false;
		for(int i=0,a,b;i<m;i++)
		{
			assert(scanf("%d%d",&a,&b)==2);
			a--,b--;
			EDGE[a][b]=true;
		}
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
	int Solve()
	{
		for(int i=0;i<N;i++)MATCH[i]=-1;
		int ans=0;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VA[j]=VB[j]=false;
			if(Match(i))ans++;
		}
		return N-ans;
	}
}HUNGARY;
int N,M;
int main()
{
	static int casecnt;assert(scanf("%d",&casecnt)==1);
	while(casecnt--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		HUNGARY.Build(N,M);
		printf("%d\n",HUNGARY.Solve());
	}
	return 0;
}
