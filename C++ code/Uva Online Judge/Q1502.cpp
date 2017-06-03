#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
inline unsigned int random()
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
		while(mx.size()<=id)mx.push_back(0),tag.push_back(0);
		mx[id]=tag[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void PutDown(const int id){getmax(mx[id*2],tag[id]),getmax(mx[id*2+1],tag[id]);}
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
		if(l==r){assert(loc==l);return mx[id];}
		PutDown(id);
		const int mid=(l+r)/2;
		if(loc<=mid)return Query(id*2,l,mid,loc);
		else return Query(id*2+1,mid+1,r,loc);
	}
}MXSEGTREE;
struct Treap
{
	struct Node
	{
		Node *ch[2];
		int v,mn,sz,pri;
		Node(const int _v):v(_v),mn(_v),sz(1),pri(random()),ch{NULL,NULL}{}
	}*root;
	int Mn(Node* &o){return o?o->mn:INF;}
	int Sz(Node* &o){return o?o->sz:0;}
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
	}
	int QueryLeft(const int loc)
	{
		
	}
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
				else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?p-1:p++);
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
	void Build(const vector<char>&str)
	{
		n=str.size();
		BuildSa(str),BuildHeight(str);
		BuildSparse();
	}
	vector<vector<int> >sparse;
	void BuildSparse()
	{
		sparse.resize(1),sparse[0].resize(n);
		for(int i=0;i<n;i++)sparse[0][i]=height[i];
		for(int d=1;(1<<d)<=n;d++)
		{
			sparse.push_back(vector<int>(n));
			for(int i=0;i+(1<<d)<=n;i++)sparse[d][i]=min(sparse[d-1][i],sparse[d-1][i+(1<<(d-1))]);
		}
	}
	int QuerySparse(const int l,const int r)
	{
		assert(l<=r);
		int d=0;
		while((1<<(d+1))<=r-l+1)d++;
		return min(sparse[d][l],sparse[d][r-(1<<d)+1]);
	}
	int Match(const int ra,const int rb)
	{
		assert(ra<rb);
		return QuerySparse(ra+1,rb);
	}
}MATCHER;
int T,N,M;
vector<char>S;
vector<int>W,LOC;
int main()
{
	freopen("in.txt","r",stdin);
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
			S.push_back('\0');
			for(;tmp[n]==' ';n++);
			assert(tmp[n]>='0'&&tmp[n]<='9');
			int w=0;
			for(;tmp[n]>='0'&&tmp[n]<='9';n++)w=w*10+(tmp[n]-'0');
			W.push_back(w);
		}
		LOC.push_back(S.size());
		MATCHER.Build(S);
		MXSEGTREE.Build(1,0,(M=(int)S.size())-1);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			getmax(ans,MXSEGTREE.Query(1,0,M-1,MATCHER.rank[LOC[i]]));
			const int n=LOC[i+1]-1-LOC[i];
			
		}
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	return 0;
}
