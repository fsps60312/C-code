#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge
{
	int x,y,cost,used;
};
Edge EDGE[200];
int MAXCOST[101][101],T,N,M;
int DJSET[101];
int findset(int a)
{
	if(DJSET[a]==a)return a;
	return DJSET[a]=findset(DJSET[a]);
}
vector<int> TO[101];
bool cmp_EDGE(Edge a,Edge b)
{
	return a.cost<b.cost;
}
void getmin(int &a,int b){if(b<a)a=b;}
int get_differ()
{
	int ans=2147483647;
	for(int i=0;i<M;i++)
	{
		Edge &e=EDGE[i];
		if(e.used)continue;
		getmin(ans,e.cost-MAXCOST[e.x][e.y]);
	}
	return ans;
}
void dfs_MAXCOST(int &o,int u,int fa,int cost)
{
	MAXCOST[o][u]=cost;
	for(int i=0;i<TO[u].size();i++)
	{
		int &en=TO[u][i];
		Edge &e=EDGE[en];
		int nxu=(e.x==u?e.y:e.x);
		if(nxu==fa)continue;
		dfs_MAXCOST(o,nxu,u,max(cost,e.cost));
	}
}
void get_MAXCOST()
{
	for(int i=1;i<=N;i++)
	{
		dfs_MAXCOST(i,i,i,0);
	}
}
int solve()
{
	if(N==1)return -1;
	for(int i=1;i<=N;i++)
	{
		DJSET[i]=i;
		TO[i].clear();
	}
	sort(EDGE,EDGE+M,cmp_EDGE);
	int gpn=N,mstsz=0;
	for(int i=0;i<M;i++)
	{
		Edge &e=EDGE[i];
		int a=findset(e.x),b=findset(e.y);
		if(a!=b)
		{
			e.used=1;
			mstsz+=e.cost;
			DJSET[a]=b;
			TO[e.x].push_back(i);
			TO[e.y].push_back(i);
			if(--gpn==1)break;
		}
	}
	if(gpn>1)return -2;
	get_MAXCOST();
	int differ=get_differ();
	if(differ==2147483647)return -1;
	return mstsz+differ;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<M;i++)
		{
			Edge &e=EDGE[i];
			scanf("%d%d%d",&e.x,&e.y,&e.cost);
			e.used=0;
		}
		int ans=solve();
		printf("Case #%d : ",kase++);
		if(ans==-2)printf("No way");
		else if(ans==-1)printf("No second way");
		else printf("%d",ans);
		printf("\n");
	}
	return 0;
}
