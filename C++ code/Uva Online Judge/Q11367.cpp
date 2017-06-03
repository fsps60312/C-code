#include<cstdio>
#include<vector>
#include<queue>
using namespace std; 
int N,M,P[1000],S,E,C;
struct Edge
{
	int to,l;
	Edge(){}
	Edge(int to,int l):to(to),l(l){}
};
vector<Edge>AD[1000];
bool VIS[1000][101];
struct Pq
{
	int u,fuel,cost;
	Pq(){}
	Pq(int u,int fuel,int cost):u(u),fuel(fuel),cost(cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<=C;j++)VIS[i][j]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(S,0,0));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(VIS[p.u][p.fuel])continue;
		VIS[p.u][p.fuel]=true;
		if(p.u==E)return p.cost;
		for(int i=0;i<AD[p.u].size();i++)
		{
			Edge &e=AD[p.u][i];
			if(e.l>C)continue;
			Pq pt=p;
			pt.u=e.to;
			if(pt.fuel<e.l)pt.cost+=(e.l-pt.fuel)*P[p.u],pt.fuel=e.l;
			pt.fuel-=e.l;
			for(;pt.fuel+e.l<=C;pt.fuel++,pt.cost+=P[p.u])pq.push(pt);
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			scanf("%d",&P[i]);
		}
		for(int i=0;i<M;i++)
		{
			static int a,b,l;scanf("%d%d%d",&a,&b,&l);
			AD[a].push_back(Edge(b,l));
			AD[b].push_back(Edge(a,l));
		}
		int q;scanf("%d",&q);
		while(q--)
		{
			scanf("%d%d%d",&C,&S,&E);
			int ans=solve();
			if(ans==-1)puts("impossible");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
