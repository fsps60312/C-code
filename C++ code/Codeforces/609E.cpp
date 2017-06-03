#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct DisjointSets
{
	int S[200000];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){return ((a=Find(a))==(b=Find(b))?false:(S[a]=b,true));}
}DJ;
struct Edge
{
	int ID,A,B,W;
	bool USED;
	Edge(){}
	Edge(const int _ID,const int _A,const int _B,const int _W):ID(_ID),A(_A),B(_B),W(_W),USED(false){}
};
bool operator<(const Edge &a,const Edge &b){return a.W<b.W;}
vector<int>ET[200000],PARENT[200000],MX[200000];
vector<Edge>EDGE;
int DEPTH[200000];
void Dfs(const int u,const int depth,const int parent,const int pre_w)
{
//	printf("u=%d\n",u+1);
	DEPTH[u]=depth;
	PARENT[u].clear(),MX[u].clear();
	if(parent!=-1)
	{
		for(int cur=parent,mx=pre_w,i=0;;mx=max(mx,MX[cur][i]),cur=PARENT[cur][i],++i)
		{
//			printf("cur=%d\n",cur+1);
			PARENT[u].push_back(cur),MX[u].push_back(mx);
			if(i>=(int)PARENT[cur].size())break;
		}
	}
	for(const int ei:ET[u])if(EDGE[ei].USED)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt!=parent)Dfs(nxt,depth+1,u,e.W);
	}
}
const int INF=2147483647;
int QueryLcaMax(int a,int b)
{
	if(DEPTH[a]>DEPTH[b])swap(a,b);
	int ans=-INF;
	for(int d=0,dis=DEPTH[b]-DEPTH[a];(1<<d)<=dis;d++)if(dis&(1<<d))ans=max(ans,MX[b][d]),b=PARENT[b][d];
	if(a==b)return ans;
	for(int d=30;d>=0;d--)if(d<(int)PARENT[a].size()&&PARENT[a][d]!=PARENT[b][d])ans=max(ans,max(MX[a][d],MX[b][d])),a=PARENT[a][d],b=PARENT[b][d];
	assert(PARENT[a][0]==PARENT[b][0]);
	return max(ans,max(MX[a][0],MX[b][0]));
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,w;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&w),--a,--b;
			EDGE.push_back(Edge(i,a,b,w));
		}
		sort(EDGE.begin(),EDGE.end());
		DJ.Clear(N);
		long long cost=0;
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			ET[e.A].push_back(i),ET[e.B].push_back(i);
			if(DJ.Merge(e.A,e.B))EDGE[i].USED=true,cost+=e.W;
		}
		Dfs(0,0,-1,0);
		static long long ans[200000];
		for(const Edge &e:EDGE)
		{
			if(e.USED)ans[e.ID]=cost;
			else ans[e.ID]=cost+e.W-QueryLcaMax(e.A,e.B);
		}
		for(int i=0;i<M;i++)printf("%lld\n",ans[i]);
	}
	return 0;
}
