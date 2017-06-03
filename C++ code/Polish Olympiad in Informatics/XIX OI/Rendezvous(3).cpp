#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,K,PARENT[500000],CLOC[500000],CID[500000];
vector<vector<int> >CYCLE;
void BuildCycle()
{
	static int vis[500000],kase;
	for(int i=0;i<N;i++)vis[i]=0,CID[i]=-1-i;
	kase=1;
	CYCLE.clear();
	for(int u=0;u<N;u++,kase++)
	{
		int cur=u;
		for(;vis[cur]==0;cur=PARENT[cur])vis[cur]=kase;
		if(vis[cur]!=kase)continue;
		vector<int>cyc;
		for(;vis[cur]==kase;cur=PARENT[cur])vis[cur]=kase+1,cyc.push_back(cur);
		kase++;
		for(int i=0;i<(int)cyc.size();i++)PARENT[cyc[i]]=cyc[i],CLOC[cyc[i]]=i,CID[cyc[i]]=(int)CYCLE.size();
		CYCLE.push_back(cyc);
	}
}
vector<int>ET[500000],PARENTS[500000];
int DEPTH[500000];
void Dfs(const int u,const int parent,const int depth,const int cid,const int cloc)
{
	DEPTH[u]=depth;
	CID[u]=cid,CLOC[u]=cloc;
	PARENTS[u].clear();
	if(parent!=-1)
	{
		for(int cur=parent,i=0;;cur=PARENTS[cur][i++])
		{
			PARENTS[u].push_back(cur);
			if((1<<i)>DEPTH[cur])break;
		}
	}
	for(int i=0;i<(int)ET[u].size();i++)Dfs(ET[u][i],u,depth+1,cid,cloc);
}
void BuildTrees()
{
	for(int i=0;i<N;i++)ET[i].clear();
	vector<int>roots; 
	for(int i=0;i<N;i++)
	{
		if(PARENT[i]==i)roots.push_back(i);
		else ET[PARENT[i]].push_back(i);
	}
	for(int i=0;i<(int)roots.size();i++)Dfs(roots[i],-1,0,CID[roots[i]],CLOC[roots[i]]);
}
#include<utility>
pair<int,int>Best(const pair<int,int>&a,const pair<int,int>&b)
{
	int av=max(a.first,a.second),bv=max(b.first,b.second);
	if(av!=bv)return av<bv?a:b;
	av=min(a.first,a.second),bv=min(b.first,b.second);
	if(av!=bv)return av<bv?a:b;
	return a.first>=a.second?a:b;
}
int LowestCommonAncestor(int a,int b)
{
	if(DEPTH[a]>DEPTH[b])swap(a,b);
	for(int dis=DEPTH[b]-DEPTH[a],i=30;i>=0;i--)if(dis&(1<<i))b=PARENTS[b][i];
	assert(DEPTH[a]==DEPTH[b]);
	if(a==b)return a;
	for(int i=30;i>=0;i--)if((1<<i)<=DEPTH[a]&&PARENTS[a][i]!=PARENTS[b][i])a=PARENTS[a][i],b=PARENTS[b][i];
	return PARENTS[a][0];
}
pair<int,int>Solve(const int a,const int b)
{
	if(CID[a]!=CID[b])return make_pair(-1,-1);
	if(CLOC[a]!=CLOC[b])
	{
		const int dis=(CLOC[a]>CLOC[b]?CLOC[a]-CLOC[b]:CLOC[a]+(int)CYCLE[CID[a]].size()-CLOC[b]);
		return Best(make_pair(DEPTH[a],DEPTH[b]+dis),make_pair(DEPTH[a]+((int)CYCLE[CID[a]].size()-dis),DEPTH[b]));
	}
	else
	{
		const int lca=LowestCommonAncestor(a,b);
		return make_pair(DEPTH[a]-DEPTH[lca],DEPTH[b]-DEPTH[lca]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&PARENT[i]),PARENT[i]--;
		BuildCycle();
		BuildTrees();
		for(int i=0,a,b;i<K;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			const pair<int,int>&ans=Solve(a,b);
			printf("%d %d\n",ans.first,ans.second);
		}
	}
	return 0;
}
