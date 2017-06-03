#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
#include<set>
using namespace std;
int N,M,D[300000];
vector<int>ET[300000];
int LOC[300000],DEPTH[300000],PARENT[300000];
pair<int,int>U[21][600000];
int B[600000];
void Dfs(const int u,const int parent,const int depth,int &cnt)
{
	PARENT[u]=parent;
	DEPTH[u]=depth;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		Dfs(ET[u][i],u,depth+1,cnt);
		U[0][LOC[u]=cnt++]=make_pair(depth,u);
	}
}
void BuildSparse(const int n)
{
	for(int bit=1;(1<<bit)<=n;bit++)for(int i=0;i+(1<<bit)<=n;i++)
	{
		U[bit][i]=min(U[bit-1][i],U[bit-1][i+(1<<(bit-1))]);
	}
	for(int i=0;i<n;i++)
	{
		for(int &j=B[i];(1<<(j+1))<=i+1;j++);
	}
}
pair<int,int>QuerySparse(const int a,const int b)
{
//	if(a>b)return QuerySparse(b,a);
	assert(a<=b);
	const int bit=B[b-a];
	assert(b-(1<<(bit+1))+1<a&&b-(1<<bit)+1>=a);
	return min(U[bit][a],U[bit][b-(1<<bit)+1]);
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
			const pair<int,int>&p=QuerySparse(LOC[u],*it);
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
