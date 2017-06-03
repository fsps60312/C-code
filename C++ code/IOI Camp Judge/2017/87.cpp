#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int MAX_N=100000;
int N;
vector<int>ET[MAX_N];
namespace LCA
{
	vector<int>PA[MAX_N];
	int DEP[MAX_N];
	void Dfs(const int u,const int pa,const int dep)
	{
		DEP[u]=dep;
		PA[u].clear();
		if(pa!=-1)
		{
			for(int cur=pa,i=0;;cur=PA[cur][i++])
			{
				PA[u].push_back(cur);
				if(i>=(int)PA[cur].size())break;
			}
		}
		for(const int nxt:ET[u])if(nxt!=pa)Dfs(nxt,u,dep+1);
	}
	void Build()
	{
		Dfs(0,-1,0);
	}
	int Get(int a,int b)
	{
		if(DEP[a]<DEP[b])swap(a,b);
		for(int dis=DEP[a]-DEP[b],i=0;(1<<i)<=dis;i++)if(dis&(1<<i))a=PA[a][i];
		assert(DEP[a]==DEP[b]);
		if(a==b)return a;
		for(int i=30;i>=0;i--)if(i<(int)PA[a].size()&&PA[a][i]!=PA[b][i])a=PA[a][i],b=PA[b][i];
		return PA[a][0];
	}
}
bool Solve(int u,int v,int p,int q)
{
	int a=LCA::Get(u,v),b=LCA::Get(p,q);
	const int c=LCA::Get(a,b);
	if(c!=a&&c!=b)return false;
	else
	{
		if(c==b)swap(a,b),swap(u,p),swap(v,q);
		assert(c==a);
		return LCA::Get(u,b)==b||LCA::Get(v,b)==b;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;
		scanf("%d%d",&N,&querycount);
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		LCA::Build();
		for(int u,v,p,q;querycount--;)
		{
			scanf("%d%d%d%d",&u,&v,&p,&q),--u,--v,--p,--q;
			puts(Solve(u,v,p,q)?"tsan":"hao");
		}
		for(int i=0;i<N;i++)ET[i].clear();
	}
	return 0;
}
