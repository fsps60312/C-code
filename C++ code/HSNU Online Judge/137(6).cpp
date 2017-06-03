#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,cost;
	bool intree;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c),intree(false){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int N,M;
struct Pq
{
	int u,pre,cost;
	Pq(){}
	Pq(const int _u,const int _p,const int _c):u(_u),pre(_p),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
int DIST[100000];
void BuildTree()
{
	for(int i=0;i<N;i++)DIST[i]=INF;
	priority_queue<Pq>pq;
	pq.push(Pq(0,-1,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(DIST[p.u]!=INF){assert(p.cost>DIST[p.u]);continue;}
		DIST[p.u]=p.cost;
		if(p.pre!=-1)EDGE[p.pre].intree=true;
		for(const int ei:ET[p.u])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(e.a==p.u?e.b:e.a);
			pq.push(Pq(nxt,ei,p.cost+e.cost));
		}
	}
}
int ANS[100000];
void getmin(int &a,const int b){if(b<a)a=b;}
struct CmpEdge{bool operator()(const int a,const int b)const
{
	const Edge &e1=EDGE[a],&e2=EDGE[b];
	return e1.cost+DIST[e1.a]+DIST[e1.b]>e2.cost+DIST[e2.a]+DIST[e2.b];
}};
typedef priority_queue<int,vector<int>,CmpEdge> prique_dfs;
prique_dfs *Merge(prique_dfs *a,prique_dfs *b)
{
	if(a->size()<b->size())swap(a,b);
	while(!b->empty())a->push(b->top()),b->pop();
	return a;
}
set<int>*Merge(set<int>*a,set<int>*b)
{
	if(a->size()<b->size())swap(a,b);
	for(const int v:*b)a->insert(v);
	b->clear();
	return a;
}
int GetCost(const set<int>*ch,const int ei)
{
	const Edge &e=EDGE[ei];
	const auto hasa=(ch->find(e.a)!=ch->end()),hasb=(ch->find(e.b)!=ch->end());
	if(hasa&&hasb)return INF;
	assert(hasa||hasb);
	return DIST[e.a]+DIST[e.b]+e.cost;
}
void Dfs(const int u,const int fa,prique_dfs* &pq,set<int>* &ch)
{
	vector<int>edge;
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(e.intree)
		{
			prique_dfs *nxtpq=new prique_dfs();
			set<int>*nxtch=new set<int>();
			Dfs(nxt,ei,nxtpq,nxtch);
			pq=Merge(pq,nxtpq);
			ch=Merge(ch,nxtch);
		}
		else
		{
			edge.push_back(ei);
			assert(DIST[nxt]!=INF);
			getmin(ANS[u],e.cost+DIST[nxt]);
		}
	}
	int tmp=INF;
	while(!pq->empty()&&(tmp=GetCost(ch,pq->top()))==INF)pq->pop();
	if(tmp!=INF)getmin(ANS[u],tmp-DIST[u]);
	ch->insert(u);
	for(const int ei:edge)pq->push(ei);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			assert(scanf("%d%d%d",&a,&b,&c)==3);
			EDGE.push_back(Edge(--a,--b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		BuildTree();
		for(int i=0;i<N;i++)ANS[i]=INF;//,printf("dist[%d]=%d\n",i,DIST[i]);
		prique_dfs *tmppq=new prique_dfs();
		set<int>*tmpch=new set<int>();
		Dfs(0,-1,tmppq,tmpch);
		for(int i=1;i<N;i++)printf("%d\n",ANS[i]==INF?-1:ANS[i]);
	}
	return 0;
}
