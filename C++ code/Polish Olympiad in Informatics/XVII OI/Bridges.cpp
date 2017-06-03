#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Pipe
{
	int a,b,flow,limit;
	Pipe(){}
	Pipe(const int _a,const int _b,const int _flow,const int _limit):a(_a),b(_b),flow(_flow),limit(_limit){}
};
vector<int>EP[3002];
vector<Pipe>PIPE;
int LEVEL[3002],CUR[3002];
bool Bfs(const int n,const int source,const int target)
{
	for(int i=0;i<n;i++)LEVEL[i]=INF,CUR[i]=0;
	queue<int>q;
	q.push(source),LEVEL[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(int i=0;i<(int)EP[u].size();i++)
		{
			const Pipe &p=PIPE[EP[u][i]];
			if(p.flow<p.limit&&LEVEL[u]+1<LEVEL[p.b])
			{
				LEVEL[p.b]=LEVEL[u]+1;
				q.push(p.b);
			}
		}
	}
	return LEVEL[target]<INF;
}
int Dfs(const int u,const int target,const int supply)
{
	if(u==target||supply==0)return supply;
	int ans=0;
	for(int &i=CUR[u];ans<supply&&i<(int)EP[u].size();i++)
	{
		const int pi=EP[u][i];
		const Pipe &p=PIPE[pi];
		if(p.flow<p.limit&&LEVEL[p.a]+1==LEVEL[p.b])
		{
			const int flow=Dfs(p.b,target,min(supply-ans,p.limit));
			ans+=flow;
			PIPE[pi].flow+=flow;
			PIPE[pi^1].flow-=flow;
		}
	}
	return ans;
}
void DoFlow(const int n,const int source,const int target)
{
	while(Bfs(n,source,target))Dfs(source,target,INF);
}
void AddPipe(const int a,const int b,const int limit)
{
	const int i=(int)PIPE.size();
	PIPE.push_back(Pipe(a,b,0,limit));
	PIPE.push_back(Pipe(b,a,limit,limit));
	EP[a].push_back(i);
	EP[b].push_back(i+1);
}
struct Edge
{
	int a,b,l,p,direction;
	bool visited;
	Edge(){}
	Edge(const int _a,const int _b,const int _l,const int _p):a(_a),b(_b),l(_l),p(_p),visited(false){}
};
int N,M;
vector<int>ET[1000];
vector<Edge>EDGE;
bool Solve(const int max_cost)
{
//	printf("Solve(%d)\n",max_cost);
	for(int i=0;i<M+N+2;i++)EP[i].clear();
	PIPE.clear();
	static int flows[1000];
	for(int i=0;i<N;i++)flows[i]=0;
	for(int i=0;i<M;i++)
	{
		Edge &e=EDGE[i];
		if(e.l>max_cost&&e.p>max_cost)return false;
		else if(e.p>max_cost)
		{
			e.direction=1;
			++flows[e.b];
//			printf("%d to %d\n",e.a+1,e.b+1);
		}
		else if(e.l>max_cost)
		{
			e.direction=-1;
			++flows[e.a];
//			printf("%d to %d\n",e.b+1,e.a+1);
		}
		else
		{
			e.direction=0;
			AddPipe(M+N,i,1);
			AddPipe(i,M+e.a,1);
			AddPipe(i,M+e.b,1);
		}
	}
	for(int i=0;i<N;i++)
	{
		if((int)ET[i].size()%2==1)return false;
		const int need=(int)ET[i].size()/2;
		if(flows[i]>need)return false;
		if(flows[i]<need)AddPipe(M+i,M+N+1,need-flows[i]);//,printf("%d must flow %d\n",i+1,need-flows[i]);
	}
	DoFlow(M+N+2,M+N,M+N+1);
	for(int i=0;i<(int)EP[M+N].size();i++)
	{
		const Pipe p=PIPE[EP[M+N][i]];
		if(p.flow<p.limit)return false;
		assert((int)EP[p.b].size()==3);
		assert(PIPE[EP[p.b][1]].flow+PIPE[EP[p.b][2]].flow==1);
		if(PIPE[EP[p.b][1]].flow==1)EDGE[p.b].direction=-1;
		else EDGE[p.b].direction=1;
//		printf("edge %d(%d,%d) is to %d\n",p.b+1,EDGE[p.b].a+1,EDGE[p.b].b+1,EDGE[p.b].direction);
	}
	return true;
}
void Dfs(const int u,vector<int>&ans)
{
//	printf("u=%d\n",u+1);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		const Edge &e=EDGE[ei];
		assert(e.direction==1||e.direction==-1);
		const int nxt=(e.direction==1?e.b:e.a);
		if(nxt!=u&&!e.visited)
		{
			EDGE[ei].visited=true;
//			printf("(%d,%d)\n",u+1,nxt+1);
			Dfs(nxt,ans);
			ans.push_back(ei);
//			printf("ei=%d\n",ei+1);
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
		for(int i=0,a,b,l,p;i<M;i++)
		{
			scanf("%d%d%d%d",&a,&b,&l,&p),--a,--b;
			EDGE.push_back(Edge(a,b,l,p));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		int l=1,r=1000;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
		if(!Solve(r))puts("NIE");
		else
		{
			printf("%d\n",r);
			vector<int>ans;
			Dfs(0,ans);
			reverse(ans.begin(),ans.end());
			for(int i=0;i<(int)ans.size();i++)
			{
				if(i)putchar(' ');
				printf("%d",ans[i]+1);
			}
			puts("");
			assert((int)ans.size()==M);
		}
	}
	return 0;
}
