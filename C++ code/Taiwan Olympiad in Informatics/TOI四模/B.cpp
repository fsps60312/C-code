#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int INF=2147483647;
struct Bit
{
	int S[1000*1001/2+1],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int v){++i;for(;i<=N;i+=(i&(-i)))S[i]+=v;}
	int Query(int i){++i;int ans=0;for(;i;i-=(i&(-i)))ans+=S[i];return ans;}
	int Query_nth(const int th)
	{
		int l=0,r=N-1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Query(mid)<th)l=mid+1;
			else r=mid;
		}
		return r;
	}
}BIT;
struct Edge
{
	int a,b,dist;
	Edge(){}
	Edge(const int _a,const int _b,const int _dist):a(_a),b(_b),dist(_dist){}
};
vector<Edge>EDGE;
int N,START,END,M;
set<int>ET[1000];
int PARENT[1000],DIST[1000];
set<int>EM[1000];
void RemoveSubTree(const int u)
{
	for(const int nxt:EM[u])PARENT[nxt]=-1,DIST[nxt]=INF,RemoveSubTree(nxt);
	EM[u].clear();
}
void RemoveTrench(const int u)
{
	assert(EM[u].empty());
	if(PARENT[u]==-1)return;
	EM[PARENT[u]].erase(u);
	if(EM[PARENT[u]].empty())RemoveTrench(PARENT[u]);
	PARENT[u]=-1,DIST[u]=INF;
}
struct Pq
{
	int u,pre,dist;
	Pq(){}
	Pq(const int _u,const int _pre,const int _dist):u(_u),pre(_pre),dist(_dist){}
	bool operator<(const Pq &p)const{return dist>p.dist;}
};
bool BuildMinPathTree()
{
	for(int i=0;i<N;i++)PARENT[i]=-1,DIST[i]=INF,EM[i].clear();
	priority_queue<Pq>pq;pq.push(Pq(START,-1,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.dist>=DIST[p.u])continue;
		DIST[p.u]=p.dist;
		if(p.pre!=-1)
		{
			PARENT[p.u]=p.pre;
			EM[p.pre].insert(p.u);
		}
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			pq.push(Pq(e.b,p.u,p.dist+e.dist));
		}
	}
	return DIST[END]!=INF;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%d%d%d",&START,&END,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		BIT.Clear(M);
		EDGE.clear();
		for(int i=0,a,b,dist;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&dist);
			EDGE.push_back(Edge(a,b,dist));
			ET[a].insert(i);
			BIT.Add(i,1);
		}
		vector<int>ans;
		int d=-1;
		while(BuildMinPathTree())
		{
			for(;;)
			{
				++d;
				ans.push_back(DIST[END]);
				const int ei=BIT.Query_nth(DIST[END]%(M-d));
				printf("ei=%d\n",ei);
				BIT.Add(ei,-1);
				const Edge &e=EDGE[ei];
				const int a=(DIST[e.a]<DIST[e.b]?e.a:e.b),b=(a==e.a?e.b:e.a);
				RemoveSubTree(b);
				RemoveTrench(b);
				assert(ET[e.a].find(ei)!=ET[e.a].end()&&ET[e.b].find(ei)!=ET[e.b].end());
				ET[e.a].erase(ei),ET[e.b].erase(ei);
				if(DIST[END]==INF)break;
				break;
			}
		}
		printf("%d\n",(int)ans.size());
		for(const int v:ans)printf("%d\n",v);
	}
	return 0;
}
