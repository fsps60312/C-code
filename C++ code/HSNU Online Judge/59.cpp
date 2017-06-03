#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(const int &_a,const int &_b,const int &_c):a(_a),b(_b),c(_c){}
};
vector<Edge>EDGE;
vector<int>ET[5000];
int DIST1[5000],DIST2[5000];
bool INQ[5000];
void Bfs(const int &s,int *dist)
{
	for(int i=0;i<N;i++)dist[i]=INF;
	queue<int>q;
	dist[s]=0;
	q.push(s);
	INQ[s]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			const Edge &e=EDGE[ET[u][i]];
			const int &nxt=(u==e.a?e.b:e.a);
			if(dist[u]+e.c<dist[nxt])
			{
				dist[nxt]=dist[u]+e.c;
				if(!INQ[nxt])
				{
					q.push(nxt);
					INQ[nxt]=true;
				}
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i);
			ET[b].push_back(i);
		}
		Bfs(0,DIST1);
		Bfs(N-1,DIST2);
		assert(DIST1[N-1]==DIST2[0]);
		int mn=DIST1[N-1],ans=INF;
		for(int i=0;i<EDGE.size();i++)
		{
			static int ta;
			Edge &e=EDGE[i];
			ta=DIST1[e.a]+DIST2[e.b]+e.c;
			if(mn<ta&&ta<ans)ans=ta;
			ta=DIST1[e.b]+DIST2[e.a]+e.c;
			if(mn<ta&&ta<ans)ans=ta;
		}
		if(ans==INF)puts("0");
		else printf("%d\n",ans);
	}
	return 0;
}
