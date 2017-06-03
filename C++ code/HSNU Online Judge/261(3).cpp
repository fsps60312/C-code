#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M,P;
struct Edge
{
	int from,to;
	Edge(){}
	Edge(const int _f,const int _t):from(_f),to(_t){}
};
vector<Edge>EDGE;
vector<int>ET[150000];
int NXT[300000],DIST[300000],TYPE[300000];
bool VIS[300000];
void Dfs(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	if(EDGE[u].to==P)
	{
		const Edge &e=EDGE[u];
		DIST[u]=1;
		TYPE[u]=(NXT[u]==ET[P][0]?0:1);
		return;
	}
	assert(EDGE[u].to==EDGE[NXT[u]].from);
	Dfs(NXT[u]);
	if(DIST[NXT[u]]==INF)return;
	DIST[u]=DIST[NXT[u]]+1;
	TYPE[u]=TYPE[NXT[u]];
}
bool Solve(const int source,int g)
{
	const int dist=DIST[ET[source][0]],type=TYPE[ET[source][0]];
	if(dist==INF)return false;
	assert(type==0||type==1);
	g-=dist;
	if(g<0)return false;
	if(g==0)return true;
	const int pdist0=DIST[ET[P][type]],ptype0=TYPE[ET[P][type]];
	if(pdist0==INF)return false;
	if(ptype0==type)return g%pdist0==0;
	g-=pdist0;
	assert(g!=0);
	const int pdist1=DIST[ET[P][type^1]],ptype1=TYPE[ET[P][type^1]];
	if(pdist1==INF)return false;
	if(ptype1==(type^1))return g%pdist1==0;
	g%=pdist0+pdist1;
	return g==0||g==pdist1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&P)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			assert(a>=0&&a<N&&b>=0&&b<N);
			EDGE.push_back(Edge(a,b)),EDGE.push_back(Edge(b,a));
			ET[a].push_back(i*2),ET[b].push_back(i*2+1);
		}
		for(int i=0;i<M*2;i++)
		{
			const Edge &e=EDGE[i];
			NXT[i]=(ET[e.to][0]==(i^1)&&ET[e.to].size()>=2?ET[e.to][1]:ET[e.to][0]);
		}
		for(int i=0;i<M*2;i++)DIST[i]=INF,TYPE[i]=-1,VIS[i]=false;
		for(int i=0;i<M*2;i++)if(!VIS[i])Dfs(i);
//		for(int i=0;i<M*2;i++)
//		{
//			const Edge &a=EDGE[i],&b=EDGE[NXT[i]];
//			printf("DIST=%d,TYPE=%d(%d,%d)->(%d,%d)\n",DIST[i],TYPE[i],a.from,a.to,b.from,b.to);
//		}
		static int q;scanf("%d",&q);
		while(q--)
		{
			static int g;scanf("%d",&g);
			assert(g>0);
			int ans=0;
			for(int i=0;i<N;i++)if(Solve(i,g))ans++;
			printf("%d\n",ans);
		}
		break;
	}
	return 0;
}
