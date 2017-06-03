#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
int N;
struct Edge
{
	int a,b,w,limit,flow;
	Edge(){}
	Edge(int a,int b,int w,int l,int f):a(a),b(b),w(w),limit(l),flow(f){}
};
vector<Edge>EDGE;
vector<int>AD[200];
void AddEdge(int a,int b,int w,int l,int f)
{
	int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,w,l,f));
	AD[a].push_back(sz);
}
void AddEdge(int a,int b,int w)
{
	AddEdge(a,b,w,1,0);
	AddEdge(b,a,-w,1,1);
}
#include<queue>
int H[200],PRE[200],INQ[200];
bool Bfs()
{
	for(int i=0;i<N*2+2;i++)H[i]=INF,PRE[i]=-1,INQ[i]=false;
	queue<int>q;
	q.push(N*2);INQ[N*2]=true;
	H[N*2]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			if(e.flow==e.limit)continue;
			int h=H[u]+e.w;
			if(h<H[e.b])
			{
				H[e.b]=h,PRE[e.b]=AD[u][i];
				if(!INQ[e.b])
				{
					q.push(e.b);
					INQ[e.b]=true;
				}
			}
		}
	}
	return PRE[N*2+1]!=-1;
}
int Solve()
{
	int ans=0,cnt=0;
	while(1)
	{
		if(!Bfs())break;
		cnt++;
		for(int u=N*2+1;u!=N*2;u=EDGE[PRE[u]].a)
		{
			EDGE[PRE[u]].flow++;
			EDGE[PRE[u]^1].flow--;
			ans+=EDGE[PRE[u]].w;
		}
//		printf("ans=%d\n",ans);
	}
	if(cnt!=N)return -1;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N*2+2;i++)AD[i].clear();
		EDGE.clear();
		for(int i=0;i<N;i++)
		{
			static int a,w;
			while(scanf("%d",&a)==1&&a)
			{
				scanf("%d",&w);
				a--;
				AddEdge(i,a+N,w);
			}
		}
		for(int i=0;i<N;i++)
		{
			AddEdge(N*2,i,0);
			AddEdge(i+N,N*2+1,0);
		}
		int ans=Solve();
		if(ans==-1)puts("N");
		else printf("%d\n",ans);
	}
	return 0;
}
