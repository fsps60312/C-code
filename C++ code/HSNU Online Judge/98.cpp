#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,K,M;
vector<int>ET[1000000];
int DP[1000000][2],PRE[1000000][2];
void Dfs(const int u,const int fa)
{
	DP[u][0]=DP[u][1]=0;
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		Dfs(nxt,u);
		DP[u][0]+=DP[nxt][1];
		
	}
}
int Solve()
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		if(DP[i][0]!=INF)continue;
		ans+=Dfs(i,-1);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&M);
	for(int i=0;i<N;i++)
	{
		ET[i].clear();
		DP[i][0]=DP[i][1]=INF;
	}
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b);
		a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	printf("%d\n",Solve());
	return 0;
}
