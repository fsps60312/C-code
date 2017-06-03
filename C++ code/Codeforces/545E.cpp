#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Edge
{
	int id,a,b;
	LL cost;
	Edge(){}
	Edge(const int _id,const int _a,const int _b,const LL _cost):id(_id),a(_a),b(_b),cost(_cost){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>EDGE;
vector<int>ET[300000];
int N,M;
struct Pq
{
	int u;
	LL cost;
	Pq(){}
	Pq(const int _u,const LL _cost):u(_u),cost(_cost){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
LL DIST[300000];
void Bfs(const int start)
{
	for(int i=0;i<N;i++)DIST[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(start,0LL));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]<=p.cost)continue;
		DIST[p.u]=p.cost;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(p.u==e.a?e.b:e.a);
			pq.push(Pq(nxt,p.cost+e.cost));
		}
	}
}
int DJ[300000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			EDGE.push_back(Edge(i+1,a,b,c));
		}
		sort(EDGE.begin(),EDGE.end());
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			ET[e.a].push_back(i),ET[e.b].push_back(i);
		}
		int start;scanf("%d",&start);start--;
		Bfs(start);
		for(int i=0;i<N;i++)DJ[i]=i;
		LL ans=0LL;
		vector<int>s;
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			if(Find(e.a)==Find(e.b)||abs(DIST[e.a]-DIST[e.b])!=e.cost)continue;
			DJ[Find(e.a)]=Find(e.b);
			ans+=e.cost;
			s.push_back(e.id);
		}
		printf("%lld\n",ans);
		for(int i=0;i<(int)s.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",s[i]);
		}
		puts("");
	}
	return 0;
}
