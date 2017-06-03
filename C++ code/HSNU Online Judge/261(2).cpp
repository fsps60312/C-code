#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M,P;
struct Edge
{
	int from,to;
	Edge(){}
	Edge(const int _a,const int _b):from(_a),to(_b){}
	bool operator<(const Edge &e)const{return from!=e.from?from<e.from:to<e.to;}
};
map<Edge,int>IDX;
vector<Edge>EDGE;
vector<int>ET[150000];
int NXT[300000],DIST[300000],TYPE[300000];
bool VIS[300000];
int GetIdx(const int a,const int b)
{
	auto it=IDX.find(Edge(a,b));
	assert(it!=IDX.end());
	return it->second;
}
void Dfs(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	if(EDGE[u].to==P){DIST[u]=1,TYPE[u]=(ET[P][0]==EDGE[u].from?0:1);return;}
	Dfs(NXT[u]);
	if(DIST[NXT[u]]==INF)return;
	DIST[u]=DIST[NXT[u]]+1;
	TYPE[u]=TYPE[NXT[u]];
}
int A[150000],B[150000],C[150000][2];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&P)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		IDX.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			ET[a].push_back(b),ET[b].push_back(a);
			assert(IDX.find(Edge(a,b))==IDX.end());
			IDX[Edge(a,b)]=IDX[Edge(b,a)]=-1;
		}
		EDGE.clear();
		int cnt=0;
		for(auto it=IDX.begin();it!=IDX.end();it++)it->second=cnt++,EDGE.push_back(it->first);
		assert(IDX.size()==M*2);
		for(int i=0;i<M*2;i++)VIS[i]=false,DIST[i]=INF,TYPE[i]=-1;
		for(auto it:IDX)
		{
			const Edge &e=it.first;
			NXT[it.second]=(ET[e.to][0]==e.from&&ET[e.to].size()>=2)?GetIdx(e.to,ET[e.to][1]):GetIdx(e.to,ET[e.to][0]);
		}
		for(int i=0;i<M*2;i++)if(!VIS[i])Dfs(i);
		for(int i=0;i<N;i++)
		{
			const int e=GetIdx(i,ET[i][0]);
			A[i]=DIST[e];
			if(A[i]==INF)continue;
			if(ET[P].size()==1)B[i]=DIST[GetIdx(P,ET[P][0])];
			else
			{
				const int i0=GetIdx(P,ET[P][0]),i1=GetIdx(P,ET[P][1]);
				if(TYPE[e]==0)
				{
					if(TYPE[i1]==0)B[i]=DIST[i1],C[i][0]=C[i][1]=0;
					else if(DIST[i0]==INF||DIST[i1]==INF)B[i]=INF,C[i][0]=C[i][1]=0;
					else B[i]=DIST[i1]+DIST[i0],C[i][0]=0,C[i][1]=DIST[i1];
				}
				else
				{
					if(TYPE[i0]==1)B[i]=DIST[i0],C[i][0]=C[i][1]=0;
					else if(DIST[i0]==INF||DIST[i1]==INF)B[i]=INF,C[i][0]=C[i][1]=0;
					else B[i]=DIST[i0]+DIST[i1],C[i][0]=0,C[i][1]=DIST[i0];
				}
			}
		}
		static int q;scanf("%d",&q);
		while(q--)
		{
			static int g;scanf("%d",&g);
			int ans=0;
			for(int i=0;i<N;i++)if(A[i]!=INF)
			{
				if(g>=A[i]&&((g-A[i])%B[i]==C[i][0]||(g-A[i])%B[i]==C[i][1]))ans++;
			}
			printf("%d\n",ans);
		}
		break;
	}
	return 0;
}
