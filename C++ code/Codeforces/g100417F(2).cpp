#include<cstdio>
#include<cassert>
#include<vector>
#include<utility> 
using namespace std;
struct Hungary
{
	bool VA[200],VB[200],EDGE[200][200];
	int N,MA[200],MB[200];
	bool MatchA(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(!VB[nxt]&&EDGE[u][nxt])
		{
			VB[nxt]=true;
			if(MA[nxt]==-1||MatchA(MA[nxt]))
			{
				MA[nxt]=u;
				MB[u]=nxt;
				return true;
			}
		}
		return false;
	}
	bool MatchB(const int u)
	{
		if(VB[u])return false;
		VB[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(!VA[nxt]&&EDGE[nxt][u])
		{
			VA[nxt]=true;
			if(MB[nxt]==-1||MatchB(MB[nxt]))
			{
				MB[nxt]=u;
				MA[u]=nxt;
				return true;
			}
		}
		return false;
	}
	void Solve(const int _N,vector<pair<int,int> >&ans)
	{
		N=_N;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=(i<j);
		for(int i=0;i<N;i++)EDGE[i][i]=false;
		for(int count=0;count<N-1;count++)
		{
			for(int i=0;i<N;i++)MA[i]=MB[i]=-1;
			printf("count=%d\n",count);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)VA[j]=VB[j]=false;
				if(!MatchA(i))
				{
					for(int j=0;j<N;j++)VA[j]=VB[j]=false;
					assert(MatchB(i));
				}
			}
			for(int i=0;i<N;i++)
			{
				ans.push_back(make_pair(MA[i],i));
				EDGE[MA[i]][i]=false;
			}
		}
	}
}HUNGARY;
int N,K;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	vector<pair<int,int> >ans;
	HUNGARY.Solve(N*2,ans);
	scanf("%d",&K);
	for(int i=0,v,sum=0;i<K;i++)
	{
		scanf("%d",&v);
		for(int j=sum;j<sum+v*N;j++)printf("%d %d\n",ans[j].first+1,ans[j].second+1);
		sum+=v*N;
	}
	return 0;
}
