#pragma GCC optimize("O3")
#include<cstdio>
//#include<cassert>
#include<algorithm>
using namespace std;
inline char GetChar()
{
	static char buf[(1<<20)+3],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,(1<<20)+3,stdin))==buf)return EOF;
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
int DATA[1000001+2],BN;
void Clear(const int _N){BN=_N;for(int i=1;i<=BN;i++)DATA[i]=0;}
inline void Add(int i){while(i<=BN)++DATA[i],i+=i&(-i);}
inline void Remove(int i){while(i<=BN)--DATA[i],i+=i&(-i);}
inline int Query(int i){int ans=0;while(i)ans+=DATA[i],i-=i&(-i);return ans;}
long long ANS;
int S[2000000+3],SSZ;
struct Node
{
	static Node POOL[2000000+3],*NEW;
	int v;
	int sz;
	Node *lch,*rch;
	Node(){}
	Node(const int _v):v(_v),sz(1),lch(NULL),rch(NULL){}
}Node::POOL[2000000+3],*Node::NEW=Node::POOL;
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
//	if(o->sz==1){S[++SSZ]=o->v;if(type==1)Add(o->v);return;}
	Node *&lch=o->lch,*&rch=o->rch;
	if(lch->sz>rch->sz)swap(lch,rch);
	const int l=SSZ;
	if(lch->sz==1)S[++SSZ]=lch->v;
	else Solve1(lch,-1);
	const int r=SSZ;
	if(rch->sz==1)Add(S[++SSZ]=rch->v);
	else Solve1(rch,1);
	long long ta=0LL;
	for(int i=l+1;i<=r;++i)ta+=Query(S[i]);
	ANS+=min(ta,((long long)(lch->sz)*(rch->sz))-ta);
	if(type==1)
	{
		for(int i=l+1;i<=r;++i)Add(S[i]);
	}
	else if(type==-1)
	{
		for(int i=r+1;i<=SSZ;++i)Remove(S[i]);
	}
}
int *Solve2(Node *o)
{
	int *s0=new int[o->sz];
	if(o->sz==1){s0[0]=o->v;return s0;}
	if(o->lch->sz>o->rch->sz)swap(o->lch,o->rch);
	const int lsz=o->lch->sz,rsz=o->rch->sz;
	int *s1=Solve2(o->lch),*s2=Solve2(o->rch);
	long long ta=0LL;
//	for(int i=0;i<lsz;++i)
//	{
//		ta+=(upper_bound(s2,s2+rsz,s1[i])-s2);
//	}
	for(int i=0,j=0,k=0;k<o->sz;++k)
	{
		if(j==rsz||(i<lsz&&s1[i]<s2[j]))s0[k]=s1[i],++i,ta+=j;
		else s0[k]=s2[j],++j;
	}
	ANS+=min(ta,((long long)(o->lch->sz)*(o->rch->sz))-ta);
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
	else ANS=0LL,Clear(N),SSZ=-1,Solve1(root,0);
	printf("%lld\n",ANS);
	return 0;
}


