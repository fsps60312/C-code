#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int K,M,M1,M2;
struct Node2D
{
	Node2D *l,*r;
	LL sz;
	Node2D():l(NULL),r(NULL),sz(0LL){}
};
struct Node1D
{
	Node1D *l,*r;
	Node2D *ch;
	Node1D():l(NULL),r(NULL),ch(NULL){}
}*ROOT;
int X,Y,X1,X2,Y1,Y2;
LL Query2D(Node2D* &o,int l,int r)
{
	if(!o||l>Y2||r<Y1)return 0LL;
	if(Y1<=l&&r<=Y2)return o->sz;
	int mid=l+(r-l)/2;
	return Query2D(o->l,l,mid)+Query2D(o->r,mid+1,r);
}
LL Query1D(Node1D* &o,int l,int r)
{
	if(!o||l>X2||r<X1)return 0LL;
	if(X1<=l&&r<=X2)return Query2D(o->ch,1,M2);
	int mid=l+(r-l)/2;
	return Query1D(o->l,l,mid)+Query1D(o->r,mid+1,r);
}
LL Sz(Node2D* &o){return o?o->sz:0;}
void Maintain(Node2D* &o){o->sz=Sz(o->l)+Sz(o->r);}
void Add2D(Node2D* &o,int l,int r)
{
	if(!o)o=new Node2D();
	if(l==r){o->sz++;return;}
	int mid=l+(r-l)/2;
	if(Y<=mid)Add2D(o->l,l,mid);
	else Add2D(o->r,mid+1,r);
	Maintain(o);
}
void Add1D(Node1D* &o,int l,int r)
{
	if(!o)o=new Node1D();
	if(l==r){Add2D(o->ch,1,M2);return;}
	int mid=l+(r-l)/2;
	if(X<=mid)Add1D(o->l,l,mid);
	else Add1D(o->r,mid+1,r);
	Add2D(o->ch,1,M2);
}
//void AddLEAF(Node2D* &o,int l,int r)
//{
//	if(!o)o=new Node2D();
//	if(l==r){o->sz++;return;}
//	int mid=l+(r-l)/2;
//	if(Y<=mid)AddLEAF(o->l,l,mid);
//	else AddLEAF(o->r,mid+1,r);
//	Maintain(o);
//}
//Node2D *L(Node2D* &o){return o?o->l:NULL;}
//Node2D *R(Node2D* &o){return o?o->r:NULL;}
//void Add2D(Node2D* &o,int l,int r,Node2D *lch,Node2D *rch)
//{
//	if(!lch&&!rch)return;
//	if(!o)o=new Node2D();
//	if(l==r){o->sz=Sz(lch)+Sz(rch);return;}
//	int mid=l+(r-l)/2;
//	if(Y<=mid)Add2D(o->l,l,mid,L(lch),L(rch));
//	else Add2D(o->r,mid+1,r,R(lch),R(rch));
//	Maintain(o);
//}
//Node2D *Ch(Node1D* &o){return o?o->ch:NULL;}
//void Add1D(Node1D* &o,int l,int r)
//{
//	if(!o)o=new Node1D();
//	if(l==r){AddLEAF(o->ch,1,M2);return;}
//	int mid=l+(r-l)/2;
//	if(X<=mid)Add1D(o->l,l,mid);
//	else Add1D(o->r,mid+1,r);
//	Add2D(o->ch,1,M2,Ch(o->l),Ch(o->r));
//}
struct Data
{
	int i,v,r;
	Data(){}
	Data(int i,int r):i(i),r(r){}
};
bool Cmpi(const Data &a,const Data &b){return a.i<b.i;}
bool Cmpr(const Data &a,const Data &b){return a.r<b.r;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&M)==2)
	{
		M1=M2=M;
		ROOT=NULL;
		vector<Data>va,vb;
		for(int i=0,a;i<K;i++){scanf("%d",&a);va.push_back(Data(i,a));}
		for(int i=0,b;i<K;i++){scanf("%d",&b);vb.push_back(Data(i,b));}
//		for(int i=0;i<K;i++)printf("(%d,%d)\n",va[i].v,vb[i].v);puts("");
		sort(va.begin(),va.end(),Cmpr);
		sort(vb.begin(),vb.end(),Cmpr);
		M1=M2=2;
		va[0].v=vb[0].v=1;
		for(int i=1;i<K;i++)
		{
			va[i].v=(va[i].r==va[i-1].r?M1-1:M1++);
			vb[i].v=(vb[i].r==vb[i-1].r?M2-1:M2++);
		}
		M1--,M2--;
		sort(va.begin(),va.end(),Cmpi);
		sort(vb.begin(),vb.end(),Cmpi);
//		for(int i=0;i<K;i++)printf("(%d,%d)\n",va[i].v,vb[i].v);puts("");
		LL ans=0LL;
		for(int i=0;i<K;i++)
		{
			//all k: A[k]>A[i]&&B[k]<B[i]
			//all k: A[k]<A[i]&&B[k]>B[i]
			X1=va[i].v+1,X2=M1,Y1=1,Y2=vb[i].v-1;
			ans+=Query1D(ROOT,1,M1);
//			printf("a%d\n",ans);
			X1=1,X2=va[i].v-1,Y1=vb[i].v+1,Y2=M2;
			ans+=Query1D(ROOT,1,M1);
//			printf("b%d\n",ans);
			X=va[i].v,Y=vb[i].v;
			Add1D(ROOT,1,M1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
