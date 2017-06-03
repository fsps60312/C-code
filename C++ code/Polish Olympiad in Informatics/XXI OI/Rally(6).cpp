#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(a<b)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
struct PriorityQueue
{
	priority_queue<int>S;
	int DEL[500003];
	void Clear(const int n)
	{
		while(!S.empty())S.pop();
		for(int i=0;i<n;i++)DEL[i]=0;
	}
	inline void Push(const int v){S.push(v);}
	inline int Top()const{return S.empty()?0:S.top();}
	inline void Erase(const int v)
	{
		++DEL[v];
		while(!S.empty()&&DEL[S.top()])--DEL[S.top()],S.pop();
	}
};
inline char ReadChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
inline int ReadInt()
{
	char c=ReadChar();
	while(c<'0'||'9'<c)c=ReadChar();
	int v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=ReadChar();
	return v;
}
int N,M,ORDER[500002];
void Bfs(const vector<int>*es,int *dist)
{
	static int degree[500002];
	for(int i=0;i<N+2;i++)degree[i]=0;
	for(int i=0;i<N+2;i++)for(int j=0;j<(int)es[i].size();j++)
	{
		const Edge &e=EDGE[es[i][j]];
		const int nxt=(i==e.a?e.b:e.a);
		++degree[nxt];
	}
	queue<int>q;
	for(int i=0;i<N+2;i++)if(degree[i]==0)dist[i]=0,q.push(i);
	assert((int)q.size()==1);
	int cur=0;
	while(!q.empty())
	{
		const int u=ORDER[cur++]=q.front();q.pop();
		assert(degree[u]==0);
		for(int i=0;i<(int)es[u].size();i++)
		{
			const Edge &e=EDGE[es[u][i]];
			const int nxt=(u==e.a?e.b:e.a);
			dist[nxt]=dist[u]+1;
			if(!--degree[nxt])q.push(nxt);
		}
	}
	assert(cur==N+2);
}
vector<int>ET[500002],EF[500002];
void AddEdge(const int a,const int b)
{
	const int sz=(int)EDGE.size();
	EDGE.push_back(Edge(a,b));
	ET[a].push_back(sz),EF[b].push_back(sz);
}
int DT[500002],DF[500002];
int main()
{
//	freopen("in.txt","r",stdin);
	N=ReadInt(),M=ReadInt();
	for(int i=0;i<N+2;i++)ET[i].clear(),EF[i].clear();
	EDGE.clear();
	for(int i=0,a,b;i<M;i++)
	{
		a=ReadInt(),b=ReadInt();
		AddEdge(--a,--b);
	}
	for(int i=0;i<N;i++)AddEdge(N,i),AddEdge(i,N+1);
	Bfs(EF,DT),Bfs(ET,DF);
	for(int i=0;i<(int)EDGE.size();i++)
	{
		Edge &e=EDGE[i];
		e.cost=DF[e.a]+DT[e.b];
	}
	int uppoints=0;
	static PriorityQueue midedges;
	midedges.Clear(N+2+1);
	static int downpoints[500003];
	downpoints[N+2]=0;
	for(int i=N+1;i>=0;i--)downpoints[i]=max(downpoints[i+1],DT[ORDER[i]]);
	int ans_dist=INF,ans_u=-1;
	for(int _u=0;_u<N+2;_u++)
	{
		const int u=ORDER[_u];
		for(int i=0;i<(int)EF[u].size();i++)midedges.Erase(EDGE[EF[u][i]].cost);
		if(u<N)
		{
			const int ta=max(midedges.Top(),max(uppoints,downpoints[_u+1]));
			if(ta<ans_dist)ans_dist=ta,ans_u=u;
		}
		for(int i=0;i<(int)ET[u].size();i++)midedges.Push(EDGE[ET[u][i]].cost);
		getmax(uppoints,DF[u]);
	}
	printf("%d %d\n",ans_u+1,ans_dist-1);
	assert(midedges.S.empty());
	return 0;
}
