#include<cstdio>
#include<vector>
#include<queue>
#define debug(x,...) printf(x,##__VA_ARGS__)
using namespace std;
const int MAX_FLR=101;
const int INF=2147483647;
int N,M,K,S,T;
vector<int> ORI_GETO[101],GETO[51*100];//N*K*2
void get_min(int &a,int b){if(b<a)a=b;}
struct Edge
{
	int from,to,limit,flow;
	void init(int fr,int t,int l,int fl)
	{
		from=fr,to=t,limit=l,flow=fl;
	}
}EDGE[500*MAX_FLR];
int DEP[50*MAX_FLR+1],DEP_CNT[50+MAX_FLR+1],VIS[50*MAX_FLR+1];
void build_DEPx(int day,int sp,int ep)
{
	for(int i=0;i<=N+day;i++)DEP_CNT[i]=0;
	for(int d=0;d<=day;d++)
	{
		for(int i=1;i<=N;i++)
		{
			DEP[d*N+i]=N+day;
		}
	}
	queue<int> q;
	q.push(ep);
	DEP[ep]=0;
	VIS[ep]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &ed=EDGE[GETO[u][i]^1],&eu=EDGE[GETO[u][i]];
			if(ed.flow==ed.limit||VIS[ed.from])continue;
			printf(" %d to %d\n",ed.from,ed.to);
			DEP[ed.from]=DEP[ed.to]+1;
			q.push(ed.from);
			VIS[ed.from]=1;
		}
		u-=N;
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &ed=EDGE[GETO[u][i]],&eu=EDGE[GETO[u][i]^1];
			if(ed.flow==ed.limit||VIS[ed.from])continue;
			printf(" %d to %d\n",ed.from,ed.to);
			DEP[ed.from]=DEP[ed.to]+1;
			q.push(ed.from);
			VIS[ed.from]=1;
		}
	}
	for(int d=0;d<=day;d++)
	{
		for(int i=1;i<=N;i++)
		{
			debug("DEP[%d]=%d\n",d*N+i,DEP[d*N+i]);
			DEP_CNT[DEP[d*N+i]]++; 
		}
	}
}
int ANS;
void build_EDGE(int flr,int sp,int ep)
{
	if(flr>1)
	{
		for(int i=0;i<M*2;i++)
		{
			Edge &e=EDGE[(flr-2)*M*2+i],&te=EDGE[(flr-1)*M*2+i];
			te.init(e.from+N,e.to+N,e.limit,0);
			if(te.from==sp&&te.to==ep)te.flow=ANS;
			if(te.to==sp&&te.from==ep)te.flow=-ANS;
			debug("add edge %d : from %d to %d flow %d\n",(flr-1)*M*2+i,te.from,te.to,te.flow);
		}
	}
	for(int p=1;p<=N*2;p++)
	{
		GETO[(flr-1)*N+p].clear();
		for(int j=0;j<ORI_GETO[p].size();j++)
		{
			int en=ORI_GETO[p][j]+(flr-1)*M*2;
			debug("add to(%d,%d) : %d to %d\n",(flr-1)*N+p,en,EDGE[en].from,EDGE[en].to);
			GETO[(flr-1)*N+p].push_back(en);
		}
	}
}
int PRE[50*MAX_FLR+1];
int try_flow(int sp,int ep)
{
	int x=ep,ans=INF;
	while(x!=sp)
	{
		Edge &e=EDGE[PRE[x]];
		get_min(ans,e.limit-e.flow);
		x=e.from;
	}
	x=ep;
	while(x!=sp)
	{
		Edge &e=EDGE[PRE[x]];
		e.flow+=ans;
		EDGE[PRE[x]^1].flow-=ans;
	}
	return ans;
}
int CUR[50*101+1];
int get_MAXFLOW(int day,int sp,int ep)
{
	debug("build_EDGE:\n");
	build_EDGE(day,sp,ep);
	debug("build_DEPx:\n");
	build_DEPx(day,sp,ep);
	for(int d=0;d<=day;d++)
	{
		for(int i=1;i<=N;i++)
		{
			CUR[d*N+i]=0;
		}
	}
	int x=sp,ans=0;
	while(DEP[x]<N+day)
	{
		if(x==ep)
		{
			ans+=try_flow(sp,ep);
			x=sp;
		}
		bool found=false;
		for(int &i=CUR[x];i<GETO[x].size();i++)
		{
			Edge &e=EDGE[GETO[x][i]];
			if(e.flow==e.limit||DEP[e.from]!=DEP[e.to]+1)continue;
			found=true;
			PRE[e.to]=GETO[x][i];
			x=e.to;
			break;
		}
		if(!found)
		{
			if(!--DEP_CNT[DEP[x]])break;
			CUR[x]=0;
			DEP[x]=N;
			for(int i=0;i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				get_min(DEP[x],DEP[e.to]+1);
			}
			if(DEP[x]==N)break;
			DEP_CNT[DEP[x]]++;
			x=EDGE[PRE[x]].from;
		}
	}
	return ans;
}
void termin()
{
	int a[10];
	for(int i=0;;i--)a[i]=100;
}
int main()
{
	freopen("in.txt","r",stdin); 
	while(scanf("%d%d%d%d%d",&N,&M,&K,&S,&T)==5)
	{
		for(int i=1;i<=N*2;i++)
		{
			ORI_GETO[i].clear();
		}
		for(int i=0;i<M*2;)
		{
			int u,v;scanf("%d%d",&u,&v);
			ORI_GETO[u].push_back(i);
			EDGE[i++].init(u,v+N,1,0);
			debug("add edge %d : from %d to %d\n",i-1,u,v+N);
			ORI_GETO[v].push_back(i);
			EDGE[i++].init(v,u+N,1,0);
			debug("add edge %d : from %d to %d\n",i-1,v,u+N);
		}
		M+=N;
		for(int i=M*2,j=1;j<=N;j++)
		{
			ORI_GETO[j].push_back(i);
			EDGE[i++].init(j,j+N,INF,0);
			debug("add edge %d : from %d to %d\n",i-1,j,j+N);
			ORI_GETO[j+N].push_back(i);
			EDGE[i++].init(j+N,j,0,0);
			debug("add edge %d : from %d to %d\n",i-1,j,j+N);
		}
		int now=0;
		ANS=0;
		do
		{
			ANS++;
			debug("DAY %d\n",ANS);
			debug("EDGE[%d]=(%d,%d)\n",0,EDGE[0].from,EDGE[0].to);
			now+=get_MAXFLOW(ANS,S,N*ANS+T);
			debug("now=%d\n",now);
			termin();
		}while(now<K);
		printf("%d\n",ANS);
	}
	return 0;
}
