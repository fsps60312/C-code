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
int N,PARENT[1000000];
LL SZ[1000000],DP[1000000],RDP[1000000];
LL BuildSZ(const int u,const int parent)
{
	PARENT[u]=parent;
	LL &sz=SZ[u]=1;
	for(int i=HEAD[u];i!=-1;i=NEXT[i])if(ONTO[i]!=parent)sz+=BuildSZ(ONTO[i],u);
	return sz;
}
LL BuildDP(const int u,const int parent)
{
	LL &dp=DP[u]=SZ[u]-1;
	for(int i=HEAD[u];i!=-1;i=NEXT[i])if(ONTO[i]!=parent)dp+=BuildDP(ONTO[i],u);
	return dp;
}
LL GetRDP(const int u)
{
	LL &rdp=RDP[u];
	if(rdp!=-1)return rdp;
//	printf("u=%d\n",u+1);
	rdp=GetRDP(PARENT[u])+(N-SZ[u]);
	return rdp+=DP[PARENT[u]]-DP[u]-SZ[u];
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
	BuildSZ(0,-1),BuildDP(0,-1);
	for(int i=0;i<N;i++)RDP[i]=-1;
	RDP[0]=0;
	LL reduced=DP[0];
	int ans=0;
	for(int i=1;i<N;i++)
	{
		if(getmax(reduced,DP[i]+GetRDP(i)))ans=i;
//		printf("u=%d, val=%lld\n",i+1,DP[i]+GetRDP(i));
	}
	assert(ans!=-1);
	printf("%d\n",ans+1);
	return 0;
}
