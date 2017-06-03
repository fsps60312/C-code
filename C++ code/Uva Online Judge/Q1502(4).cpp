#include<cstdio>
//#include<cassert>
//#define bssert(x) assert(x)
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
void bssert(bool valid){if(valid)return;for(;;);putchar('E');}
void getmax(int &a,const int b){if(b>a)a=b;}
unsigned int myrand()
{
	static unsigned int seed=20151207;
	seed=seed*0xdefaced+105853;
	return seed+=(seed>>20);
}
struct MxSegTree
{
	vector<int>mx,tag;
	void Build(const int id,const int l,const int r)
	{
		while((int)mx.size()<=id)mx.push_back(0),tag.push_back(0);
		mx[id]=tag[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void PutDown(const int id)
	{
		getmax(tag[id*2],tag[id]),getmax(tag[id*2+1],tag[id]);
		getmax(mx[id*2],tag[id]),getmax(mx[id*2+1],tag[id]);
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(mx[id],v),getmax(tag[id],v);return;}
		PutDown(id);
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,v),Modify(id*2+1,mid+1,r,bl,br,v);
		mx[id]=max(mx[id*2],mx[id*2+1]);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r){bssert(loc==l);return mx[id];}
		PutDown(id);
		const int mid=(l+r)/2;
		if(loc<=mid)return Query(id*2,l,mid,loc);
		else return Query(id*2+1,mid+1,r,loc);
	}
}SEGTREE;
struct Treap
{
	struct Node
	{
		Node *ch[2];
		int v,mn,sz;
		unsigned int pri;
		Node(const int _v):ch{NULL,NULL},v(_v),mn(_v),sz(1),pri(myrand()){}
	}*root;
	int Mn(Node* &o)const{return o?o->mn:INF;}
	int Sz(Node* &o)const{return o?o->sz:0;}
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
	void Split(Node* &o,Node* &a,Node* &b,const int loc)
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
	void Build(vector<int>&data_base)
	{
		root=NULL;
		for(const auto v:data_base)root=Merge(root,new Node(v));
		bssert(root!=NULL);
	}
	int QueryLeft(Node* &o,const int bound)
	{
		bssert(o!=NULL&&"QueryLeft");
		if(o->mn>=bound)return 0;
		if(Mn(o->ch[1])<bound)return Sz(o->ch[0])+1+QueryLeft(o->ch[1],bound);
		else if(o->v<bound)return Sz(o->ch[0])+1;
		else return min(QueryLeft(o->ch[0],bound),Sz(o->ch[0]));
	}
	int QueryLeft(const int loc,const int bound)
	{
//		Check(root);
		Node *a,*b;
		Split(root,a,b,loc+1);
		int ans=QueryLeft(a,bound);
		root=Merge(a,b);
		return ans;
	}
	int QueryRight(Node* &o,const int bound)
	{
		bssert(o!=NULL&&"QueryRight");
		if(o->mn>=bound)return Sz(o)-1;
		if(Mn(o->ch[0])<bound)return QueryRight(o->ch[0],bound);
		else if(o->v<bound)return Sz(o->ch[0])-1;
		else return max(Sz(o->ch[0]),Sz(o->ch[0])+1+QueryRight(o->ch[1],bound));
	}
	int QueryRight(const int loc,const int bound)
	{
//		Check(root);
		if(loc+1==Sz(root))return loc;
		Node *a,*b;
		Split(root,a,b,loc+1);
		int ans=Sz(a)+QueryRight(b,bound);
		root=Merge(a,b);
		return ans;
	}
//	void Check(Node* &o)
//	{
//		if(!o)return;
//		assert(o->mn==min(Mn(o->ch[0]),min(o->v,Mn(o->ch[1]))));
//		assert(o->sz==Sz(o->ch[0])+1+Sz(o->ch[1]));
//		Check(o->ch[0]),Check(o->ch[1]);
//	}
};
struct StringMatcher
{
	int n;
	vector<int>sa,rank,height;
	void BuildSa(const vector<char>&str)
	{
		sa.resize(n);
		static vector<int>tmp[3];
		for(int i=0;i<3;i++)tmp[i].resize(max(n,256));
		int *x=&tmp[0][0],*y=&tmp[1][0],*c=&tmp[2][0];
		int p=256;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]=str[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
		for(int move=1;move<n;move<<=1)
		{
			int idx=0;
			for(int i=n-move;i<n;i++)y[idx++]=i;
			for(int i=0;i<n;i++)if(sa[i]>=move)y[idx++]=sa[i]-move;
			for(int i=0;i<p;i++)c[i]=0;
			for(int i=0;i<n;i++)c[x[i]]++;
			for(int i=1;i<p;i++)c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			p=0,x[sa[0]]=p++;
			for(int i=1;i<n;i++)
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
		for(int i=0;i<n;i++)rank[sa[i]]=i;
		for(int i=0,ans=0;i<n;i++)
		{
			if(ans)ans--;
			if(rank[i]==0){height[0]=0;continue;}
			const int j=sa[rank[i]-1];
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
	int QueryLeft(const int rank,const int n){return treap.QueryLeft(rank,n);}
	int QueryRight(const int rank,const int n){return treap.QueryRight(rank,n);}
}MATCHER;
int T,N,M;
vector<char>S;
vector<int>W,LOC;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	static char tmp[300100];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
	while(T--)
	{
		assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&N)==1);
		S.clear(),W.clear(),LOC.clear();
		for(int i=0;i<N;i++)
		{
			assert(fgets(tmp,INF,stdin));
			LOC.push_back(S.size());
			int n=0;
			for(;tmp[n]!=' ';n++)assert(tmp[n]>='a'&&tmp[n]<='z'),S.push_back(tmp[n]);
			S.push_back(' ');
			int w;
			assert(sscanf(tmp+n,"%d",&w)==1);
			W.push_back(w);
		}
		LOC.push_back(M=S.size());
		MATCHER.Build(S);
		SEGTREE.Build(1,0,M-1);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			const int n=LOC[i+1]-1-LOC[i];
			int result=-INF;
			for(int j=0;j<n;j++)
			{
				const int rank=MATCHER.rank[LOC[i]+j];
				getmax(result,SEGTREE.Query(1,0,M-1,rank));
			}
			result+=W[i];
			getmax(ans,result);
			const int rank=MATCHER.rank[LOC[i]];
			const int l=MATCHER.QueryLeft(rank,n)-1,r=MATCHER.QueryRight(rank,n);
			SEGTREE.Modify(1,0,M-1,l,r,result);
		}
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	return 0;
}
