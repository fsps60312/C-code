#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(min(_a,_b)),b(max(_a,_b)){}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
};
vector<Edge>EDGE;
bool HasEdge(const int a,const int b)
{
	Edge e=Edge(a,b);
	return upper_bound(EDGE.begin(),EDGE.end(),e)!=lower_bound(EDGE.begin(),EDGE.end(),e);
}
vector<int>ET[100000];
int N,M,K,A,B;
int DIST[300000];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d%d",&N,&M,&K,&A,&B),K--;
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		EDGE.push_back(Edge(a,b));
	}
	sort(EDGE.begin(),EDGE.end());
	for(int i=0;i<M;i++)ET[EDGE[i].a].push_back(i),ET[EDGE[i].b].push_back(i);
	for(int i=0;i<N+M+M;i++)DIST[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(K,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]<=p.cost)continue;
		DIST[p.u]=p.cost;
		const int u=(p.u<N?p.u:(p.u<N+M?EDGE[p.u-N].a:EDGE[p.u-N-M].b));
//		printf("p.u=%d,cost=%d,u=%d\n",p.u,DIST[p.u],u);
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int ei=ET[u][i];
			const Edge &e=EDGE[ei];
			const int nxt=(u==e.a?e.b:e.a);
			if(p.u<N)
			{
				pq.push(Pq(nxt,p.cost+A));
//				printf("to %d\n",nxt);
				if(nxt==e.a)pq.push(Pq(N+ei,p.cost+B));
				else pq.push(Pq(N+M+ei,p.cost+B));
			}
			else if(p.u<N+M)
			{
				const Edge &oe=EDGE[p.u-N];
				const int ou=(u==oe.a?oe.b:oe.a);
				if(ou==nxt||HasEdge(ou,nxt))continue;
//				printf("from %d to %d to %d\n",ou,u,nxt);
				pq.push(Pq(nxt,p.cost));
			}
			else
			{
				const Edge &oe=EDGE[p.u-N-M];
				const int ou=(u==oe.a?oe.b:oe.a);
				if(ou==nxt||HasEdge(ou,nxt))continue;
//				printf("from %d to %d to %d\n",ou,u,nxt);
				pq.push(Pq(nxt,p.cost));
			}
		}
	}
	for(int i=0;i<N;i++)printf("%d\n",DIST[i]);
	return 0;
}
