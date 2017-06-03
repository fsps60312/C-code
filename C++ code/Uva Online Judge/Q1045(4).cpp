#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=2147483647;
int N;
vector<int>AD[32];
struct Point
{
	int r,c;
	Point(){}
	Point(int r,int c):r(r),c(c){}
}P[30];
struct Edge
{
	int a,b,w,limit,flow;
	Edge(){}
	Edge(int a,int b,int w,int l,int f):a(a),b(b),w(w),limit(l),flow(f){}
};
vector<Edge>EDGE;
void AddEdge(int a,int b,int w,int l,int f)
{
	int sz=EDGE.size();
	EDGE.push_back(Edge(a,b,w,l,f));
	AD[a].push_back(sz);
}
void AddEdge(int a,int b,int w,int l)
{
	AddEdge(a,b,w,l,0);
	AddEdge(b,a,-w,l,l);
}
void BuildEdge()
{
	for(int i=0;i<N*2+2;i++)
	{
		AD[i].clear();
	}
	EDGE.clear();
	for(int i=0;i<N;i++)
	{
		AddEdge(N*2,i,0,1);
		AddEdge(N+i,N*2+1,0,1);
	}
	for(int i=0;i<N;i++)
	{
		for(int j=N;j<N*2;j++)
		{
			int w=abs(P[i].r-P[j].r)+abs(P[i].c-P[j].c);
			AddEdge(i,j,w,1);
		}
	}
}
#include<queue>
int H[32],PRE[32],INQ[32];
int Bfs()
{
	for(int i=0;i<N*2+2;i++)H[i]=INF,PRE[i]=-1,INQ[i]=false;
	queue<int>q;
	q.push(N*2);INQ[N*2]=true;
	H[N*2]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();INQ[u]=false;
//		if(u==N*2+1)continue;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=EDGE[AD[u][i]];
			if(e.flow==e.limit)continue;
			int h=H[u]+e.w;
			if(h<H[e.b])
			{
				H[e.b]=h;PRE[e.b]=AD[u][i];
				if(!INQ[e.b])q.push(e.b);
			}
		}
	}
//	printf("PRE[%d]=%d\n",N*2+1,PRE[N*2+1]);
	if(PRE[N*2+1]==-1)return -1;
	int flow=INF;
	for(int u=N*2+1;PRE[u]!=-1;u=EDGE[PRE[u]].a)
	{
		Edge &e=EDGE[PRE[u]];
//		printf(" %d(w%d)",u,e.w);
		flow=min(flow,e.limit-e.flow);
		e.flow++;
		EDGE[PRE[u]^1].flow--;
	}
//	puts("");
	return H[N*2+1];
}
int Solve()
{
	int ans=0;
	while(1)
	{
		int flow=Bfs();
//		printf("flow=%d\n",flow);
		if(flow==-1)break;
		ans+=flow;
	}
//	printf("ans=%d\n",ans);
//	while(1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			a--,b--;
			P[i]=Point(a,b);
		}
		int ans=INF;
		for(int t=0;t<N;t++)
		{
			for(int i=0;i<N;i++)P[N+i]=Point(t,i);
//			for(int i=0;i<N*2;i++)printf("(%d,%d)",P[i].r,P[i].c);puts("");
			BuildEdge();
			ans=min(ans,Solve());
		}
		for(int t=0;t<N;t++)
		{
			for(int i=0;i<N;i++)P[N+i]=Point(i,t);
			BuildEdge();
			ans=min(ans,Solve());
		}
		for(int i=0;i<N;i++)P[N+i]=Point(i,i);
		BuildEdge();
		ans=min(ans,Solve());
		for(int i=0;i<N;i++)P[N+i]=Point(N-1-i,i);
		BuildEdge();
		ans=min(ans,Solve());
		static int kase=0;
		kase++;
		printf("Board %d: %d moves required.\n\n",kase,ans);
	}
	return 0;
}
