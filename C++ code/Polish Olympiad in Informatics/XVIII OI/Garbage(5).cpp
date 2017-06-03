#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
int N,M;
multiset<int>ET[100000];
inline void AddEdge(const int a,const int b)
{
	ET[a].insert(b),ET[b].insert(a);
}
int PATH[2000000],PSZ;
void Dfs(const int u)
{
	multiset<int>&et=ET[u];
	while(!et.empty())
	{
		const int nxt=*et.begin();
		et.erase(et.begin());
		ET[nxt].erase(ET[nxt].find(u));
		Dfs(nxt);
	}
	PATH[++PSZ]=u;
}
int HEAD[1000000],CNT[1000000],HSZ,NEXT[2000000],VAL[2000000],NSZ;
bool Solve()
{
	for(int i=0;i<N;i++)if(ET[i].size()&1)return false;
	static bool vis[100000];
	for(int i=0;i<N;i++)vis[i]=false;
	HSZ=NSZ=-1;
	for(int u=0;u<N;u++)if(!ET[u].empty())
	{
		PSZ=-1;
		Dfs(u);
		static int stk[2000000];
		int ssz=-1;
		for(int i=0;i<=PSZ;i++)
		{
			stk[++ssz]=PATH[i];
			if(vis[PATH[i]])
			{
				++HSZ;
				HEAD[HSZ]=-1,CNT[HSZ]=0;
				while(vis[stk[ssz]])
				{
					vis[stk[ssz]]=false;
					++NSZ;
					VAL[NSZ]=stk[ssz];
					NEXT[NSZ]=HEAD[HSZ];
					HEAD[HSZ]=NSZ,++CNT[HSZ];
					--ssz;
				}
				++NSZ;
				VAL[NSZ]=stk[ssz];
				NEXT[NSZ]=HEAD[HSZ];
				HEAD[HSZ]=NSZ,++CNT[HSZ];
//				printf("CNT[%d]=%d\n",HSZ,CNT[HSZ]);
			}
			vis[PATH[i]]=true;
		}
	}
	return true;
}
char GetChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
int ReadInt()
{
	char c=GetChar();
	while(c<'0'||'9'<c)c=GetChar();
	int v=0;
	while('0'<=c&&c<='9')v=v*10+(c-'0'),c=GetChar();
	return v;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("smi7b.in","r",stdin);
//	freopen("new.txt","w",stdout);
	N=ReadInt(),M=ReadInt();
//	printf("N=%d,M=%d\n",N,M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b,f,t;i<M;i++)
	{
		a=ReadInt(),b=ReadInt(),f=ReadInt(),t=ReadInt(),a--,b--;
		if(t<=f)t+=2;
		for(int j=0;j<t-f;j++)AddEdge(a,b);
	}
	if(!Solve())puts("NIE");
	else
	{
		printf("%d\n",HSZ+1);
		for(int i=0;i<=HSZ;i++)
		{
			printf("%d",CNT[i]-1);
			for(int cur=HEAD[i];cur!=-1;cur=NEXT[cur])printf(" %d",VAL[cur]+1);
			puts("");
		}
	}
	return 0;
}
