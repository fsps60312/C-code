#include<cstdio>
#include<vector>
using namespace std;
int N,M,DEG[1000];
bool VIS[1000];
vector<int>TO[1000];
int dfs(int u)
{
	if(VIS[u])return 0;
	VIS[u]=true;
	int ans=TO[u].size()==1?1:0;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		ans+=dfs(j);
	}
	return ans;
}
int solve()
{
	int ans=0,cnt=0;
	for(int i=0;i<N;i++)if(!VIS[i])ans+=max(dfs(i)-2,0),cnt++;
	return ans+cnt;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			DEG[i]=0;
			VIS[i]=false;
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			TO[a].push_back(b);
			TO[b].push_back(a);
			DEG[a]++,DEG[b]++;
		}
		printf("%d\n",solve());
	}
	return 0;
}
