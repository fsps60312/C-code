#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
const int INF=2147483647/2;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
int CntBits(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
};
int N,M;
vector<Edge>EDGE;
vector<int>ET[1000];
bool GetNxt(const int u,const int i,int &ans)
{
	assert(i!=-1);
	const Edge &e=EDGE[ET[u][i]];
	if(e.cost!=0)return false;
	ans=(e.a==u?e.b:e.a);
	return true;
}
int OUTLET[1000][1000],COLOR[1000];
vector<int>BuildOUTLET(const int u,const int parent,const int color)
{
	COLOR[u]=color;
	int *outlet=OUTLET[u];
	for(int i=0;i<N;i++)outlet[i]=-1;
	vector<int>ans;ans.push_back(u);
	for(int i=0,nxt;i<(int)ET[u].size();i++)if(GetNxt(u,i,nxt)&&nxt!=parent)
	{
		const vector<int>&ch_nodes=BuildOUTLET(nxt,u,color^1);
		for(const int node:ch_nodes)outlet[node]=i,ans.push_back(node);
	}
	return ans;
}
int DP[1000][1<<10],EDGE_LOC[1000][5000];
int GetPathCost(const int pre_ei,const int u,const int to,const int ei)
{
	const int all=(1<<ET[u].size())-1;
	if(u==to)return DP[u][all-(1<<EDGE_LOC[u][pre_ei])-(1<<EDGE_LOC[u][ei])];
	int nxt;assert(GetNxt(u,OUTLET[u][to],nxt));
	return DP[u][all-(1<<EDGE_LOC[u][pre_ei])-(1<<OUTLET[u][to])]+GetPathCost(ET[u][OUTLET[u][to]],nxt,to,ei);
}
int GetPathCost(const int u,const int to,const int ei)
{
	assert(OUTLET[u][to]!=-1);
	int nxt;assert(GetNxt(u,OUTLET[u][to],nxt));
	return GetPathCost(ET[u][OUTLET[u][to]],nxt,to,ei);
}
void BuildDP(const int u,const int parent,vector<int>&edges)
{
	const int *outlet=OUTLET[u];
	if(true)
	{
		vector<vector<int> >ch_edges;
		ch_edges.resize(ET[u].size());
		if(true)
		{
			vector<int>my_edges;
			for(const int ei:edges)
			{
				const Edge &e=EDGE[ei];
				if(e.a==u||e.b==u)my_edges.push_back(ei);
				else
				{
					assert(outlet[e.a]!=-1&&outlet[e.b]!=-1);
					if(outlet[e.a]==outlet[e.b])ch_edges[outlet[e.a]].push_back(ei);
					else my_edges.push_back(ei);
				}
			}
			edges.swap(my_edges);
			vector<int>().swap(my_edges);
		}
		for(int i=0,nxt;i<(int)ET[u].size();i++)if(GetNxt(u,i,nxt)&&nxt!=parent)BuildDP(nxt,u,ch_edges[i]);
		vector<vector<int> >().swap(ch_edges);
	}
	int *dp=DP[u];
	const int n=ET[u].size(),all=(1<<n)-1;
	for(int s=0;s<=all;s++)dp[s]=0;
	for(const int ei:edges)
	{
		const Edge &e=EDGE[ei];
		if(e.a==u||e.b==u)
		{
			const int to=(e.a==u?e.b:e.a);
			assert(outlet[to]!=-1);
			getmax(dp[(1<<outlet[to])+(1<<EDGE_LOC[u][ei])],GetPathCost(u,to,ei)+e.cost);
		}
		else
		{
			assert(outlet[e.a]!=outlet[e.b]);
			getmax(dp[(1<<outlet[e.a])+(1<<outlet[e.b])],GetPathCost(u,e.a,ei)+GetPathCost(u,e.b,ei)+e.cost);
		}
	}
	int *full=new int[n];
	for(int i=0;i<n;i++)full[i]=0;
	for(int i=0,nxt;i<(int)ET[u].size();i++)if(GetNxt(u,i,nxt)&&nxt!=parent)full[i]=DP[nxt][(1<<ET[nxt].size())-1];
	vector<int>updates;
	for(int s=0;s<=all;s++)if(dp[s])updates.push_back(s);//,printf("DP[%d][%d]=%d\n",u,s,dp[s]);
	vector<vector<int> >sets;
	sets.resize(n+1);
	for(int s=0;s<=all;s++)sets[CntBits(s)].push_back(s);
	for(int bitcnt=0;bitcnt<n;bitcnt++)
	{
		for(const int s:sets[bitcnt])
		{
			for(int i=0;i<n;i++)if(!(s&(1<<i)))getmax(dp[s+(1<<i)],dp[s]+full[i]);
			for(const int v:updates)if(!(s&v))getmax(dp[s+v],dp[s]+dp[v]);
		}
	}
	vector<vector<int> >().swap(sets);
}
//void MergeFiles()
//{
//	freopen("new.txt","w",stdout);
//	for(int i=1;i<=11;i++)
//	{
//		for(int j=0;j<(i<=7?2:(i<=9?3:4));j++)
//		{
//			static char filename[1000];
//			sprintf(filename,"training.out.%d%c",i,'a'+j);
//			freopen(filename,"r",stdin);
//			for(char c;scanf("%c",&c)==1;)putchar(c);
//		}
//	}
//	exit(0);
//}
int main()
{
//	MergeFiles();
	freopen("inn.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		int sum=0;
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			sum+=c;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		assert((int)BuildOUTLET(0,-1,0).size()==N);
		for(int i=0;i<N;i++)
		{
			int *edge_loc=EDGE_LOC[i];
			for(int j=0;j<M;j++)edge_loc[j]=0;
			for(int j=0;j<(int)ET[i].size();j++)edge_loc[ET[i][j]]=j;
		}
		vector<int>edges;
		for(int ei=0;ei<M;ei++)
		{
			const Edge &e=EDGE[ei];
			if(COLOR[e.a]==COLOR[e.b]&&e.cost!=0)edges.push_back(ei);
		}
		BuildDP(0,-1,edges);
		printf("%d\n",sum-DP[0][(1<<ET[0].size())-1]);
	}
	return 0;
}
