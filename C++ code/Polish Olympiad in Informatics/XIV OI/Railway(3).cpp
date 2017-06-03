#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct DisjointSets
{
	int S[5000];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){return (a=Find(a))==(b=Find(b))?false:(S[a]=b,true);}
}DJ;
struct Pq
{
	int U,COST,PRE;
	Pq(){}
	Pq(const int _U,const int _COST,const int _PRE):U(_U),COST(_COST),PRE(_PRE){}
};
bool operator<(const Pq &a,const Pq &b){return a.COST>b.COST;}
struct Edge
{
	int A,B,COST;
	Edge(){}
	Edge(const int _A,const int _B,const int _COST):A(_A),B(_B),COST(_COST){}
};
bool operator<(const Edge &a,const Edge &b){return a.COST<b.COST;}
vector<Edge>EDGE;
vector<int>ET[5000];
void Bfs(const int root,int *dist,int *pre)
{
	priority_queue<Pq>pq;pq.push(Pq(root,0,-1));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(p.COST>=dist[p.U])continue;
		dist[p.U]=p.COST,pre[p.U]=p.PRE;
		for(int i=0;i<(int)ET[p.U].size();i++)
		{
			const int ei=ET[p.U][i];
			const Edge &e=EDGE[ei];
			const int nxt=(p.U==e.A?e.B:e.A);
			pq.push(Pq(nxt,p.COST+e.COST,ei));
		}
	}
}
int DIST[5000],PRE[5000];
int N,M,P;
int REMAIN[5000];
bool IS_ANS[500000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
			IS_ANS[i]=false;
		}
		scanf("%d",&P);
		for(int i=0;i<P;i++)scanf("%d",&REMAIN[i]),--REMAIN[i];
		for(int i=0;i<N;i++)DIST[i]=INF;
		Bfs(REMAIN[0],DIST,PRE);
		vector<int>ans;
		for(int i=1;i<P;i++)
		{
			int cur=REMAIN[i];
			for(;cur!=REMAIN[0];)
			{
				if(IS_ANS[PRE[cur]])break;
				IS_ANS[PRE[cur]]=true;
				ans.push_back(PRE[cur]);
				const Edge &f=EDGE[PRE[cur]];
				cur=(cur==f.A?f.B:f.A);
			}
		}
		int ans_cost=0;
		for(int i=0;i<(int)ans.size();i++)ans_cost+=EDGE[ans[i]].COST;
		printf("%d %d\n",ans_cost,(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)printf("%d %d\n",EDGE[ans[i]].A+1,EDGE[ans[i]].B+1);
	}
	return 0;
}
