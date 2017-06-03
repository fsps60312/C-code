#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
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
struct Bit
{
	int S[1000001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	inline void Add(int i,const int v){while(i<=N)S[i]+=v,i+=i&(-i);}
	inline int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=i&(-i);return ans;}
}BIT;
LL ANS;
int S[2000000],SSZ;
struct Node
{
	Node *lch,*rch;
	int v;
	int sz;
	Node():v(GetInt())
	{
		if(v){sz=1;return;}
		lch=new Node();
		rch=new Node();
		sz=lch->sz+rch->sz;
	}
	void Solve()
	{
		if(sz==1){BIT.Add(S[++SSZ]=v,1);return;}
		if(lch->sz>rch->sz)swap(lch,rch);
		const int l=SSZ+1;
		lch->Solve();
		const int r=SSZ;
		for(int i=l;i<=r;i++)BIT.Add(S[i],-1);
		rch->Solve();
		LL ta=0LL;
		for(int i=l;i<=r;i++)ta+=BIT.Query(S[i]);
		ANS+=min(ta,((LL)(lch->sz)*(rch->sz))-ta);
		for(int i=l;i<=r;i++)BIT.Add(S[i],1);
	}
};
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	N=GetInt();
	BIT.Clear(N);
	SSZ=-1;
	ANS=0LL;
	(new Node())->Solve();
	printf("%lld\n",ANS);
//	assert(SSZ+1==N);
	return 0;
}
