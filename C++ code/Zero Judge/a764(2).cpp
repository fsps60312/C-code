#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b,const int _c):a(_a),b(_b),cost(_c){}
};
int N,M;
int DIST[400*400];
bool INQ[400*400];
vector<int>ET[400];
vector<Edge>EDGE;
int Solve(const int source)
{
	for(int i=0;i<N*N;i++)DIST[i]=INF,INQ[i]=false;
	queue<int>q;
	for(const int ei:ET[source])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==source?e.b:e.a);
		DIST[nxt*N+source]=e.cost;
		q.push(nxt*N+source),INQ[nxt*N+source]=true;
	}
	int ans=INF;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		const int now=u/N,pre=u%N;
		if(now==source)getmin(ans,DIST[u]);
		for(const int ei:ET[now])
		{
			const Edge &e=EDGE[ei];
			const int nxt=(e.a==now?e.b:e.a);
			if(nxt==pre)continue;
			const int nxtu=nxt*N+now;
			if(DIST[u]+e.cost<DIST[nxtu])
			{
				DIST[nxtu]=DIST[u]+e.cost;
				if(!INQ[nxtu])q.push(nxtu),INQ[nxtu]=true;
			}
		}
	}
	return ans;
}
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b,c;i<M;i++)
	{
		scanf("%d%d%d",&a,&b,&c),a--,b--;
		if(a==b){M--,i--;continue;}
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	int ans=INF;
	for(int i=0;i<N;i++)getmin(ans,Solve(i));
	if(ans==INF)puts("No solution.");
	else printf("%d\n",ans);
	return 0;
}
