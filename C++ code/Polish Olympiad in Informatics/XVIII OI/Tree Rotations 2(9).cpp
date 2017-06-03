#pragma optimize("O3")
#include<cstdio>
#include<cstring>
//#include<cassert>
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
	void Clear(const int _N){N=_N;memset(S,0,sizeof(S));}
	inline void Add(int i){while(i<=N)++S[i],i+=i&(-i);}
	inline void Remove(int i){while(i<=N)--S[i],i+=i&(-i);}
	inline int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=i&(-i);return ans;}
}BIT;
LL ANS;
int S[2000000],SSZ;
struct Node
{
	static Node POOL[2000000],*NEW;
	int v;
	LL sz;
	Node *lch,*rch;
	Node(){}
	Node(const int _v):v(_v),sz(1LL),lch(NULL),rch(NULL){}
}Node::POOL[2000000],*Node::NEW=Node::POOL;
Node *Build()
{
	const int v=GetInt();
	Node *o=new (Node::NEW++)Node(v);
	if(!v)
	{
		o->lch=Build();
		o->rch=Build();
		o->sz=o->lch->sz+o->rch->sz;
	}
	ANS+=o->sz;
	return o;
}
void Solve1(Node *o,int type)
{
	if(o->sz==1){S[++SSZ]=o->v;if(type==1)BIT.Add(o->v);return;}
	if(o->lch->sz>o->rch->sz)swap(o->lch,o->rch);
	const int l=SSZ;
	Solve1(o->lch,-1);
	const int r=SSZ;
	Solve1(o->rch,1);
	LL ta=0LL;
	for(int i=l+1;i<=r;++i)ta+=BIT.Query(S[i]);
	ANS+=min(ta,((o->lch->sz)*(o->rch->sz))-ta);
	if(type==1)
	{
		for(int i=l+1;i<=r;++i)BIT.Add(S[i]);
	}
	else if(type==-1)
	{
		for(int i=r+1;i<=SSZ;++i)BIT.Remove(S[i]);
	}
}
int *Solve2(Node *o)
{
	int *s0=new int[o->sz];
	if(o->sz==1){s0[0]=o->v;return s0;}
	if(o->lch->sz>o->rch->sz)swap(o->lch,o->rch);
	const int lsz=o->lch->sz,rsz=o->rch->sz;
	int *s1=Solve2(o->lch),*s2=Solve2(o->rch);
	LL ta=0LL;
	for(int i=0;i<lsz;++i)ta+=(upper_bound(s2,s2+rsz,s1[i])-s2);
	ANS+=min(ta,((o->lch->sz)*(o->rch->sz))-ta);
	for(int i=0,j=0,k=0;k<o->sz;k++)
	{
		if(j==rsz||(i<lsz&&s1[i]<s2[j]))s0[k]=s1[i],++i;
		else s0[k]=s2[j],++j;
	}
	delete[]s1;delete[]s2;
	return s0;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	N=GetInt();
	ANS=0LL;
	Node *root=Build();
	if(ANS<=200*N)ANS=0LL,Solve2(root);//,puts("a");
	else ANS=0LL,BIT.Clear(N),SSZ=-1,Solve1(root,0);
	printf("%lld\n",ANS);
	return 0;
}
