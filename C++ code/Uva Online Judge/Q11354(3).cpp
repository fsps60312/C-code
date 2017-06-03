#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int N,M;
struct Road
{
	int x,y,d;
};
Road ROAD[1000000];
struct City
{
	int fa[170];
	int d[170];
	int DJSET,dep;
	void init(int _idx)
	{
		DJSET=_idx;
		for(int i=0;i<170;i++)
		{
			fa[i]=-1;
			d[i]=-1;
		}
	}
};
int VIS[500001];
void termin()
{
	for(int i=0;;i--)VIS[i]=0;
}
City CITY[500001];
bool cmp_Road(Road a,Road b)
{
	return a.d<b.d;
}
bool isleader(int a){return CITY[a].DJSET==a;}
vector<int> V;
int findset(int a)
{
	V.clear();
	V.push_back(a);
	while(!isleader(V[V.size()-1]))
	{
		V.push_back(CITY[V[V.size()-1]].DJSET);
	}
	while(V.size()>=2)
	{
		CITY[V[V.size()-2]].DJSET=CITY[V[V.size()-1]].DJSET;
		V.pop_back();
	}
	return CITY[V[0]].DJSET;
}
struct Tree
{
	int to,d;
};
vector<Tree> MST[500001];
struct Bfs{int u,fa,d,dep;};
queue<Bfs> BQ;
void buildMST()
{
	sort(ROAD,ROAD+M,cmp_Road);
	int cnet=0,root=-1;
	for(int i=0;cnet!=N-1;i++)
	{
		if(i==M)break;//termin();//not here
		int findx=findset(ROAD[i].x),findy=findset(ROAD[i].y);
		if(findx==findy)continue;
		CITY[findx].DJSET=findy;
		MST[ROAD[i].x].push_back((Tree){ROAD[i].y,ROAD[i].d});
		MST[ROAD[i].y].push_back((Tree){ROAD[i].x,ROAD[i].d});
		root=ROAD[i].x;
		cnet++;
	}
	BQ.push((Bfs){root,-1,-1,0});
	while(!BQ.empty())
	{
		Bfs b=BQ.front();BQ.pop();
		if(VIS[b.u])continue;
		if(b.u<1||b.u>N)return;//termin();
		VIS[b.u]=1;
		CITY[b.u].fa[0]=b.fa;
		CITY[b.u].d[0]=b.d;
		CITY[b.u].dep=b.dep;
		for(int i=0;i<MST[b.u].size();i++)
		{
			BQ.push((Bfs){MST[b.u][i].to,b.u,MST[b.u][i].d,b.dep+1});
		}
	}
	for(int dis=1;dis<17;dis++)
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
		if(i==170)return ans;//termin();
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
		if(x==-1||y==-1)return ans;//termin();
		int i;
		for(i=0;CITY[x].fa[i+1]!=CITY[y].fa[i+1];i++)if(i+1+1==170)return ans;//termin();
		ans=max(ans,max(CITY[x].d[i],CITY[y].d[i]));
		x=CITY[x].fa[i],y=CITY[y].fa[i];
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d%d",&N,&M)==2)
	{
		if(kase++)printf("\n");
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
		//printf("\n");
	}
	return 0;
}
