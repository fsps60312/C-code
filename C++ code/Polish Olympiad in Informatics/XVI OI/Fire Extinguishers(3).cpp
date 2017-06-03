#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,S,K;
vector<int>ET[100000];
void AssignExtinguishers(int *supply,int *demand)
{
	for(int i=0;i<=K;i++)
	{
		const int val=min(supply[i],demand[i]);
		supply[i]-=val,demand[i]-=val;
	}
	for(int i=0;i<K;i++)
	{
		const int val=min(supply[i+1],demand[i]);
		supply[i+1]-=val,demand[i]-=val;
	}
}
void Dfs(const int u,const int parent,int *supply,int *demand,int &ans)
{
	for(int i=0;i<=K;i++)supply[i]=demand[i]=0;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		int *ch_supply=new int[K+1],*ch_demand=new int[K+1];
		Dfs(nxt,u,ch_supply,ch_demand,ans);
		for(int j=1;j<=K;j++)supply[j-1]+=ch_supply[j];
		for(int j=0;j<K;j++)demand[j+1]+=ch_demand[j];
		delete[]ch_supply;
		delete[]ch_demand;
	}
	++demand[0];
	AssignExtinguishers(supply,demand);
	const int need=(demand[K]+S-1)/S;
	ans+=need;
	supply[K]+=need*S;
	AssignExtinguishers(supply,demand);
	assert(!demand[K]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&S,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		int ans=0;
		int *supply=new int[K+1],*demand=new int[K+1];
		Dfs(0,-1,supply,demand,ans);
		for(int dis=0;dis<=K;dis++)
		{
			for(int i=0;i+dis<=K;i++)
			{
				const int val=min(supply[i+dis],demand[i]);
				supply[i+dis]-=val,demand[i]-=val;
			}
		}
		delete[]supply;
		int sum=0;
		for(int i=0;i<K;i++)sum+=demand[i];
		const int need=(sum+S-1)/S;
		ans+=need;
		delete[]demand;
		printf("%d\n",ans);
	}
	return 0;
}
