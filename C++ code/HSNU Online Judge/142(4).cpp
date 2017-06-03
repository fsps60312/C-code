#include<cstdio>
#include<vector>
#include<set>
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
set<int>BRIDGE;
void Dfs(const int u,const int fa)
{
//	printf("u=%d\n",u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
//		printf("Edge(%d,%d):%d\n",e.a,e.b,ei);
		if(!PRE[nxt])
		{
			Dfs(nxt,ei);
			getmin(LOW[u],LOW[nxt]);
			if(PRE[u]<LOW[nxt])
			{
//				if(BRIDGE.find(ei)!=BRIDGE.end())
//				{
//					printf("N=%d,M=%d\n",N,M);
//					for(Edge &e:EDGE)printf("(%d,%d)\n",e.a,e.b);
//				}
				assert(BRIDGE.find(ei)==BRIDGE.end());
				BRIDGE.insert(ei);
				ANS++;
			}
		}
		else getmin(LOW[u],PRE[nxt]);
	}
} 
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)PRE[i]=0,ET[i].clear();
		EDGE.clear();
		BRIDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b),a--,b--;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		ANS=PRE_CNT=0;
		Dfs(0,-1);
		printf("%d\n",ANS);
	}
	return 0;
}
