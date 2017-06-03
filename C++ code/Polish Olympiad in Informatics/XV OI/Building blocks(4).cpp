#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct SegTree
{
	int SZ[4000000],N;
	void Build(const int id,const int l,const int r)
	{
		SZ[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N)
	{
		N=_N;
		Build(1,0,N);
	}
	void Add(const int id,const int l,const int r,const int loc,const int val)
	{
		SZ[id]+=val;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Add(id*2,l,mid,loc,val);
			else Add(id*2+1,mid+1,r,loc,val);
		}
	}
	void Add(const int loc,const int val)
	{
		Add(1,0,N,loc,val);
	}
	int Query(const int id,const int l,const int r,const int rank)
	{
		assert(1<=rank&&rank<=SZ[id]);
		if(l==r)return r;
		const int mid=(l+r)/2;
		if(rank<=SZ[id*2])return Query(id*2,l,mid,rank);
		else return Query(id*2+1,mid+1,r,rank-SZ[id*2]);
	}
	int Query(const int rank)
	{
		return Query(1,0,N,rank);
	}
}SEG;
struct Treap
{
	static Treap POOL[100000];
	Treap *l,*r;
	int loc,val,tag,sz;
	LL sum;
	unsigned int pri;
	Treap(){}
	Treap(const int _loc,const int _val):l(NULL),r(NULL),loc(_loc),val(_val),tag(0),sz(1),sum(_val),pri(Rand()){}
	unsigned int Rand()const
	{
		static unsigned int seed=20160620;
		(seed*=0xdefaced)+=114624;
		return seed+=seed>>20;
	}
}Treap::POOL[100000],*NEW_TREAP=Treap::POOL;
inline void AddTag(Treap* &o,const int val)
{
	if(!o)return;
	o->val+=val;
	o->tag+=val;
	o->sum+=(LL)o->sz*val;
}
inline LL Sum(Treap* &o){return o?o->sum:0LL;}
inline int Sz(Treap* &o){return o?o->sz:0;}
inline void PutDown(Treap* &o)
{
	if(o->tag)
	{
		AddTag(o->l,o->tag);
		AddTag(o->r,o->tag);
		o->tag=0;
	}
}
inline void Maintain(Treap* &o)
{
//	assert(!o->tag);
	o->sum=Sum(o->l)+(o->val)+Sum(o->r);
	o->sz=Sz(o->l)+1+Sz(o->r);
}
Treap *Merge(Treap *a,Treap *b)
{
	if(!a||!b)return a?a:b;
//	assert(a->loc<b->loc);
	if(a->pri>b->pri)
	{
		PutDown(a);
		a->r=Merge(a->r,b);
		Maintain(a);
		return a;
	}
	else
	{
		PutDown(b);
		b->l=Merge(a,b->l);
		Maintain(b);
		return b;
	}
}
void Split(Treap *o,Treap* &a,Treap* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	PutDown(o);
	if(loc<o->loc)
	{
		b=o;
		Split(b->l,a,b->l,loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(a->r,a->r,b,loc);
		Maintain(a);
	}
}
inline Treap *Extract(Treap* &o,const int loc)
{
	Treap *a,*b,*c;
	Split(o,a,b,loc-1);
	Split(b,b,c,loc);
	o=Merge(a,c);
	return b;
}
inline void Insert(Treap* &o,Treap *v)
{
	Treap *a,*b;
	Split(o,a,b,v->loc);
	o=Merge(Merge(a,v),b);
}
LL Query(Treap* &o,const int l,const int r)
{
	Treap *a,*b,*c;
	Split(o,a,b,l-1);
	Split(b,b,c,r);
	const LL ans=Sum(b);
	o=Merge(Merge(a,b),c);
	return ans;
}
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
	for(;c<'0'||'9'<c;c=GetChar());
	int ans=0;
	for(;'0'<=c&&c<='9';c=GetChar())ans=ans*10+(c-'0');
	return ans;
}
int N,K,H[100000];
int main()
{
	freopen("klo11c.in","r",stdin);
	freopen("out.txt","w",stdout);
	N=GetInt(),K=GetInt();
	for(int i=0;i<N;i++)H[i]=GetInt();
	multimap<int,int>queries;
	if(true)
	{
		SEG.Build(1000000);
		for(int i=0;i<N;i++)
		{
			SEG.Add(H[i],1);
			if(i-K>=0)SEG.Add(H[i-K],-1);
			if(i>=K-1)queries.insert(make_pair(SEG.Query(SEG.SZ[1]/2+1),i));
		}
	}
	multimap<int,int>sot;
	for(int i=0;i<N;i++)sot.insert(make_pair(H[i],i));
	Treap *upon=NULL,*down=NULL;
	if(true)
	{
		const int mn=sot.begin()->first;
		for(int i=0;i<N;i++)upon=Merge(upon,new (NEW_TREAP++)Treap(i,H[i]-mn));
	}
	LL ansc=INF;
	int ansv=0,ansi=-1;
	if(true)
	{
		int pre=sot.begin()->first;
		for(multimap<int,int>::iterator it=sot.begin(),iq=queries.begin();it!=sot.end()&&iq!=queries.end();pre=(it++)->first)
		{
			AddTag(upon,pre-(it->first));
			AddTag(down,(it->first)-pre);
			Insert(down,Extract(upon,it->second));
			for(;iq!=queries.end()&&iq->first==it->first;++iq)
			{
				const int l=(iq->second)-(K-1),r=(iq->second);
				const LL ta=Query(upon,l,r)+Query(down,l,r);
				if(ta<ansc)ansc=ta,ansv=it->first,ansi=l;
			}
		}
	}
	printf("%lld\n",ansc);
	for(int _i=0;_i<K;_i++)
	{
		const int i=ansi+_i;
		ansc-=abs(H[i]-ansv);
		H[i]=ansv;
	}
	for(int i=0;i<N;i++)printf("%d\n",H[i]);
	assert(ansc==0LL);
	return 0;
}
