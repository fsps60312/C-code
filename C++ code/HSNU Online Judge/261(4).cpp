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
vector<int>TRASH[2];
int A[2][300000];//a+bn
int B[2];
void BuildAns(const int source)
{
	const int dist=DIST[ET[source][0]],type=TYPE[ET[source][0]];
	if(dist==INF)return;
	A[type][dist]++;
	assert(type==0||type==1);
	const int pdist0=DIST[ET[P][type]],ptype0=TYPE[ET[P][type]];
	if(pdist0==INF)return;
	if(ptype0==type){B[type]=pdist0;return;}
	A[type][dist]--,TRASH[type].push_back(dist),A[type][dist+pdist0]++;
	const int pdist1=DIST[ET[P][type^1]],ptype1=TYPE[ET[P][type^1]];
	if(pdist1==INF)return;
	if(ptype1==(type^1)){B[type]=pdist1;return;}
	A[type][dist]++;TRASH[type].pop_back();
	B[type]=pdist0+pdist1;
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
		static int q;scanf("%d",&q);
		for(int i=0;i<M*2;i++)A[0][i]=A[1][i]=0;
		B[0]=B[1]=INF;
		TRASH[0].clear(),TRASH[1].clear();
		for(int i=0;i<N;i++)BuildAns(i);
//		printf("B(%d,%d)\n",B[0],B[1]);
		for(int i=0;i<M*2;i++)
		{
			if(i-B[0]>=0)A[0][i]+=A[0][i-B[0]];
			if(i-B[1]>=0)A[1][i]+=A[1][i-B[1]];
		}
//		for(int i=0;i<M*2;i++)printf("(%d,%d)\n",A[0][i],A[1][i]);
		for(const auto v:TRASH[0])A[0][v]++;
		for(const auto v:TRASH[1])A[1][v]++;
		while(q--)
		{
			static int g;scanf("%d",&g);
			assert(g>0);
			int ans=0,v;
			for(int i=0;i<2;i++)
			{
				v=g;
				if(B[i]==INF){ans+=(v<M*2?A[i][v]:0);continue;}
//				printf("av=%d,M*2=%d\n",v,M*2);
				if(v>=M*2)v-=((v-M*2)/B[i]+1)*B[i],assert(v<M*2&&v+B[i]>=M*2);
//				printf("bv=%d,M*2=%d\n",v,M*2);
				ans+=A[i][v];
			}
			printf("%d\n",ans);
		}
		break;
	}
	return 0;
}
