#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
struct Dist
{
	int dist,ei;
	Dist(){}
	Dist(const int _dist,const int _ei):dist(_dist),ei(_ei){}
};
struct State
{
	int ei,u;
	State(){}
	State(const int _ei,const int _u):ei(_ei),u(_u){}
};
int N,S,T,M;
vector<Edge>EDGE;
vector<int>ET[1000];
Dist Solve()
{
	static Dist dist[2][1000];
	for(int i=0;i<N;i++)dist[0][i]=dist[1][i]=Dist(INF,-1);
	queue<State>q;//edge, u
	q.push(State(-1,S)),dist[0][S]=Dist(0,-1);
	while(!q.empty())
	{
		const State p=q.front();q.pop();
		for(const int ei:ET[p.u])
		{
			const auto &e=EDGE[ei];
			if(p.ei==-1)
			{
				if(p.u==e.a)
				{
					if(dist[0][p.u].dist+1<dist[0][e.b].dist)
					{
						dist[0][e.b]=Dist(dist[0][p.u].dist+1,-1);
						q.push(State(-1,e.b));
					}
				}
				else
				{
					if(dist[0][p.u].dist+1<dist[1][e.a].dist)
					{
						dist[1][e.a]=Dist(dist[0][p.u].dist+1,ei);
						q.push(State(ei,e.a));
					}
				}
			}
			else
			{
				if(p.u==e.a)
				{
					if(dist[1][p.u].dist+1<dist[1][e.b].dist)
					{
						dist[1][e.b]=Dist(dist[1][p.u].dist+1,dist[1][p.u].ei);
						q.push(State(dist[1][p.u].ei,e.b));
					}
				}
			}
		}
	}
	if(dist[1][T].dist<dist[0][T].dist)return dist[1][T];
	else return dist[0][T];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%d",&S,&T),--S,--T;
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		scanf("%d",&M);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		const auto &ans=Solve();
		assert(ans.dist!=INF);
		printf("%d %d\n",ans.dist,ans.ei+1);
	}
	return 0;
}
