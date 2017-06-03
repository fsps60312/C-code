#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(const int _t,const int _c):to(_t),cost(_c){}
};
vector<Edge>ET[101];
int N,M,DIST[101],CNT[101];
bool INQ[101];
bool Solve()
{
	for(int i=0;i<=N;i++)DIST[i]=CNT[i]=0;
	queue<int>q;
	for(int i=0;i<=N;i++)q.push(i),INQ[i]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(++CNT[u]>2*N)return true;
		INQ[u]=false;
		for(const Edge &e:ET[u])
		{
			if(DIST[u]+e.cost>DIST[e.to])
			{
				DIST[e.to]=DIST[u]+e.cost;
				if(!INQ[e.to])q.push(e.to),INQ[e.to]=true;
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<=N;i++)ET[i].clear();
		scanf("%d",&M);
		for(int i=0;i<M;i++)
		{
			static int s,n,k;
			static char o[3];
			scanf("%d%d%s%d",&s,&n,o,&k);
			if(o[0]=='g')ET[s+n].push_back(Edge(s-1,k+1));
			else if(o[0]=='l')ET[s-1].push_back(Edge(s+n,-k+1));
			else assert(0);
		}
		puts(Solve()?"successful conspiracy":"lamentable kingdom");
	}
	return 0;
}
