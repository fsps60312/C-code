#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int N;
struct Edge
{
	int a,b,l;
	Edge(){}
	Edge(const int _a,const int _b,const int _l):a(_a),b(_b),l(_l){}
};
vector<Edge>EDGE;
vector<int>ET[1000000];
int NXT[1000000];
void FindCycle(const int u,const int fa,vector<int>&cycle,bool &found)
{
	if(NXT[u]!=-1)
	{
		assert(!found);
		cycle.clear();
		cycle.push_back(NXT[u]);
		for(int i=EDGE[NXT[u]].Nxt(i);i!=u;i=EDGE[NXT[i]].Nxt[i])cycle.push_back(NXT[i]);
		found=true;return;
	}
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==fa)continue;
		if(!found)NXT[u]=ET[u][i];
		FindCycle(nxt,u,cycle,found);
	}
}
bool VIS[1000000];
LL Solve()
{
	for(int i=0;i<N;i++)NXT[i]=-1,VIS[i]=false;
	for(int u=0;u<N;u++)if(!VIS[u])
	{
		static vector<int>cycle;
		bool found=false;
		FindCycle(u,-1,cycle,found);
		for(int i=0;i<cycle.size();i++)VIS[EDGE[cycle[i]].a]=VIS[EDGE[cycle[i]].b]=true;
		for(int s=EDGE[cycle[i]].a,i=NXT[s];i!=s;i=NXT[i])
		{
			int p=-1,dist=0;
			FindRemote(i,-1,p,dist);
			FindRemote()
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,b,l;i<N;i++)
	{
		scanf("%d%d",&b,&l);
		b--;
		EDGE.push_back(Edge(i,b,l));
		ET[i].push_back(i),ET[b].push_back(i);
	}
	printf("%lld\n",Solve());
	return 0;
}
