#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
inline void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b,cost,monster;
	Edge(){}
	Edge(const int _a,const int _b,const int _cost,const int _monster):a(_a),b(_b),cost(_cost),monster(_monster){}
};
struct Pq
{
	int u,sword,dist;
	Pq(){}
	Pq(const int _u,const int _sword,const int _dist):u(_u),sword(_sword),dist(_dist){}
};
bool operator<(const Pq &a,const Pq &b){return a.dist>b.dist;}
vector<Edge>EDGE;
int N,M,P,K,C[200];
int DIST[200][1<<13];
vector<int>ET[200];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&P,&K)==4)
	{
		for(int i=0;i<N;i++)C[i]=0;
		for(int i=0,w,q;i<K;i++)
		{
			scanf("%d%d",&w,&q),--w;
			for(int r;q--;)scanf("%d",&r),C[w]|=1<<(--r);
		}
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,v,w,t,s;i<M;i++)
		{
			scanf("%d%d%d%d",&v,&w,&t,&s),--v,--w;
			int monster=0;
			for(int u;s--;)scanf("%d",&u),monster|=1<<(--u);
			EDGE.push_back(Edge(v,w,t,monster));
			ET[v].push_back(i),ET[w].push_back(i);
		}
		for(int i=0;i<N;i++)for(int j=0;j<(1<<P);j++)DIST[i][j]=INF;
		priority_queue<Pq>pq;pq.push(Pq(0,0,0));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DIST[p.u][p.sword]<=p.dist)continue;
			DIST[p.u][p.sword]=p.dist;
			if((p.sword|C[p.u])!=p.sword)
			{
				pq.push(Pq(p.u,p.sword|C[p.u],p.dist));
			}
			else
			{
				for(int i=0;i<(int)ET[p.u].size();i++)
				{
					const int ei=ET[p.u][i];
					const Edge &e=EDGE[ei];
					if((p.sword&e.monster)!=e.monster)continue;
					const int nxt=(e.a==p.u?e.b:e.a);
					pq.push(Pq(nxt,p.sword,p.dist+e.cost));
				}
			}
		}
		int ans=INF;
		for(int i=0;i<(1<<P);i++)getmin(ans,DIST[N-1][i]);
		printf("%d\n",ans==INF?-1:ans);
	}
	return 0;
}
