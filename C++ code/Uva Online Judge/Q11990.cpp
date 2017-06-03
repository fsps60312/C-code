#include<cstdio>
int N,M,X,Y,X1,X2,Y1,Y2,V;
bool LEAF;
struct Node2D
{
	Node2D *l,*r;
	int sum;
	Node2D():l(NULL),r(NULL),sum(0){}
};
int Sum(Node2D* &o){return o?o->sum:0;}
Node2D *L(Node2D* &o){return o?o->l:NULL;}
Node2D *R(Node2D* &o){return o?o->r:NULL;}
void Pull(Node2D* &o){o->sum=Sum(o->l)+Sum(o->r);}
struct Node1D
{
	Node1D *l,*r;
	Node2D *ch;
	Node1D():l(NULL),r(NULL),ch(NULL){}
}*ROOT;
Node2D *Ch(Node1D* &o){return o?o->ch:NULL;}
int SEQ[200001],ANS;
void Add2D(Node2D* &o,int l,int r,Node2D *lch,Node2D *rch)
{
	if(!o)o=new Node2D();
	if(l==r)
	{
		if(LEAF){o->sum+=V;return;}
		o->sum=Sum(lch)+Sum(rch);
		return;
	}
	int mid=(l+r)/2;
	if(Y<=mid)Add2D(o->l,l,mid,L(lch),L(rch));
	else Add2D(o->r,mid+1,r,R(lch),R(rch));
	Pull(o);
}
void Add1D(Node1D* &o,int l,int r)
{
	if(!o)o=new Node1D();
	if(l==r)
	{
		LEAF=true;
		Add2D(o->ch,1,N,NULL,NULL);
	}
	else
	{
		int mid=(l+r)/2;
		if(X<=mid)Add1D(o->l,l,mid);
		else Add1D(o->r,mid+1,r);
		LEAF=false;
		Add2D(o->ch,1,N,Ch(o->l),Ch(o->r));
	}
}
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
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		ROOT=NULL;
		ANS=0,V=1;
		for(Y=1;Y<=N;Y++)
		{
			scanf("%d",&X);
			SEQ[X]=Y;
//			puts("adding");
			Add1D(ROOT,1,N);
//			puts("added");
			X1=X+1,X2=N,Y1=1,Y2=Y-1;
			ANS+=Query1D(ROOT,1,N);
			X1=1,X2=X-1,Y1=Y+1,Y2=N;
			ANS+=Query1D(ROOT,1,N);
		}
		V=-1;
		for(int i=0;i<M;i++)
		{
			printf("%d\n",ANS);
			scanf("%d",&X);
			Y=SEQ[X];
			X1=X+1,X2=N,Y1=1,Y2=Y-1;
			ANS-=Query1D(ROOT,1,N);
			X1=1,X2=X-1,Y1=Y+1,Y2=N;
			ANS-=Query1D(ROOT,1,N);
			Add1D(ROOT,1,N);
		}
	}
	return 0;
}
