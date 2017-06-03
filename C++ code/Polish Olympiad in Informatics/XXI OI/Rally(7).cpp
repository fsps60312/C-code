#include<cstdio>
#include<cassert>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
inline void getmax(int &a,const int b){if(a<b)a=b;}
struct Edge
{
	int a,b,cost;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
Edge EDGE[2000000];
int ESZ;
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
void Bfs(const int *head,const int *next,const int *val,int *dist)
{
	static int degree[500002];
	for(int i=0;i<N+2;i++)degree[i]=0;
	for(int i=0;i<N+2;i++)for(int cur=head[i];cur!=-1;cur=next[cur])
	{
		const Edge &e=EDGE[val[cur]];
		const int nxt=(i==e.a?e.b:e.a);
		++degree[nxt];
	}
	queue<int>q;
	for(int i=0;i<N+2;i++)if(degree[i]==0)dist[i]=0,q.push(i);
	assert((int)q.size()==1);
	int ccr=0;
	while(!q.empty())
	{
		const int u=ORDER[ccr++]=q.front();q.pop();
		assert(degree[u]==0);
		for(int cur=head[u];cur!=-1;cur=next[cur])
		{
			const Edge &e=EDGE[val[cur]];
			const int nxt=(u==e.a?e.b:e.a);
			dist[nxt]=dist[u]+1;
			if(!--degree[nxt])q.push(nxt);
		}
	}
	assert(ccr==N+2);
}
int HT[500002],HF[500002],NEXT[(1000000+500000*2)*2],VAL[(1000000+500000*2)*2],NSZ;
inline void AddEdge(const int a,const int b)
{
	NEXT[NSZ]=HT[a];
	VAL[NSZ]=ESZ;
	HT[a]=NSZ++;
	NEXT[NSZ]=HF[b];
	VAL[NSZ]=ESZ;
	HF[b]=NSZ++;
	EDGE[ESZ++]=Edge(a,b);
}
int DT[500002],DF[500002];
int main()
{
//	freopen("in.txt","r",stdin);
	N=ReadInt(),M=ReadInt();
	NSZ=0;
	for(int i=0;i<N+2;i++)HT[i]=HF[i]=-1;
	ESZ=0;
	for(int i=0,a,b;i<M;i++)
	{
		a=ReadInt(),b=ReadInt();
		AddEdge(--a,--b);
	}
	for(int i=0;i<N;i++)AddEdge(N,i),AddEdge(i,N+1);
	Bfs(HF,NEXT,VAL,DT),Bfs(HT,NEXT,VAL,DF);
	for(int i=0;i<ESZ;i++)
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
	for(int _u=0;_u<N+1;_u++)
	{
		const int u=ORDER[_u];
		for(int cur=HF[u];cur!=-1;cur=NEXT[cur])midedges.Erase(EDGE[VAL[cur]].cost);
		if(u<N)
		{
			const int ta=max(midedges.Top(),max(uppoints,downpoints[_u+1]));
			if(ta<ans_dist)ans_dist=ta,ans_u=u;
		}
		for(int cur=HT[u];cur!=-1;cur=NEXT[cur])midedges.Push(EDGE[VAL[cur]].cost);
		getmax(uppoints,DF[u]);
	}
	printf("%d %d\n",ans_u+1,ans_dist-1);
//	assert(midedges.S.empty());
	return 0;
}
