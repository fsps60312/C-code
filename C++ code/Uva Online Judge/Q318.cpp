#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
struct Edge
{
	int a,b,l;
	Edge(){}
	Edge(const int _a,const int _b,const int _l):a(_a),b(_b),l(_l){}
};
vector<Edge>EDGE;
vector<int>ET[500];
int N,M;
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
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,l;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&l),a--,b--;
			EDGE.push_back(Edge(a,b,l));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		priority_queue<Pq>pq;
		pq.push(Pq(0,0));
		int *dist=new int[N];
		for(int i=0;i<N;i++)dist[i]=-1;
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(dist[p.u]!=-1)continue;
			dist[p.u]=p.cost;
			for(const int ei:ET[p.u])
			{
				const Edge &e=EDGE[ei];
				const int nxt=(p.u==e.a?e.b:e.a);
				pq.push(Pq(nxt,p.cost+e.l));
			}
		}
		int target=0;
		for(int i=1;i<N;i++)if(dist[i]>dist[target])target=i;
		int ans1=target,ans2=target,time=dist[target]*2;
		for(const Edge &e:EDGE)
		{
			if(dist[e.a]+dist[e.b]+e.l>time)
			{
				time=dist[e.a]+dist[e.b]+e.l;
				ans1=e.a,ans2=e.b;
			}
		}
		ans1++,ans2++;
		static int kase=1;
		printf("System #%d\n",kase++);
		if(ans1==ans2)printf("The last domino falls after %.1f seconds, at key domino %d.\n",0.5*time,ans1);
		else printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n",0.5*time,min(ans1,ans2),max(ans1,ans2));
		puts("");
	}
	return 0;
}
