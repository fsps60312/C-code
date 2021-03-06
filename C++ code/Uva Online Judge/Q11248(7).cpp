#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
vector<int> GETO[101];
int N,E,C;
struct Edge
{
	int from,to,fp,idx,flow[2];
	void init(int f,int t,int _fp,int i)
	{
		from=f,to=t,fp=_fp,idx=i;
		flow[0]=flow[1]=0;
	}
}EDGE[20000];
int DEP[101],DEP_CNT[101];
int vis[101];
void get_min(int &a,int b){if(b<a)a=b;}
void build_DEPx(int t)
{
	for(int i=0;i<=N;i++)
	{
		DEP[i]=N;
		vis[i]=0;
		DEP_CNT[i]=0;
	}
	queue<int> q;
	DEP[N]=0;
	q.push(N);
	vis[N]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &e=EDGE[GETO[u][i]^1];
			if(e.fp==e.flow[t]||vis[e.from])continue;
			vis[e.from]=1;
			DEP[e.from]=DEP[e.to]+1;
			q.push(e.from);
		}
	}
	for(int i=1;i<=N;i++)DEP_CNT[DEP[i]]++;
}
int PRE[101];
int set_max_flow(int t)
{
	int x=N,flow=INF;
	while(x!=1)
	{
		Edge &e=EDGE[PRE[x]];
		get_min(flow,e.fp-e.flow[t]);
		x=e.from;
	}
	x=N;
	while(x!=1)
	{
		Edge &e=EDGE[PRE[x]];
		e.flow[t]+=flow;
		EDGE[PRE[x]^1].flow[t]-=flow;
		x=e.from;
	}
	return flow;
}
int CUR[101];
int get_max_flow(int t,int goal)
{
	for(int i=1;i<=N;i++)
	{
		CUR[i]=0;
	}
	int x=1,ans=0;
	while(DEP[1]<N)
	{
		if(x==N)
		{
			ans+=set_max_flow(t);
			if(ans>=goal)break;
			x=1;
		}
		bool found=false;
		for(int i=CUR[x];i<GETO[x].size();i++)
		{
			Edge &e=EDGE[GETO[x][i]];
			if(e.fp==e.flow[t]||DEP[e.from]!=DEP[e.to]+1)continue;
			CUR[x]=i;
			found=true;
			PRE[e.to]=GETO[x][i];
			x=e.to;
			break;
		}
		if(!found)
		{
			if(!--DEP_CNT[DEP[x]])break;
			DEP[x]=N;
			CUR[x]=0;
			for(int i=0;i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				if(e.fp==e.flow[t])continue;
				get_min(DEP[x],DEP[e.to]+1);
			}
			if(DEP[x]==N)break;
			DEP_CNT[DEP[x]]++;
			if(x!=1)x=EDGE[PRE[x]].from;
		}
	}
	return ans;
}
int MAX_FLOW;
void try_improve()
{
	//printf("try_improve\n");
	int goal=C-MAX_FLOW;
	bool found=false;printf(" E=%d ",E);
	for(int i=0;i<E*2;i+=2)
	{
		Edge &e=EDGE[i];
		//if(e.fp==0)printf("error\n");
		if(e.fp!=e.flow[0])continue;
		//printf("from %d to %d\n",e.from,e.to);
		for(int j=0;j<E*2;j++)
		{
			EDGE[j].flow[1]=EDGE[j].flow[0];
		}
		e.fp+=2000000000;
		build_DEPx(1);
		if(get_max_flow(1,goal)>=goal)
		{
			if(!found)printf("possible option:");
			else printf(",");
			printf("(%d,%d)",e.from,e.to);
			found=true;
		}
		e.fp-=2000000000;
	}
	if(!found)printf("not possible\n");
	else puts("");
}
bool cmp_EDGE(Edge _a,Edge _b)
{
	if((_a.idx|1)==(_b.idx|1))return _a.idx<_b.idx;
	Edge &a=EDGE[(_a.idx|1)-1],&b=EDGE[(_b.idx|1)-1];
	if(a.from!=b.from)return a.from<b.from;
	if(a.to!=b.to)return a.to<b.to;
	return a.idx<b.idx;
}
Edge msort_EDGE[20000];
void msort(int l,int r)
{
	if(l>=r)return;
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	int a=l,b=mid+1;
	for(int i=l;i<=r;i++)
	{
		if(b>r||(a<=mid&&cmp_EDGE(EDGE[a],EDGE[b])))msort_EDGE[i]=EDGE[a++];
		else msort_EDGE[i]=EDGE[b++];
	}
	for(int i=l;i<=r;i++)EDGE[i]=msort_EDGE[i];
}
int main()
{
	freopen("in.txt","r",stdin); 
	int kase=1;
	while(scanf("%d%d%d",&N,&E,&C)==3&&(N||E||C))
	{
		//printf("E=%d\n",E);
//		for(int i=1;i<=N;i++)GETO[i].clear();
		for(int i=0;i<E*2;)
		{
			int a,b,fp;scanf("%d%d%d",&a,&b,&fp);
			if(i>=20000||a<=0||a>N||b<=0||b>N){printf("error\n");return 0;}
			if(a==b)
			{
				E--;
				continue;
			}
//			GETO[a].push_back(i);
			EDGE[i].init(a,b,fp,i);i++;
//			GETO[b].push_back(i);
			EDGE[i].init(b,a,0,i);i++;
		}
		if(N>1)
		{
			//printf("E=%d\n",E);
			if(E)msort(0,E*2-1);
			for(int i=1;i<=N;i++)GETO[i].clear();
			for(int i=0;i<E*2;i++)
			{
				Edge &e=EDGE[i];
				GETO[e.from].push_back(i);
			}
			build_DEPx(0);
		}
		printf("Case %d: ",kase++);
		if(N==1||(MAX_FLOW=get_max_flow(0,C))>=C)printf("possible\n");
		else try_improve();
	}
	return 0;
}
