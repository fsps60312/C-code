#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int N;
void Dfs(const int u,const int fa,const int cost,int &maxcost,int &ans)
{
	if(cost>maxcost)maxcost=cost,ans=u;
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		Dfs(nxt,ei,cost+e.cost,maxcost,ans);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b,c;i<N-1;i++)
	{
		scanf(3,"%d%d%d",&a,&b,&c),a--,b--;
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	int maxcost=-1,ans=-1;
	Dfs(0,-1,0,maxcost,ans);
	assert(ans!=-1);
	Dfs(ans,-1,0,maxcost,ans);
	printf("%d.%c\n",maxcost/2,(maxcost&1?'5':'0'));
	return 0;
}
