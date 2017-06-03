#include<cstdio>
#include<cassert>
#include<vector>
#include<utility> 
using namespace std;
struct Hungary
{
	bool VA[200],VB[200],EDGE[200][200];
	int N,MATCH[200];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(!VB[nxt]&&EDGE[u][nxt])
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
	void Solve(const int _N,vector<pair<int,int> >&ans)
	{
		N=_N;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=true;
		for(int i=0;i<N;i++)EDGE[i][i]=false;
		for(int count=0;count<N-1;count++)
		{
			for(int i=0;i<N;i++)MATCH[i]=-1;
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)VA[j]=VB[j]=false;
				assert(Match(i));
			}
			for(int i=0;i<N;i++)
			{
				ans.push_back(make_pair(MATCH[i],i));
				EDGE[MATCH[i]][i]=false;
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
