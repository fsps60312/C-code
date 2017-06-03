#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Node
{
	Node *ch[2];
	int val,sz;
	Node(const int _val):val(_val),sz(1){ch[0]=ch[1]=NULL;}
};
inline int Sz(Node* &o){return o?o->sz:0;}
inline void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
}
inline void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
inline void Rotate(Node* &o)
{
		 if(Sz(o->ch[0])-Sz(o->ch[1])>2)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>2)Rotate(o,1);
}
void Insert(Node* &o,const int val)
{
	if(!o){o=new Node(val);return;}
	Insert(o->ch[val<o->val?0:1],val);
	Maintain(o);
	Rotate(o);
}
void Delete(Node* &o)
{
	assert(o);
	if(o->ch[0]&&o->ch[1])
	{
		const int cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
		Rotate(o,cu);
		Delete(o->ch[cu^1]);
		Maintain(o);
	}
	else o=o->ch[o->ch[0]?0:1];
}
void Erase(Node* &o,const int val)
{
	assert(o);
	if(o->val==val){Delete(o);return;}
	Erase(o->ch[val<o->val?0:1],val);
	Maintain(o);
	Rotate(o);
}
int Query(Node* &o,const int loc)
{
	assert(o);
	if(loc<Sz(o->ch[0]))return Query(o->ch[0],loc);
	else if(loc==Sz(o->ch[0]))return o->val;
	else return Query(o->ch[1],loc-Sz(o->ch[0])-1);
}
struct Treap
{
	Treap *l,*r;
	int loc,val,tag,sz;
	LL sum;
	unsigned int pri;
	Treap(const int _loc,const int _val):l(NULL),r(NULL),loc(_loc),val(_val),tag(0),sz(1),sum(_val),pri(Rand()){}
	unsigned int Rand()const
	{
		static unsigned int seed=20160620;
		(seed*=0xdefaced)+=114624;
		return seed+=seed>>20;
	}
};
inline void AddTag(Treap* &o,const int val)
{
	if(!o)return;
	o->val+=val;
	o->tag+=val;
	o->sum+=(LL)o->sz*val;
}
LL Sum(Treap* &o){return o?o->sum:0LL;}
int Sz(Treap* &o){return o?o->sz:0;}
void PutDown(Treap* &o)
{
	if(o->tag)
	{
		AddTag(o->l,o->tag);
		AddTag(o->r,o->tag);
		o->tag=0;
	}
}
void Maintain(Treap* &o)
{
	assert(!o->tag);
	o->sum=Sum(o->l)+(o->val)+Sum(o->r);
	o->sz=Sz(o->l)+1+Sz(o->r);
}
Treap *Merge(Treap *a,Treap *b)
{
	if(!a||!b)return a?a:b;
	assert(a->loc<b->loc);
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
Treap *Extract(Treap* &o,const int loc)
{
	Treap *a,*b,*c;
	Split(o,a,b,loc-1);
	Split(b,b,c,loc);
	o=Merge(a,c);
	return b;
}
void Insert(Treap* &o,Treap *v)
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
int N,K,H[100000];
int main()
{
	freopen("klo11c.in","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		multimap<int,int>queries;
		if(true)
		{
			Node *root=NULL;
			for(int i=0;i<N;i++)
			{
				Insert(root,H[i]);
				if(i-K>=0)Erase(root,H[i-K]);
				if(i>=K-1)queries.insert(make_pair(Query(root,Sz(root)/2),i));
			}
		}
		multimap<int,int>sot;
		for(int i=0;i<N;i++)sot.insert(make_pair(H[i],i));
		Treap *upon=NULL,*down=NULL;
		if(true)
		{
			const int mn=sot.begin()->first;
			for(int i=0;i<N;i++)upon=Merge(upon,new Treap(i,H[i]-mn));
		}
		LL ansc=INF;
		int ansv=0,ansi=-1;
		if(true)
		{
			int pre=sot.begin()->first;
			for(multimap<int,int>::iterator it=sot.begin(),iq=queries.begin();it!=sot.end();pre=(it++)->first)
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
	}
	return 0;
}
