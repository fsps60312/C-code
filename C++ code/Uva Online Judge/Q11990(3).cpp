#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,M,SEQ[200001],VAL[200001],ANS;
struct Bit
{
	int v[200001];
	void Clear(){for(int i=1;i<=N;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i)
	{
		while(i<=N)
		{
			v[i]++;
			i+=lowbit(i);
		}
	}
	int Query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=v[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BIT;
struct Node2D
{
	Node2D *l,*r;
	int sum;
	Node2D():l(NULL),r(NULL),sum(0){}
};
struct Node1D
{
	Node1D *l,*r;
	Node2D *ch;
	Node1D():l(NULL),r(NULL),ch(NULL){}
}*ROOT;
int X,Y,X1,X2,Y1,Y2;
int Query2D(Node2D* &o,int l,int r)
{
	if(!o||l>Y2||r<Y1)return 0;
	if(Y1<=l&&r<=Y2)return o->sum;
	int mid=(l+r)/2;
	return Query2D(o->l,l,mid)+Query2D(o->r,mid+1,r);
}
int Query1D(Node1D* &o,int l,int r)
{
	if(!o||l>X2||r<X1)return 0;
	if(X1<=l&&r<=X2)return Query2D(o->ch,1,N);
	int mid=(l+r)/2;
	return Query1D(o->l,l,mid)+Query1D(o->r,mid+1,r);
}
int Sum(Node2D* &o){return o?o->sum:0;}
void Maintain(Node2D* &o){o->sum=Sum(o->l)+Sum(o->r);if(!o->sum)o=NULL;}
Node2D *null=NULL;
Node2D* &L(Node2D* &o){return o?o->l:null;}
Node2D* &R(Node2D* &o){return o?o->r:null;}
void BuildLEAF(Node2D* &o,int l,int r)
{
	if(!o)o=new Node2D();
	if(l==r){o->sum=1;return;}
	int mid=(l+r)/2;
	if(SEQ[X]<=mid)BuildLEAF(o->l,l,mid);
	else BuildLEAF(o->r,mid+1,r);
	Maintain(o);
}
void Build2D(Node2D* &o,int l,int r,Node2D* &lch,Node2D* &rch)
{
	if(Sum(lch)+Sum(rch)==0){o=NULL;return;}
	if(!o)o=new Node2D();
	if(l==r){o->sum=Sum(lch)+Sum(rch);return;}
	int mid=(l+r)/2;
	Build2D(o->l,l,mid,L(lch),L(rch));
	Build2D(o->r,mid+1,r,R(lch),R(rch));
	Maintain(o);
}
void Build1D(Node1D* &o,int l,int r)
{
	if(!o)o=new Node1D();
	if(l<r)
	{
		int mid=(l+r)/2;
		Build1D(o->l,l,mid);
		Build1D(o->r,mid+1,r);
		assert(o->l&&o->r);
		Build2D(o->ch,1,N,o->l->ch,o->r->ch);
	}
	else
	{
		X=l;
		BuildLEAF(o->ch,1,N);
		assert(o->ch->sum==1);
	}
}
void Minus2D(Node2D* &o,int l,int r,Node2D* &lch,Node2D* &rch)
{
	if(Sum(lch)+Sum(rch)==0){o=NULL;return;}
	int mid=(l+r)/2;
	if(Y<=mid)Minus2D(o->l,l,mid,L(lch),L(rch));
	else Minus2D(o->r,mid+1,r,R(lch),R(rch));
	Maintain(o);
}
void Minus1D(Node1D* &o,int l,int r)
{
	if(l==r){o->ch=NULL;return;}
	int mid=(l+r)/2;
	if(X<=mid)Minus1D(o->l,l,mid);
	else Minus1D(o->r,mid+1,r);
	Minus2D(o->ch,1,N,o->l->ch,o->r->ch);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)
		{
			static int v;
			scanf("%d",&v);
			VAL[v]=i;
			SEQ[i]=v;
		}
		ANS=0;
		BIT.Clear();
		for(int i=1;i<=N;i++)
		{
			BIT.Add(SEQ[i]);
			ANS+=BIT.Query(N)-BIT.Query(SEQ[i]);
		}
		Build1D(ROOT=NULL,1,N);
		for(int i=1;i<=M;i++)
		{
			scanf("%d",&Y);
			X=VAL[Y];
			printf("%d\n",ANS);
			X1=1,X2=X-1,Y1=Y+1,Y2=N;
			ANS-=Query1D(ROOT,1,N);
			X1=X+1,X2=N,Y1=1,Y2=Y-1;
			ANS-=Query1D(ROOT,1,N);
			Minus1D(ROOT,1,N);
		}
	}
	return 0;
}
