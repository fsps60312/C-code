#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int T,N,M,P;
struct Edge
{
	int u,cost;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),cost(_c){}
};
vector<Edge>ET[100];
int DIST[10000],INQ[10000];
bool Bfs(const int s)
{
	for(int i=0;i<N*N;i++)DIST[i]=-INF,INQ[i]=false;
	queue<int>q;
	for(int i=0;i<ET[s].size();i++)
	{
		const Edge &e=ET[s][i];
		const int nxt=s*N+e.u;
		q.push(nxt);
		INQ[nxt]=true;
		DIST[nxt]=e.cost;
	}
	while(!q.empty())
	{
		const int qf=q.front();q.pop();
		INQ[qf]=true;
		const int pre=qf/N,u=qf%N;
		if(u==s&&DIST[qf]>0)return true;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			if(e.u==pre)continue;
			const int nxt=u*N+e.u;
			if(DIST[u]+e.cost>DIST[nxt])
			{
				DIST[nxt]=DIST[u]+e.cost;
				if(!INQ[nxt])
				{
					q.push(nxt);
					INQ[nxt]=true;
				}
			}
		}
	}
	return false;
}
bool Solve()
{
	for(int s=0;s<N;s++)if(Bfs(s))return true;
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&P);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,income,afford,cost;
			scanf("%d%d%d%d",&a,&b,&income,&afford);
			cost=income-afford*P;
			ET[a].push_back(Edge(b,cost));
//			ET[b].push_back(Edge(a,cost));
		}
		puts(Solve()?"Yes":"No");
	}
	return 0;
}
