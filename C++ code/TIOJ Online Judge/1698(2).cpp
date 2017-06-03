#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<stack>
#include<algorithm>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Djset
{
	int data[100000];
	void Clear(const int n){for(int i=0;i<n;i++)data[i]=i;}
	int Find(const int a){return data[a]==a?a:(data[a]=Find(data[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;data[a]=b;return true;}
	int operator[](const int i){return Find(i);}
}DJ;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
vector<int>ANS;
struct BccSolver
{
	vector<int>ET[100000];
	int PRE[100000],PRE_CNT;
	bool VIS[400000];
	stack<int>STK;
	int Dfs(const int u)
	{
		int low=PRE[u]=++PRE_CNT;
		for(const int ei:ET[u])if(!VIS[ei])
		{
			VIS[ei]=true;
			const Edge &e=EDGE[ei];
			const int nxt=(u==DJ[e.a]?DJ[e.b]:DJ[e.a]);
			if(!PRE[nxt])
			{
				const int nxt_low=Dfs(nxt);
				getmin(low,nxt_low);
				if(nxt_low>PRE[u])ANS.push_back(ei);
			}
			else getmin(low,PRE[nxt]);
		}
		return low;
	}
	void Solve(const vector<int>&edges)
	{
		for(const int ei:edges)
		{
			const Edge &e=EDGE[ei];
			assert(DJ[e.a]!=DJ[e.b]);
			ET[DJ[e.a]].clear(),ET[DJ[e.b]].clear();
			PRE[DJ[e.a]]=PRE[DJ[e.b]]=0;
			VIS[ei]=false;
		}
		for(const int ei:edges)
		{
			const Edge &e=EDGE[ei];
			ET[DJ[e.a]].push_back(ei),ET[DJ[e.b]].push_back(ei);
		}
		PRE_CNT=0;
		for(const int ei:edges)
		{
			const Edge &e=EDGE[ei];
			if(!PRE[DJ[e.a]])Dfs(DJ[e.a]),assert(STK.empty());
			assert(PRE[DJ[e.b]]);
		}
	}
}BCC;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	EDGE.clear();
	map<int,vector<int> >sorted_edge;
	for(int i=0,a,b,c;i<M;i++)
	{
		scanf("%d%d%d",&a,&b,&c),a--,b--;
		EDGE.push_back(Edge(a,b,c));
		sorted_edge[c].push_back(i);
	}
	DJ.Clear(N);
	ANS.clear();
	for(const auto &it:sorted_edge)
	{
		vector<int>edges;
		for(const int ei:it.second)if(DJ[EDGE[ei].a]!=DJ[EDGE[ei].b])edges.push_back(ei);
		BCC.Solve(edges);
		for(const int ei:edges)DJ.Merge(EDGE[ei].a,EDGE[ei].b);
	}
	printf("%d\n",(int)ANS.size());
	if(ANS.empty())puts("0");
	else
	{
		sort(ANS.begin(),ANS.end());
		assert(unique(ANS.begin(),ANS.end())==ANS.end());
		for(int i=0;i<(int)ANS.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]+1);
		}
		puts("");
	}
	return 0;
}
