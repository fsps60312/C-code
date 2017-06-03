#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,E,C;
struct Edge
{
	int v1,v2,fc,flow;
	int to(int from){return from==v1?v2:v1;}
}EDGE[10000];
vector<int> GETO[101];
void get_min(int &a,int b){if(b<a)a=b;}
struct Maxflow
{
	int DEP[101];
	int INQ[101],VIS[101];
	void build_DEP()
	{
		for(int i=1;i<=N;i++)INQ[i]=VIS[i]=0;
		queue<int> q;
		q.push(N);
		INQ[N]=1;
		DEP[N]=0;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			INQ[u]=0;
			VIS[u]=1;
			for(int i=0;i<GETO[u].size();i++)
			{
				Edge &e=EDGE[GETO[u][i]];
				if(VIS[e.to(u)])continue;
				DEP[e.to(u)]=DEP[u]+1;
				if(INQ[e.to(u)])continue;
				INQ[e.to(u)]=1;
				q.push(e.to(u));
			}
		}
	}
	int DEP_CNT[101];
	void build_DEP_CNT()
	{
		for(int i=0;i<=N;i++)DEP_CNT[i]=0;
		for(int i=0;i<N;i++)
		{
			DEP_CNT[DEP[i]]++;
		}
	}
	int PRE[101],POST[101];
	int flow_pathfind()
	{
		int x=N;
		int flow=INF;
		while(x!=1)
		{
			Edge &e=EDGE[PRE[x]];
			get_min(flow,e.fc-e.flow);
			x=e.to(x);
		}
		x=N;
		while(x!=1)
		{
			Edge &e=EDGE[PRE[x]];
			e.flow+=flow;
			x=e.to(x);
		}
		return flow;
	}
	int CUR[101];
	int MAX_FLOW;
	void get_FLOW()
	{
		int &ans=MAX_FLOW=0;
		int x=1;
		for(int i=1;i<=N;i++)CUR[i]=0;
		while(DEP[1]<N)
		{
			if(x==N)
			{
				ans+=flow_pathfind();
				x=1;
			}
			bool findway=false;
			for(int &i=CUR[x];i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				if(DEP[x]==DEP[e.to(x)]+1&&e.fc-e.flow)
				{
					POST[x]=PRE[e.to(x)]=GETO[x][i];
					findway=true;
					x=e.to(x);
					break;
				}
			}
			if(!findway)
			{
				if(!--DEP_CNT[DEP[x]])break;
				DEP[x]=N;
				CUR[x]=0;
				for(int i=0;i<GETO[x].size();i++)
				{
					Edge &e=EDGE[GETO[x][i]];
					if(!e.fc-e.flow)continue;
					get_min(DEP[x],DEP[e.to(x)]+1);
				}
				DEP_CNT[DEP[x]]++;
				if(x!=1)x=EDGE[PRE[x]].to(x);
			}
		}
	}
	bool check_canupdate(int fc)
	{
		int addv=fc-MAX_FLOW;
		for(int i=0;i<E;i++)
		{
			Edge &e=EDGE[i];
			if(e.fc==e.flow)
			{
				int x,y;
				if(PRE[])
			}
		}
	}
}MAXFLOW;
int main()
{
	freopen("in.txt","r",stdin); 
	while(scanf("%d%d%d",&N,&E,&C)==3&&(N||E||C))
	{
		for(int i=1;i<=N;i++)
		{
			GETO[i].clear();
		}
		for(int i=0;i<E;i++)
		{
			Edge &e=EDGE[i];
			scanf("%d%d%d",&e.v1,&e.v2,&e.fc);
			e.flow=0;
			GETO[e.v1].push_back(i);
			GETO[e.v2].push_back(i);
		}
		printf("a\n");
		MAXFLOW.build_DEP();
		printf("b\n");
		MAXFLOW.build_DEP_CNT();
		printf("c\n");
		int ans=MAXFLOW.get_FLOW();
		printf("maxflow=%d\n",ans);
	}
	return 0;
}
