#include<cstdio>
#include<vector>
#include<stack>
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
bool VIS[50000];
stack<int>STK;
void Dfs(const int u,const int fa)
{
//	printf("u=%d\n",u+1);
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(PRE[nxt])getmin(LOW[u],PRE[nxt]);
		else if(!VIS[nxt])
		{
			Dfs(nxt,ei);
			getmin(LOW[u],LOW[nxt]);
			if(PRE[u]<LOW[nxt])
			{
//				printf("(%d,%d)\n",u+1,nxt+1);
				ANS++;
			}
		}
	}
	if(LOW[u]==PRE[u])
	{
		for(;;)
		{
			const int v=STK.top();STK.pop();
			VIS[v]=true;
			if(v==u)break;
		}
	}
} 
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)PRE[i]=0,VIS[i]=false,ET[i].clear();
	EDGE.clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		EDGE.push_back(Edge(a,b));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	ANS=PRE_CNT=0;
	assert(STK.empty());
	Dfs(0,-1);
	assert(STK.empty());
	printf("%d\n",ANS);
	return 0;
}
