#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
template<class T>inline bool getmax(T &a,const T &b){if(a<b){a=b;return true;}return false;}
inline char GetChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
inline int GetInt()
{
	char c=GetChar();
	while(c<'0'||'9'<c)c=GetChar();
	int v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=GetChar();
	return v;
}
int HEAD[1000000],NEXT[1999998],FROM[1999998],ONTO[1999998],NSZ;
void AddEdge(const int a,const int b)
{
	FROM[NSZ]=a;
	ONTO[NSZ]=b;
	NEXT[NSZ]=HEAD[a];
	HEAD[a]=NSZ;
	++NSZ;
}
int N;
LL SZ[1999998],DP[1999998],COUNTER=0;
LL GetSZ(const int ei)
{
	LL &ans=SZ[ei];
	if(ans!=-1)return ans;
	++COUNTER;
	ans=1;
	const int u=ONTO[ei],parent=FROM[ei];
	for(int nxt_ei=HEAD[u];nxt_ei!=-1;nxt_ei=NEXT[nxt_ei])if(ONTO[nxt_ei]!=parent)ans+=GetSZ(nxt_ei);
	assert(ans!=-1);
	return ans;
}
LL GetDP(const int ei)
{
	LL &ans=DP[ei];
	if(ans!=-1)return ans;
	++COUNTER;
	ans=GetSZ(ei);
	const int u=ONTO[ei],parent=FROM[ei];
	for(int nxt_ei=HEAD[u];nxt_ei!=-1;nxt_ei=NEXT[nxt_ei])if(ONTO[nxt_ei]!=parent)ans+=GetDP(nxt_ei);
	assert(ans!=-1);
	return ans;
}
LL Solve(const int root)
{
	LL ans=0;
	for(int ei=HEAD[root];ei!=-1;ei=NEXT[ei])ans+=GetDP(ei),++COUNTER;
	return ans;
}
void DfsCheck(const int u,const int parent,bool *vis)
{
	assert(!vis[u]);
	vis[u]=true;
	for(int ei=HEAD[u];ei!=-1;ei=NEXT[ei])if(ONTO[ei]!=parent)DfsCheck(ONTO[ei],u,vis);
}
void CheckTree()
{
	static bool vis[1000000];
	for(int i=0;i<N;i++)vis[i]=false;
	DfsCheck(0,-1,vis);
	for(int i=0;i<N;i++)assert(vis[i]);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("sta8b.in","r",stdin);
	N=GetInt();
	for(int i=0;i<N;i++)HEAD[i]=-1;
	NSZ=0;
	for(int i=0,a,b;i<N-1;i++)
	{
		a=GetInt()-1,b=GetInt()-1;
		assert(0<=a&&a<N&&0<=b&&b<N);
		AddEdge(a,b),AddEdge(b,a);
	}
	assert(NSZ==(N-1)*2);
	CheckTree();
	for(int i=0;i<(N-1)*2;i++)SZ[i]=DP[i]=-1;
	LL reduced=-1;
	int ans=-1;
	for(int i=0;i<N;i++)if(getmax(reduced,Solve(i)))ans=i;
	assert(ans!=-1);
	printf("%d\n",ans+1);
	return 0;
}
