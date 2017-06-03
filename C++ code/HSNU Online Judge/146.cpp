#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100000],FA[100000],COST[100000];
int N,Q,DEP[100000];
int Nxt(const int u,const int ei){const Edge &e=EDGE[ei];return e.a==u?e.b:e.a;}
void Dfs(const int u,const int fa,const int dep)
{
	FA[u].clear(),COST[u].clear(),DEP[u]=dep;
	if(fa!=-1)
	{
		for(int cur=Nxt(u,fa),cost=EDGE[fa].cost,i=0;;cost+=COST[cur][i],cur=FA[cur][i],i++)
		{
			FA[u].push_back(cur);
			COST[u].push_back(cost);
			if(i>=(int)FA[cur].size())break;
		}
	}
	for(const int ei:ET[u])if(ei!=fa)
	{
		const int nxt=Nxt(u,ei);
		Dfs(nxt,ei,dep+1);
	}
}
int Query(int a,int b)
{
	if(DEP[a]<DEP[b])swap(a,b);
	int ans=0;
	for(int dis=DEP[a]-DEP[b],i=30;i>=0;i--)if(dis&(1<<i))ans+=COST[a][i],a=FA[a][i];
	assert(DEP[a]==DEP[b]);
	if(a==b)return ans;
	for(int i=30;i>=0;i--)if(DEP[a]-(1<<i)>=0&&FA[a][i]!=FA[b][i])ans+=COST[a][i]+COST[b][i],a=FA[a][i],b=FA[b][i];
	assert(FA[a][0]==FA[b][0]);
	return ans+=COST[a][0]+COST[b][0];
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&Q);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0;i<N-1;i++)
	{
		static int a,b,c;scanf("%d%d%d",&a,&b,&c),a--,b--;
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	Dfs(0,-1,0);
	while(Q--)
	{
		static int x,y;scanf("%d%d",&x,&y),x--,y--;
		printf("%d\n",Query(x,y));
	}
	return 0;
}
