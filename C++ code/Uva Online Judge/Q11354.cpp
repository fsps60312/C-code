#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
int N,M;
struct Road
{
	int x,y,d;
};
Road ROAD[100000];
struct City
{
	int fa[17];
	int d[17];
	int DJSET,dep;
	void init(int _idx)
	{
		DJSET=_idx;
		for(int i=0;i<=16;i++)
		{
			fa[i]=-1;
			d[i]=-1;
		}
	}
};
City CITY[50001];
bool cmp_Road(Road a,Road b)
{
	return a.d<b.d;
}
int findset(int a)
{
	if(CITY[a].DJSET==a)return a;
	return CITY[a].DJSET=findset(CITY[a].DJSET);
}
struct Tree
{
	int to,d;
};
vector<Tree> MST[50001];
int VIS[50001];
void dfs_MST(int u,int fa,int d,int dep)
{
	if(VIS[u]||u<=0||u>N)return;
	VIS[u]=1;
	CITY[u].fa[0]=fa;
	CITY[u].d[0]=d;
	CITY[u].dep=dep;
	for(int i=0;i<MST[u].size();i++)
	{
		dfs_MST(MST[u][i].to,u,MST[u][i].d,dep+1);
	}
}
void buildMST()
{
	sort(ROAD,ROAD+M,cmp_Road);
	int cnet=0,root=-1;
	for(int i=0;cnet!=N-1;i++)
	{
		if(i==M)return;//not here
		int findx=findset(ROAD[i].x),findy=findset(ROAD[i].y);
		if(findx==findy)continue;
		CITY[findx].DJSET=findy;
		MST[ROAD[i].x].push_back((Tree){ROAD[i].y,ROAD[i].d});
		MST[ROAD[i].y].push_back((Tree){ROAD[i].x,ROAD[i].d});
		root=ROAD[i].x;
		cnet++;
	}
	dfs_MST(root,-1,-1,0);
	for(int dis=1;dis<=16;dis++)
	{
		for(int i=1;i<=N;i++)
		{
			int fa=CITY[i].fa[dis-1];
			if(fa==-1)continue;
			CITY[i].fa[dis]=CITY[fa].fa[dis-1];
			CITY[i].d[dis]=max(CITY[i].d[dis-1],CITY[fa].d[dis-1]);
		}
	}
	//for(int i=1;i<=N;i++)printf("[%d]:dep=%d fa=%d\n",i,CITY[i].dep,CITY[i].fa[0]);
	//for(int i=0;i<4;i++)printf(" %d",CITY[4].fa[i]);printf("\n");
}
int getmaxcost(int x,int y)
{
	if(CITY[x].dep<CITY[y].dep)x^=y^=x^=y;
	//printf("%d %d\n",CITY[y].dep,CITY[x].dep);
	int gap=CITY[x].dep-CITY[y].dep;
	int ans=0;
	for(int i=0;gap;i++)
	{
		if(i==17)return ans;
		if(gap&(1<<i))
		{
			ans=max(ans,CITY[x].d[i]);
			x=CITY[x].fa[i];
			gap-=(1<<i);
		}
	}
	//printf("gap=%d x=%d y=%d\n",gap,x,y);
	while(x!=y)
	{
		//printf("%d:d%d %d:d%d\n",x,CITY[x].dep,y,CITY[y].dep);
		if(x==-1||y==-1)break;
		int i;
		for(i=0;CITY[x].fa[i+1]!=CITY[y].fa[i+1];i++)if(i==16)return ans;
		ans=max(ans,max(CITY[x].d[i],CITY[y].d[i]));
		x=CITY[x].fa[i],y=CITY[y].fa[i];
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)
		{
			CITY[i].init(i);
			MST[i].clear();
			VIS[i]=0;
		}
		for(int i=0;i<M;i++)
		{
			scanf("%d%d%d",&ROAD[i].x,&ROAD[i].y,&ROAD[i].d);
		}
		buildMST();
		int q;scanf("%d",&q);
		while(q--)
		{
			int from,to;scanf("%d%d",&from,&to);
			printf("%d\n",getmaxcost(from,to));
		}
		printf("\n");
	}
	return 0;
}
