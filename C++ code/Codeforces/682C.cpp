#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
struct Edge
{
	int A,B,COST;
	Edge(){}
	Edge(const int _A,const int _B,const int _COST):A(_A),B(_B),COST(_COST){}
};
vector<Edge>EDGE;
int N,A[100000],SZ[100000];
vector<int>ET[100000];
int BuildSZ(const int u,const int parent)
{
	int &sz=SZ[u]=1;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt!=parent)sz+=BuildSZ(nxt,u);
	}
	return sz;
}
int Dfs(const int u,const int parent,const int sum)
{
	if(sum>A[u])
	{
//		printf("pull %lld\n",u+1);
		return SZ[u];
	}
	int ans=0;
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt!=parent)ans+=Dfs(nxt,u,max(0LL,sum+e.COST));
	}
	return ans;
}
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%lld",&A[i]);
		for(int i=1,p,v;i<N;i++)
		{
			scanf("%lld%lld",&p,&v),--p;
			EDGE.push_back(Edge(p,i,v));
			ET[p].push_back(i-1),ET[i].push_back(i-1);
		}
		BuildSZ(0,-1);
		printf("%lld\n",Dfs(0,-1,0));
	}
	return 0;
}
