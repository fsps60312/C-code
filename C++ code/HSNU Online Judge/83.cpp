#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M,K;
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(const int &_a,const int &_b,const int &_c):a(_a),b(_b),c(_c){}
};
vector<Edge>EDGE;
vector<int>ET[3000];
int DIST[3000];
bool INQ[3000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear(),DIST[i]=INF,INQ[i]=false;
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
		queue<int>q;
		while(K--)
		{
			static int a;
			scanf("%d",&a);
			a--;
			if(!INQ[a])
			{
				DIST[a]=0;
				q.push(a);
				INQ[a]=true;
			}
		}
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			INQ[u]=false;
			for(int i=0;i<ET[u].size();i++)
			{
				const Edge &e=EDGE[ET[u][i]];
				const int &nxt=(e.a==u?e.b:e.a);
				if(DIST[u]+e.c<DIST[nxt])
				{
					DIST[nxt]=DIST[u]+e.c;
					if(!INQ[nxt])
					{
						q.push(nxt);
						INQ[nxt]=true;
					}
				}
			}
		}
		int ans=0;
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			const int &ta=DIST[e.a]+DIST[e.b]+e.c;
			if(ta>ans)ans=ta;
		}
		printf("%d\n",(ans+1)/2);
		break;
	}
	return 0;
}
