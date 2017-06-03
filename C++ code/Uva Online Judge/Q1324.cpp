#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M,K,S,T;
vector<int> GETO[51];
struct Edge
{
	int from,to,flow;
	void init(int fr,int t,int fl)
	{
		from=fr,to=t,flow=fl;
	}
}EDGE[400];
int DEP[51],DEP_CNT[51],VIS[51];
void build_DEPx()
{
	for(int i=0;i<=N;i++)
	{
		DEP_CNT[i]=0;
		DEP[i]=N;
	}
	queue<int> q;
	q.push(T);
	DEP[T]=0;
	VIS[T]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &e=EDGE[GETO[u][i]^1];
			if(VIS[e.from])continue;
			DEP[e.from]=DEP[e.to]+1;
			q.push(e.from);
			VIS[e.from]=1;
		}
	}
	for(int i=1;i<=N;i++)DEP_CNT[DEP[i]]++;
}
int main()
{
	while(scanf("%d%d%d%d%d",&N,&M,&K,&S,&T)==5)
	{
		for(int i=1;i<=N;i++)
		{
			GETO[i].clear();
		}
		for(int i=0;i<M*2;)
		{
			int u,v;scanf("%d%d",&u,&v);
			GETO[u].push_back(i);
			EDGE[i++].init(u,v,0);
			GETO[v].push_back(i);
			EDGE[i++].init(v,u,0);
		}
		build_DEPx();
	}
	return 0;
}
