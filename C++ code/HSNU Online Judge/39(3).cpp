#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int K,M;
struct Node2D
{
	Node2D *l,*r;
	LL sz;
	int y;
	Node2D(int y,LL sz):l(NULL),r(NULL),y(y),sz(sz){}
};
struct Node1D
{
	Node1D *l,*r;
	Node2D *ch;
	Node1D():l(NULL),r(NULL),ch(NULL){}
}*ROOT;
int X,Y,X1,X2,Y1,Y2;
LL V;
LL Query2D(Node2D* &o,int l,int r)
{
	if(!o||l>Y2||r<Y1)return 0LL;
	if(o->y!=-1)return Y1<=o->y&&o->y<=Y2?o->sz:0LL;
	if(Y1<=l&&r<=Y2)return o->sz;
	int mid=l+(r-l)/2;
	return Query2D(o->l,l,mid)+Query2D(o->r,mid+1,r);
}
LL Query1D(Node1D* &o,int l,int r)
{
	if(!o||l>X2||r<X1)return 0LL;
	if(X1<=l&&r<=X2)return Query2D(o->ch,1,M);
	int mid=l+(r-l)/2;
	return Query1D(o->l,l,mid)+Query1D(o->r,mid+1,r);
}
LL Sz(Node2D* &o){return o?o->sz:0;}
void Maintain(Node2D* &o){o->sz=Sz(o->l)+Sz(o->r);}
void Add2D(Node2D* &o,int l,int r)
{
	if(!o){o=new Node2D(Y,V);return;}
	if(o->y!=-1)
	{
		if(o->y==Y){o->sz+=V;return;}
		int y=Y;
		LL v=V;
		Y=o->y,V=o->sz,o->y=-1;
		Add2D(o,l,r);
		Y=y,V=v;
	}
	int mid=l+(r-l)/2;
	if(Y<=mid)Add2D(o->l,l,mid);
	else Add2D(o->r,mid+1,r);
	Maintain(o);
}
void Add1D(Node1D* &o,int l,int r)
{
	if(!o)o=new Node1D();
	if(l<r)
	{
		int mid=l+(r-l)/2;
		if(X<=mid)Add1D(o->l,l,mid);
		else Add1D(o->r,mid+1,r);
	}
	Add2D(o->ch,1,M);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&M)==2)
	{
		ROOT=NULL;
		vector<int>va,vb;
		for(int i=0,a;i<K;i++){scanf("%d",&a);va.push_back(a);}
		for(int i=0,b;i<K;i++){scanf("%d",&b);vb.push_back(b);}
		LL ans=0LL;
		for(int i=0;i<K;i++)
		{
			//all k: A[k]>A[i]&&B[k]<B[i]
			//all k: A[k]<A[i]&&B[k]>B[i]
			X1=va[i]+1,X2=M,Y1=1,Y2=vb[i]-1;
//			puts("a");
			ans+=Query1D(ROOT,1,M);
//			puts("b");
			X1=1,X2=va[i]-1,Y1=vb[i]+1,Y2=M;
//			puts("c");
			ans+=Query1D(ROOT,1,M);
//			puts("d");
			X=va[i],Y=vb[i],V=1LL;
//			puts("e");
			Add1D(ROOT,1,M);
//			puts("f");
		}
		printf("%lld\n",ans);
	}
	return 0;
}
