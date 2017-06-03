#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int T,N,M;
LL P;
struct Edge
{
	int u;
	LL cost;
	Edge(){}
	Edge(const int _u,const LL _c):u(_u),cost(_c){}
//	bool operator<(const Edge &e)const{return u!=e.u?u<e.u:cost<e.cost;}
};
vector<Edge>ET[100];
LL DIST[100];
bool INQ[100];
int CNT[100];
bool Bfs(const int s)
{
	for(int i=0;i<N;i++)DIST[i]=-INF,INQ[i]=false,CNT[i]=0;
	queue<int>q;
	DIST[s]=0LL;
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
		scanf("%d%d%lld",&N,&M,&P);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<M;i++)
		{
			static int a,b;
			static LL income,afford,cost;
			scanf("%d%d%lld%lld",&a,&b,&income,&afford);
			a--,b--;
			cost=income-afford*P;
			ET[a].push_back(Edge(b,cost));
		}
//		for(int i=0;i<N;i++)
//		{
//			vector<Edge>&edge=ET[i];
//			sort(edge.begin(),edge.end());
//			for(int j=1;j<edge.size();j++)if(edge[j-1].u==edge[j].u)edge[j-1].u=INF;
//			sort(edge.begin(),edge.end());
//			for(int j=(int)edge.size()-1;j>=0&&edge[j].u==INF;j--)edge.pop_back();
//		}
		puts(Solve()?"Yes":"No");
	}
	return 0;
}
