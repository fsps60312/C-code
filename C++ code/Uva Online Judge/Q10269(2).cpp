#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
int INF=(1<<30)-1;
int T,A,B,M,L,K,N;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(int to,int cost):to(to),cost(cost){}
};
vector<Edge>AD[100];
bool VIS[100][11][501];
struct Pq
{
	int u,cost,jump,l;
	Pq(){}
	Pq(int u,int cost,int jump,int l):u(u),cost(cost),jump(jump),l(l){}
	bool operator<(const Pq &p)const
	{
		if(cost!=p.cost)return cost>p.cost;
		if(jump!=p.jump)return jump>p.jump;
		return l<p.l;
	}
};
Pq solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<=K;j++)for(int k=0;k<=L;k++)VIS[i][j][k]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(N-1,0,0,0));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(VIS[p.u][p.jump][p.l])continue;
		VIS[p.u][p.jump][p.l]=true;
		if(p.u==0)return p;
		for(int i=0;i<AD[p.u].size();i++)
		{
			Edge &e=AD[p.u][i];
			if(p.u<A&&p.l>=e.cost)pq.push(Pq(e.to,p.cost,p.jump,p.l-e.cost));
			else
			{
				pq.push(Pq(e.to,p.cost+e.cost,p.jump,0));
				if(p.jump<K&&e.cost<=L)pq.push(Pq(e.to,p.cost,p.jump+1,L-e.cost));
			}
		}
	}
	assert(0);
}
int main()
{
//	freopen("inn.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d%d%d",&A,&B,&M,&L,&K);
			N=A+B;
			for(int i=0;i<N;i++)AD[i].clear();
			for(int i=0;i<M;i++)
			{
				static int a,b,l;scanf("%d%d%d",&a,&b,&l);
				a--,b--;
				AD[a].push_back(Edge(b,l));
				AD[b].push_back(Edge(a,l));
			}
			Pq ans=solve();
			printf("%d\n",ans.cost);
		}
	}
	return 0;
}
