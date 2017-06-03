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
int DIST[100],INQ[100],CNT[100];
bool Bfs(const int s)
{
	for(int i=0;i<N;i++)DIST[i]=-INF,INQ[i]=false,CNT[i]=0;
	queue<int>q;
	DIST[s]=0;
	q.push(s);
	INQ[s]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=ET[u][i];
			const int nxt=e.u;
			if(DIST[u]+e.cost>DIST[nxt])
			{
				DIST[nxt]=DIST[u]+e.cost;
				if(!INQ[nxt])
				{
					if(++CNT[nxt]>N)return true;
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
//	freopen("in.txt","r",stdin);
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
