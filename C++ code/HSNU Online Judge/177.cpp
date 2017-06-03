#include<cstdio>
#include<vector>
using namespace std;
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100000],FA[100000];
int N,Q,LEN[100000];
void BuildFA(const int u,const int fa,const int len)
{
	LEN[u]=len;
	FA[u].clear();
	if(fa!=-1)
	{
		for(int i=0,cur=fa;;cur=FA[cur][i++])
		{
			FA[u].push_back(cur);
			if(i>=(int)FA[cur].size())break;
		}
	}
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(nxt!=fa)BuildFA(nxt,u,len+e.cost);
	}
}
int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b,cost;i<N-1;i++)
	{
		scanf("%d%d%d",&a,&b,&cost),a--,b--;
		EDGE.push_back(Edge(a,b,cost));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	BuildFA(0,-1,0);
	while(Q--)
	{
		static int s,k;scanf("%d%d",&s,&k),s--;
		int ans=LEN[s];
		for(int i=0;(1<<i)<=k;i++)if(k&(1<<i))s=FA[s][i];
		printf("%d\n",ans-=LEN[s]);
	}
	return 0;
}
