#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
void bssert(bool valid){if(valid)return;for(int a=0,b=0;;)a/=b;}
void getmax(LL &a,const LL b){if(b>a)a=b;}
unsigned int myrand()
{
	static unsigned int seed=20151207;
	seed=seed*0xdefaced+105853;
	return seed+=(seed>>20);
}
struct MxSegTree
{
	vector<LL>mx,tag;
	void Build(const LL id,const LL l,const LL r)
	{
		while((LL)mx.size()<=id)mx.push_back(0),tag.push_back(0);
		mx[id]=tag[id]=0;
		if(l==r)return;
		const LL mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void PutDown(const LL id)
	{
		getmax(tag[id*2],tag[id]),getmax(tag[id*2+1],tag[id]);
		getmax(mx[id*2],tag[id]),getmax(mx[id*2+1],tag[id]);
	}
	void Modify(const LL id,const LL l,const LL r,const LL bl,const LL br,const LL v)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(mx[id],v),getmax(tag[id],v);return;}
		PutDown(id);
		const LL mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,v),Modify(id*2+1,mid+1,r,bl,br,v);
		mx[id]=max(mx[id*2],mx[id*2+1]);
	}
	LL Query(const LL id,const LL l,const LL r,const LL loc)
	{
		if(l==r){bssert(loc==l);return mx[id];}
		PutDown(id);
		const LL mid=(l+r)/2;
		if(loc<=mid)return Query(id*2,l,mid,loc);
		else return Query(id*2+1,mid+1,r,loc);
	}
}SEGTREE;
struct Treap
{
	struct Node
	{
		Node *ch[2];
		LL v,mn,sz;
		unsigned int pri;
		Node(const LL _v):ch{NULL,NULL},v(_v),mn(_v),sz(1),pri(myrand()){}
	}*root;
	LL Mn(Node* &o)const{return o?o->mn:INF;}
	LL Sz(Node* &o)const{return o?o->sz:0;}
	void Pull(Node* &o)
	{
		o->mn=min(Mn(o->ch[0]),min(o->v,Mn(o->ch[1])));
		o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	}
	Node *Merge(Node *a,Node *b)
	{
		if(!a||!b)return a?a:b;
		if(a->pri>b->pri)
		{
			a->ch[1]=Merge(a->ch[1],b);
			Pull(a);
			return a;
		}
		else
		{
			b->ch[0]=Merge(a,b->ch[0]);
			Pull(b);
			return b;
		} 
	}
	void Split(Node* &o,Node* &a,Node* &b,const LL loc)
	{
		if(!o){a=b=NULL;return;}
		if(loc<=Sz(o->ch[0]))
		{
			b=o;
			Split(b->ch[0],a,b->ch[0],loc);
			Pull(b);
		}
		else
		{
			a=o;
			Split(a->ch[1],a->ch[1],b,loc-(Sz(o->ch[0])+1));
			Pull(a);
		}
	}
	void Build(vector<LL>&data_base)
	{
		root=NULL;
		for(const auto v:data_base)root=Merge(root,new Node(v));
		bssert(root!=NULL);
	}
	LL QueryLeft(Node* &o,const LL bound)
	{
		bssert(o!=NULL&&"QueryLeft");
		if(o->mn>=bound)return 0;
		if(Mn(o->ch[1])<bound)return Sz(o->ch[0])+1+QueryLeft(o->ch[1],bound);
		else if(o->v<bound)return Sz(o->ch[0])+1;
		else return min(QueryLeft(o->ch[0],bound),Sz(o->ch[0]));
	}
	LL QueryLeft(const LL loc,const LL bound)
	{
		Node *a,*b;
		Split(root,a,b,loc+1);
		LL ans=QueryLeft(a,bound);
		root=Merge(a,b);
		return ans;
	}
	LL QueryRight(Node* &o,const LL bound)
	{
		bssert(o!=NULL&&"QueryRight");
		if(o->mn>=bound)return Sz(o)-1;
		if(Mn(o->ch[0])<bound)return QueryRight(o->ch[0],bound);
		else if(o->v<bound)return Sz(o->ch[0])-1;
		else return max(Sz(o->ch[0]),Sz(o->ch[0])+1+QueryRight(o->ch[1],bound));
	}
	LL QueryRight(const LL loc,const LL bound)
	{
		if(loc+1==Sz(root))return loc;
		Node *a,*b;
		Split(root,a,b,loc+1);
		LL ans=Sz(a)+QueryRight(b,bound);
		root=Merge(a,b);
		return ans;
	}
};
struct StringMatcher
{
	LL n;
	vector<LL>sa,rank,height;
	void BuildSa(const vector<char>&str)
	{
		sa.resize(n);
		static vector<LL>tmp[3];
		for(LL i=0;i<3;i++)tmp[i].resize(max(n,256LL));
		LL *x=&tmp[0][0],*y=&tmp[1][0],*c=&tmp[2][0];
		LL p=256;
		for(LL i=0;i<p;i++)c[i]=0;
		for(LL i=0;i<n;i++)c[x[i]=str[i]]++;
		for(LL i=1;i<p;i++)c[i]+=c[i-1];
		for(LL i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
		for(LL move=1;move<n;move<<=1)
		{
			LL idx=0;
			for(LL i=n-move;i<n;i++)y[idx++]=i;
			for(LL i=0;i<n;i++)if(sa[i]>=move)y[idx++]=sa[i]-move;
			for(LL i=0;i<p;i++)c[i]=0;
			for(LL i=0;i<n;i++)c[x[i]]++;
			for(LL i=1;i<p;i++)c[i]+=c[i-1];
			for(LL i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			p=0,x[sa[0]]=p++;
			for(LL i=1;i<n;i++)
			{
				if(y[sa[i]]!=y[sa[i-1]]||(sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=p++;
				else bssert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?p-1:p++);
			}
			if(p==n)break;
		}
	}
	void BuildHeight(const vector<char>&str)
	{
		rank.resize(n),height.resize(n);
		for(LL i=0;i<n;i++)rank[sa[i]]=i;
		for(LL i=0,ans=0;i<n;i++)
		{
			if(ans)ans--;
			if(rank[i]==0){height[0]=0;continue;}
			const LL j=sa[rank[i]-1];
			while(i+ans<n&&j+ans<n&&str[i+ans]==str[j+ans])ans++;
			height[rank[i]]=ans;
		}
	}
	Treap treap;
	void Build(const vector<char>&str)
	{
		n=str.size();
		BuildSa(str),BuildHeight(str);
		treap.Build(height);
	}
	LL QueryLeft(const LL rank,const LL n){return treap.QueryLeft(rank,n);}
	LL QueryRight(const LL rank,const LL n){return treap.QueryRight(rank,n);}
}MATCHER;
LL T,N,M;
vector<char>S;
vector<LL>W,LOC;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	assert(scanf("%lld",&T)==1);
	while(T--)
	{
		assert(scanf("%lld",&N)==1);
		S.clear(),W.clear(),LOC.clear();
		for(LL i=0;i<N;i++)
		{
			static char tmp[/*300100*/1048576];
			LL w;
			assert(scanf("%s%lld",tmp,&w)==2);
			W.push_back(w);
			LOC.push_back(S.size());
			LL n=0;
			for(;tmp[n];n++)/*assert(tmp[n]>='a'&&tmp[n]<='z'),*/S.push_back(tmp[n]);
			S.push_back(' ');
		}
		LOC.push_back(M=S.size());
		MATCHER.Build(S);
		SEGTREE.Build(1,0,M-1);
		LL ans=0;
		for(LL i=0;i<N;i++)
		{
			const LL n=LOC[i+1]-1-LOC[i];
			LL result=-INF;
			for(LL j=0;j<n;j++)
			{
				const LL rank=MATCHER.rank[LOC[i]+j];
				getmax(result,SEGTREE.Query(1,0,M-1,rank));
			}
			result+=W[i];
			getmax(ans,result);
			const LL rank=MATCHER.rank[LOC[i]];
			const LL l=MATCHER.QueryLeft(rank,n)-1,r=MATCHER.QueryRight(rank,n);
			SEGTREE.Modify(1,0,M-1,l,r,result);
		}
		static LL kase=1;
		printf("Case #%lld: %lld\n",kase++,ans);
	}
	return 0;
}
