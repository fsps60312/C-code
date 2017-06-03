#include<cstdio>
#include<cassert>
using namespace std;
struct Hungary
{
	int N,M,MATCH[100];
	bool EDGE[100][100],VB[100];
	bool Match(const int u)
	{
		for(int nxt=0;nxt<M;nxt++)if(EDGE[u][nxt]&&!VB[nxt])
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
		for(int i=0;i<M;i++)MATCH[i]=-1;
		int ans=0;
		for(int i=0;i<N;i++)
		{
//			for(int j=0;j<N;j++)VA[j]=false;
			for(int j=0;j<M;j++)VB[j]=false;
			if(Match(i))ans++;
		}
		return ans;
	}
}HUNGARY;
int A[100],B[100];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int &N=HUNGARY.N,&M=HUNGARY.M;
		scanf("%d",&N);for(int i=0;i<N;i++)scanf("%d",&A[i]);
		scanf("%d",&M);for(int i=0;i<M;i++)scanf("%d",&B[i]);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)
		{
			bool &ans=HUNGARY.EDGE[i][j];
			if(A[i]==0)ans=(B[j]==0);
			else ans=(B[j]%A[i]==0);
		}
		static int kase=1;
		printf("Case %d: %d\n",kase++,HUNGARY.Solve());
	}
	return 0;
}
