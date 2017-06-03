#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;} 
int N,M,ANS;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
vector<int>ET[50000];
int PRE[50000],LOW[50000],PRE_CNT;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(!PRE[nxt])
		{
			Dfs(nxt,ei);
			getmin(LOW[u],LOW[nxt]);
			if(PRE[u]<LOW[nxt])ANS++;
		}
		else getmin(LOW[u],PRE[nxt]);
	}
} 
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)PRE[i]=0,ET[i].clear();
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b),a--,b--;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		ANS=PRE_CNT=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1);
		for(int i=0;i<N;i++)assert(PRE[i]!=0);
		printf("%d\n",ANS);
	}
	return 0;
}
