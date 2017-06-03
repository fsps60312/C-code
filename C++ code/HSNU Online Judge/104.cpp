#include<cstdio>
#include<vector>
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
int DIST[100];
bool Bfs(const int s)
{
	for(int i=0;i<N;i++)DIST[i]=-INF,INQ[i]=false;
	queue<int>q;
	q.push(s);
	DIST[s]=0;
	INQ[s]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			if(DIST[s]+e.cost<=DIST[e.u])continue;
			DIST[e.u]=DIST[s]+e.cost;
			if(!INQ[e.u])
			{
				q.push(e.u);
				INQ[e.u]=true;
			}
		}
	}
	for(int u=0;u<N;u++)
	{
		if(u==s||DIST[u]==-INF)continue;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			if(e.u!=s)continue;
		}
	}
}
bool Solve()
{
	for(int s=0;s<N;s++)if(Bfs(s))return true;
	return false;
}
int main()
{
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
			ET[b].push_back(Edge(a,cost));
		}
		puts(Solve()?"Yes":"No");
	}
	return 0;
}
