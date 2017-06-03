#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
};
int N,M;
vector<Edge>EDGE;
vector<int>ET[1000],EI[1000];
int OUTLET[1000][1000];
vector<int>BuildOUTLET(const int u,const int parent)
{
	printf("u=%d\n",u);
	int *outlet=OUTLET[u];
	for(int i=0;i<N;i++)outlet[u]=-1;
	vector<int>ans;ans.push_back(u);
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		const vector<int>&chnodes=BuildOUTLET(nxt,u);
		for(const int node:chnodes)outlet[node]=i,ans.push_back(node);
	}
	return ans;
}
vector<int>EDGE_IDXES[1000];
void BuildEDGE_IDXES(const int u,const int parent)
{
	
}
int DP[1000][1<<10];
void BuildDP(const int u,const int parent,const vector<int>&edges)
{
	vector<int>my_edges;
	vector<vector<int> >ch_edges;
	ch_edges.resize(ET[u].size());
	const int *outlet=OUTLET[u];
	
	for(const int ei:edges)
	{
		const Edge &e=EDGE[ei];
		assert(outlet[e.a]!=-1&&outlet[e.b]!=-1);
//		if(outlet[e.a]==outlet[e.b])
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)scanf("%d%d%d",&a,&b,&c),EDGE.push_back(Edge(--a,--b,c));
		sort(EDGE.begin(),EDGE.end(),[](const Edge &a,const Edge &b)->bool{return a.cost>b.cost;});
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			if(e.cost==0)ET[e.a].push_back(e.b),ET[e.b].push_back(e.a);
			else EI[e.a].push_back(i),EI[e.b].push_back(i);
		}
		assert((int)BuildOUTLET(0,-1).size()==N);
		for(int i=0;i<N;i++)EDGE_IDXES[i].clear();
		for(int i=0;i<M-(N-1);i++)EDGE_IDXES[0].push_back(i);
		BuildEDGE_IDXES(0,-1);
	}
	return 0;
}
