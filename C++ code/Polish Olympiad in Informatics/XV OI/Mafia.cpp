#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void DeleteEdge(vector<int>&s,const int v)
{
	for(int i=0;i<(int)s.size();i++)if(s[i]==v){s.erase(s.begin()+i);return;}
	for(int i=0;i<(int)s.size();i++)printf(" %d",s[i]+1);
	printf(", v=%d\n",v+1);
	assert(0);
}
int N,S[1000000];
vector<int>ET[1000000];
void MarkVisited(const int u,bool *vis)
{
	vis[u]=true;
	for(int i=0;i<(int)ET[u].size();i++)MarkVisited(ET[u][i],vis);
}
int CountSum(const int u)
{
	int ans=1;
	for(int i=0;i<(int)ET[u].size();i++)ans+=CountSum(ET[u][i]);
	return ans;
}
int CountLeaf(const int u)
{
	if(ET[u].empty())return 1;
	int ans=0;
	for(int i=0;i<(int)ET[u].size();i++)ans+=CountSum(ET[u][i]);
	return ans;
}
int MATCH[1000000][2];
int GetMatch(const int u,const int color)
{
	int &dp=MATCH[u][color];
	if(dp!=-1)return dp;
	dp=color;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		if(color)dp+=GetMatch(ET[u][i],0);
		else dp+=max(GetMatch(ET[u][i],0),GetMatch(ET[u][i],1));
	}
	return dp;
}
const int INF=2147483647;
int Add(const int a,const int b)
{
	if(a==-INF||b==-INF)return -INF;
	return a+b;
}
int SolveMin(const int sz,const vector<int>&cycle)
{
	const int n=(int)cycle.size();
	static int dp[1000000][2][2];
	dp[0][0][1]=dp[0][1][0]=-INF;
	dp[0][0][0]=GetMatch(cycle[0],0);
	dp[0][1][1]=GetMatch(cycle[0],1);
	for(int i=1;i<n;i++)
	{
		const int v0=GetMatch(cycle[i],0),v1=GetMatch(cycle[i],1);
		for(int f=0;f<2;f++)
		{
			dp[i][f][0]=max(Add(dp[i-1][f][1],v0),Add(dp[i-1][f][0],v0));
			dp[i][f][1]=Add(dp[i-1][f][0],v1);
		}
	}
//	printf("sz=%d,live=%d\n",sz);
	return sz-max(dp[n-1][0][0],max(dp[n-1][0][1],dp[n-1][1][0]));
}
int SolveMax(const int sz,const vector<int>&cycle)
{
	const int n=(int)cycle.size();
	int live=0;
	for(int i=0;i<n;i++)if(!ET[cycle[i]].empty())live+=CountLeaf(cycle[i]);
	if(!live)++live;
//	printf("sz=%d,live=%d\n",sz,live);
	return sz-live;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&S[i]),ET[--S[i]].push_back(i);
		static bool vis[1000000];
		for(int i=0;i<N;i++)vis[i]=false,MATCH[i][0]=MATCH[i][1]=-1;
		int ans_min=0,ans_max=0;
		for(int i=0;i<N;i++)if(!vis[i])
		{
			vector<int>cycle;
			int cur=i;
			for(;!vis[cur];cur=S[cur])vis[cur]=true;
			for(;vis[cur];cur=S[cur])vis[cur]=false,cycle.push_back(cur);
			const int n=(int)cycle.size();
			for(int j=0;j<n;j++)DeleteEdge(ET[cycle[(j+1)%n]],cycle[j]);
			for(int j=0;j<n;j++)MarkVisited(cycle[j],vis);
			int sz=0;
			for(int j=0;j<n;j++)sz+=CountSum(cycle[j]);
			ans_min+=SolveMin(sz,cycle);
			ans_max+=SolveMax(sz,cycle);
		}
		printf("%d %d\n",ans_min,ans_max);
	}
	return 0;
}
