#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
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
vector<vector<int> >PRE;
int N,M,P;
int REMAIN[5000];
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
		}
		scanf("%d",&P);
		for(int i=0;i<P;i++)scanf("%d",&REMAIN[i]),--REMAIN[i];
		vector<Edge>es;
		PRE.resize(P);
		for(int i=0;i<P;i++)
		{
			static int dist[5000];
			for(int j=0;j<N;j++)dist[j]=INF;
			PRE[i].resize(N);
			Bfs(REMAIN[i],dist,&PRE[i][0]);
			for(int j=i+1;j<P;j++)es.push_back(Edge(i,j,dist[REMAIN[j]]));
		}
		sort(es.begin(),es.end());
		DJ.Clear(P);
		set<int>ans;
		for(int i=0;i<(int)es.size();i++)
		{
			const Edge &e=es[i];
			if(DJ.Merge(e.A,e.B))
			{
				int cur=REMAIN[e.B];
				for(;cur!=REMAIN[e.A];)
				{
					ans.insert(PRE[e.A][cur]);
					const Edge &f=EDGE[PRE[e.A][cur]];
					cur=(cur==f.A?f.B:f.A);
				}
//				printf("(%d,%d)\n",REMAIN[e.A]+1,REMAIN[e.B]+1);
			}
		}
		int ans_cost=0;
		for(set<int>::iterator it=ans.begin();it!=ans.end();++it)ans_cost+=EDGE[*it].COST;
		printf("%d %d\n",ans_cost,(int)ans.size());
		for(set<int>::iterator it=ans.begin();it!=ans.end();++it)printf("%d %d\n",EDGE[*it].A+1,EDGE[*it].B+1);
	}
	return 0;
}
