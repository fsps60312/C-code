#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,E,C;
int abs(int a){return a>=0?a:-a;}
struct Edge
{
	int v1,v2,fc,flow[2];
	int to(int from){return from==v1?v2:v1;}
	int get_flow(int t,int from)
	{
		if(from==v1)return flow[t];
		else return -flow[t];
	}
	void add_flow(int t,int from,int v)
	{
		if(from==v1)flow[t]+=v;
		else flow[t]-=v;
	}
}EDGE[10000];
vector<int> GETO[101];
void get_min(int &a,int b){if(b<a)a=b;}
struct Maxflow
{
	int DEP[101];
	int INQ[101],VIS[101];
	void build_DEP(int t)
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
				if(VIS[e.to(u)]||-e.get_flow(t,u)==e.fc)continue;
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
		for(int i=1;i<=N;i++)
		{
			DEP_CNT[DEP[i]]++;
		}
	}
	int PRE[101];
	int flow_pathfind(int t)
	{
		int x=N;
		int flow=INF;
		while(x!=1)
		{
			Edge &e=EDGE[PRE[x]];
			get_min(flow,e.fc+e.get_flow(t,x));
			x=e.to(x);
		}
		x=N;
		while(x!=1)
		{
			Edge &e=EDGE[PRE[x]];
			e.add_flow(t,x,-flow);
			x=e.to(x);
		}
		return flow;
	}
	int CUR[101];
	int MAX_FLOW;
	int get_FLOW(int t,int addv)
	{
		int &ans=MAX_FLOW=0;
		int x=1;
		for(int i=1;i<=N;i++)CUR[i]=0;
		while(1)
		{
			if(x==N)
			{
				ans+=flow_pathfind(t);
				if(ans>=addv)break;
				x=1;
			}
			bool findway=false;
			for(int &i=CUR[x];i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				if(DEP[x]==DEP[e.to(x)]+1&&e.get_flow(t,x)<e.fc)
				{
					PRE[e.to(x)]=GETO[x][i];
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
					if(e.get_flow(t,x)==e.fc)continue;
					get_min(DEP[x],DEP[e.to(x)]+1);
				}
				DEP_CNT[DEP[x]]++;
				if(x!=1)x=EDGE[PRE[x]].to(x);
			}
		}
		return ans;
	}
	void check_canupdate()
	{
		int addv=C-MAX_FLOW;
		bool found=false;
		for(int i=0;i<E;i++)
		{
			Edge &e=EDGE[i];
			if(e.fc==e.flow[0])
			{
				for(int j=0;j<E;j++)
				{
					EDGE[j].flow[1]=EDGE[j].flow[0];
				}
				e.flow[1]=-5000;
				build_DEP(1);
				build_DEP_CNT();
				if(get_FLOW(1,addv)>=addv)
				{
					if(!found)printf("possible option:");
					else printf(",");
					printf("(%d,%d)",e.v1,e.v2);
					found=true;
				}
			}
		}
		if(!found)printf("not possible");
		puts("");
	}
}MAXFLOW;
bool cmp_EDGE(Edge a,Edge b)
{
	if(a.v1!=b.v1)return a.v1<b.v1;
	return a.v2<b.v2;
}
template<class T_TYPE>
void myswap(T_TYPE &a,T_TYPE &b)
{
	T_TYPE c=a;
	a=b;
	b=c;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
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
			if(e.v1>e.v2)myswap(e.v1,e.v2);
			e.flow[0]=0;
		}
		sort(EDGE,EDGE+E,cmp_EDGE);
		for(int i=0;i<E;i++)
		{
			Edge &e=EDGE[i];
			GETO[e.v1].push_back(i);
			GETO[e.v2].push_back(i);
		}
		//printf("a\n");
		MAXFLOW.build_DEP(0);
		//printf("b\n");
		MAXFLOW.build_DEP_CNT();
		//printf("c\n");
		//printf("maxflow=%d\n",ans);
		printf("Case %d: ",kase++);
		if(MAXFLOW.get_FLOW(0,C)>=C)
		{
			printf("possible\n");
		}
		else
		{
			MAXFLOW.check_canupdate();
		}
		//printf("can update to %d\n",ans2);
	}
	return 0;
}
