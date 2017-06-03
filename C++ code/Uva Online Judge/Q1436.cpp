#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int T,N;
LL MOD,SZ[500000];
vector<int>CH[500000];
LL BuildSZ(const int u)
{
	LL &ans=SZ[u]=1LL;
	for(int i=0;i<CH[u].size();i++)ans+=BuildSZ(CH[u][i]);
	return ans;
}
LL Dfs(const int u)
{
	LL ans=1LL;
	for(int i=0;i<CH[u].size();i++)ans*=Dfs(CH[u][i]);
	for(LL i=1;i<SZ[u];i++)ans*=i;
	for(int i=0;i<CH[u].size();i++)for(LL j=1;j<=SZ[CH[u][i]];j++)ans/=j;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%lld",&N,&MOD);
		for(int i=0;i<N;i++)CH[i].clear();
		for(int i=1,p;i<N;i++)scanf("%d",&p),CH[--p].push_back(i);
		BuildSZ(0);
		LL ans=Dfs(0);
		printf("%lld\n",ans);
	}
	return 0;
}
