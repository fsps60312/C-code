#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int to,l;
	Edge(){}
	Edge(int to,int l):to(to),l(l){}
};
vector<Edge>AD[100];
int X,Y,K,N,M;
int DP[100][10];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(int u,int cost):u(u),cost(cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int Solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<K;j++)DP[i][j]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(X,0));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		int k=0;
		for(;k<K&&DP[p.u][k]!=INF;k++);
		if(k==K)continue;
		DP[p.u][k]=p.cost;
		if(p.u==Y&&k==K-1)return p.cost;
		for(int i=0;i<AD[p.u].size();i++)
		{
			Edge &e=AD[p.u][i];
			pq.push(Pq(e.to,p.cost+e.l));
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		scanf("%d%d%d",&X,&Y,&K);
		X--,Y--;
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
		}
		for(int i=0;i<M;i++)
		{
			static int a,b,l;
			scanf("%d%d%d",&a,&b,&l);
			a--,b--;
			AD[a].push_back(Edge(b,l));
		}
		printf("%d\n",Solve());
	}
	return 0;
}
