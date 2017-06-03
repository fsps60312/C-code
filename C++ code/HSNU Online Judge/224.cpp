#include<cstdio>
#include<vector>
using namespace std;
struct Hungary
{
	int N,MATCH[900];
	bool VB[900];
	vector<int>ET[900];
	bool Match(const int u)
	{
		for(const int nxt:ET[u])if(!VB[nxt])
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
			for(int j=0;j<N;j++)VB[j]=false;
			if(Match(i))ans++;
		}
		return ans;
	}
}HGY;
int N,M,A,B;
int GRID[30][30];
int main()
{
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d%d",&N,&M,&A,&B);
		HGY.N=N*M;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf("%d",&GRID[i][j]);
	}
	return 0;
}
