#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
#include<set>
using namespace std;
int N,M,D[300000];
vector<int>ET[300000];
int LOC[300000],DEPTH[300000];
vector<int>PARENT[300000];
int U[600000];
int B[600000];
void Dfs(const int u,const int parent,const int depth,int &cnt)
{
	PARENT[u].clear();
	if(parent!=-1)
	{
		for(int cur=parent,i=0;;cur=PARENT[cur][i++])
		{
			PARENT[u].push_back(cur);
			if(DEPTH[cur]<(1<<i))break;
		}
	}
	DEPTH[u]=depth;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		U[0][LOC[u]=cnt++]=make_pair(depth,u);
		Dfs(ET[u][i],u,depth+1);
	}
}
int Lca(int a,int b)
{
	if(DEPTH[a]>DEPTH[b])swap(a,b);
	for(int dis=DEPTH[b]-DEPTH[a],i=0;(1<<i)<=dis;i++)if(dis&(1<<i))b=PARENT[b][i];
	assert(DEPTH[a]==DEPTH[b]);
	if(a==b)return a;
	for(int i=19;i>=0;i--)if((1<<i)<=DEPTH[a]&&PARENT[a][i]!=PARENT[b][i])a=PARENT[a][i],b=PARENT[b][i];
	return PARENT[a][0];
}
int Solve(const int len)
{
	vector<pair<int,int> >order;
	for(int i=0;i<N;i++)if(D[i])order.push_back(make_pair(DEPTH[i],i));
	sort(order.begin(),order.end());
	set<int>fire;
	for(int i=(int)order.size()-1;i>=0;i--)
	{
		const int u=order[i].second;
		set<int>::iterator it=fire.lower_bound(LOC[u]);
//		printf("dep[%d]=%d\n",u,DEPTH[u]);
		if(it!=fire.end())
		{
			const int dep=Lca(LOC[u],*it);
//			printf("lca.dep=%d(%d)\n",p.first,p.second);
			if((U[0][LOC[u]].first-p.first)+(U[0][*it].first-p.first)<=len)continue;
		}
		if(it!=fire.begin())
		{
			const pair<int,int>&p=QuerySparse(*--it,LOC[u]);
//			printf("lca.dep=%d(%d)\n",p.first,p.second);
			if((U[0][LOC[u]].first-p.first)+(U[0][*it].first-p.first)<=len)continue;
		}
		int cur=u;
		for(int j=0;j<len&&PARENT[cur]!=-1;j++,cur=PARENT[cur]);
		fire.insert(LOC[cur]);
//		printf("insert(CUR[%d]=%d)\n",cur,LOC[cur]);
	}
//	printf("len=%d,ans=%d\n",len,(int)fire.size());
	return (int)fire.size();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&D[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(true)
		{
			int cnt=0;
			Dfs(0,-1,0,cnt);
			BuildSparse(cnt);
		}
		int l=0,r=N-1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid)<=M)r=mid;
			else l=mid+1;
		}
		printf("%d\n",r);
	}
	return 0;
}
