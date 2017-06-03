//#include "lib1692.h"
#include<cstdio> 
#include<vector>
#include<set>
#include<stack>
using namespace std;
void Init(){}
void GetVE(int &V,int &E){V=5,E=4;}
void Get(int &a,int &b)
{
	static int tick=0;
	static int as[4]={1,1,3,1},bs[4]={2,2,5,4};
	a=as[tick],b=bs[tick];
	tick++;
}
///////////////////////////////////////////////////////////////
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	bool vis;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b),vis(false){}
};
vector<Edge>EDGE;
set<int>ET[1000];
int PRE[1000],BCC[1000],PRE_CNT,BCC_CNT;
stack<int>STK;
int Dfs(const int u,const int parent)
{
	int low=PRE[u]=++PRE_CNT;
	STK.push(u);
	for(const int ei:ET[u])if(ei!=parent)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(!PRE[nxt])
		{
			const int ch_low=Dfs(nxt,ei);
			getmin(low,ch_low);
			if(ch_low>PRE[u])
			{
				for(;;)
				{
					const int v=STK.top();STK.pop();
					BCC[v]=BCC_CNT;
					if(v==u)break;
				}
				BCC_CNT++;
			}
		}
		else if(BCC[nxt]==-1)getmin(low,PRE[nxt]);
	}
	return low;
}
int N,M,DEGREE[1000];
int main()
{
	Init();
	GetVE(N,M);
	for(int i=0;i<N;i++)ET[i].clear(),DEGREE[i]=0;
	EDGE.clear();
	for(int i=0,a,b;i<M;i++)
	{
		Get(a,b),a--,b--;
		EDGE.push_back(Edge(a,b));
		ET[a].insert(i),ET[b].insert(i);
		DEGREE[a]++,DEGREE[b]++;
	}
	for(int i=0;i<N;i++)PRE[i]=0,BCC[i]=-1;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1);
	
	return 0;
}
