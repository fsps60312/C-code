#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Pair
{
	int a,b;
	Pair(){}
	Pair(const int _a,const int _b):a(_a),b(_b){}
};
struct Edge
{
	int end[2],d;
	Edge(){}
	Edge(const int _a,const int _b):end{_a,_b},d(-1){}
};
int N,M;
vector<Edge>EDGE;
vector<int>ET[1000];
int PRE[1000],LOW[1000],PRE_CNT,NODE[1000],MXP[1000];
vector<Pair>ANS;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const auto ei:ET[u])if(ei!=fa)
	{
		Edge &e=EDGE[ei];
		const int endid=(u==e.end[0]?1:0);
		const int nxt=e.end[endid];
		if(PRE[nxt])
		{
			getmin(LOW[u],PRE[nxt]);
			if(e.d==-1)e.d=endid,ANS.push_back(Pair(e.end[e.d^1],e.end[e.d]));
		}
		else
		{
			ANS.push_back(Pair(u,nxt));
			e.d=endid;
			Dfs(nxt,ei);
			getmin(LOW[u],LOW[nxt]);
			if(LOW[nxt]>PRE[u])ANS.push_back(Pair(nxt,u));
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&N,&M)==2);
		if(N==0&&M==0)break;
		assert(N>=2&&N<=1000);
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b)==2);
			a--,b--;
			assert(a>=0&&a<N&&b>=0&&b<N);
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<N;i++)PRE[i]=MXP[i]=0;
		PRE_CNT=0;
		ANS.clear();
		Dfs(0,-1);
//		for(int i=0;i<N;i++)printf(" %d",PRE[i]);puts("");
//		for(int i=0;i<N;i++)printf(" %d",LOW[i]);puts("");
		static int kase=1;
		printf("%d\n\n",kase++);
		for(const Pair &p:ANS)printf("%d %d\n",p.a+1,p.b+1);
		puts("#");
	}
	assert(scanf("%d",&N)!=1);
	return 0;
}
