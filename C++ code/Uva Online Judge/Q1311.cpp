#include<cstdio>
#include<vector>
//#include<cassert>
#include<queue>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
bool AtRange(const int o,const int l,const int r){return l<=o&&o<=r;}
//For all U such dist(U)<=dist(W)
//if and only if rank(U)<=rank(W)
//W is interested in V
int N,M;
int RANK[30000];
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
vector<Edge>EDGE;
vector<int>ET[30000];
struct Pq
{
	int u,cost;
	Pq(){}
	Pq(const int _u,const int _c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost>p.cost:RANK[u]<RANK[p.u];}
};
int DIST[30000];
int Solve()
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)DIST[j]=INF;
		priority_queue<Pq>pq;
		pq.push(Pq(i,0));
		int mxrank=0;
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DIST[p.u]!=INF)continue;
			DIST[p.u]=p.cost;
			for(const int ei:ET[p.u])
			{
				const Edge &e=EDGE[ei];
				const int nxt=(p.u==e.a?e.b:e.a);
				pq.push(Pq(nxt,p.cost+e.cost));
			}
			if(RANK[p.u]>=mxrank)ans++; 
			if(RANK[p.u]>mxrank)mxrank=RANK[p.u];
		}
	}
	return ans;
}
//#include<ctime>
int main()
{
//	auto aaa=clock();
//	for(int i=0;i<30000;i++)for(int j=0;j<30000;j++);
//	printf("%.3f\n",(double)(clock()-aaa)/CLOCKS_PER_SEC);
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		assert(AtRange(N,1,30000));
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<N;i++)assert(scanf("%d",&RANK[i])==1&&AtRange(--RANK[i],0,9));
		for(int i=0,a,b,c;i<M;i++)
		{
			assert(scanf("%d%d%d",&a,&b,&c)==3&&AtRange(--a,0,N-1)&&AtRange(--b,0,N-1)&&c>0);
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		printf("%d\n",Solve());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
