#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,X,Y,V,X1,Y1,X2,Y2;
struct Node2D
{
	Node2D *ch[2];
	int sum,y;
	Node2D(const int &s,const int &_y):sum(s),y(_y),ch{NULL,NULL}{}
};
struct Node1D
{
	Node1D *ch[2];
	Node2D *n;
	Node1D():n(NULL),ch{NULL,NULL}{}
}*ROOT=NULL;
void Build(Node1D* &o,const int &l,const int &r)
{
	o=new Node1D();
	if(l==r)return;
	int mid=(l+r)/2;
	Build(o->ch[0],l,mid);
	Build(o->ch[1],mid+1,r);
}
const Node2D *GetCh(const Node2D* &o,const int &d){return o?o->ch[d]:NULL;}
const int GetSum(const Node2D* o){return o?o->sum:0;}
bool LEAF;
void Add2D(Node2D* &o,const int &l,const int &r,const Node2D *och0,const Node2D *och1)
{
	if(!o)
	{
		if(LEAF)o=new Node2D(V,Y);
		else o=new Node2D(GetSum(och0)+GetSum(och1),Y);
		return;
	}
	if(l==r)
	{
		if(LEAF)o->sum+=V;
		else o->sum=GetSum(och0)+GetSum(och1);
		return;
	}
	if(o->y!=-1)
	{
		if(o->y==Y){o->sum+=V;return;}
		int ty=Y,tv=V;
		Y=o->y,V=o->sum;
		o->y=-1;
		Add2D(o,l,r,och0,och1);
		Y=ty,V=tv;
	}
	int mid=(l+r)/2;
	if(Y<=mid)Add2D(o->ch[0],l,mid,GetCh(och0,0),GetCh(och1,0));
	else Add2D(o->ch[1],mid+1,r,GetCh(och0,1),GetCh(och1,1));
	o->sum=GetSum(o->ch[0])+GetSum(o->ch[1]);
}
void Add1D(Node1D* &o,const int &l,const int &r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		if(X<=mid)Add1D(o->ch[0],l,mid);
		else Add1D(o->ch[1],mid+1,r);
	}
	LEAF=(l==r);
	Add2D(o->n,0,N-1,LEAF?NULL:o->ch[0]->n,LEAF?NULL:o->ch[1]->n);
}
void Query2D(Node2D* &o,const int &l,const int &r,int &sum)
{
	if(!o||r<Y1||l>Y2)return;
	if(Y1<=l&&r<=Y2){sum+=o->sum;return;}
	if(o->y!=-1)
	{
		if(Y1<=o->y&&o->y<=Y2)sum+=o->sum;
		return;
	}
	int mid=(l+r)/2;
	Query2D(o->ch[0],l,mid,sum);
	Query2D(o->ch[1],mid+1,r,sum);
}
void Query1D(Node1D* &o,const int &l,const int &r,int &sum)
{
	if(r<X1||l>X2)return;
	if(X1<=l&&r<=X2){Query2D(o->n,0,N-1,sum);return;}
	int mid=(l+r)/2;
	Query1D(o->ch[0],l,mid,sum);
	Query1D(o->ch[1],mid+1,r,sum);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	Build(ROOT,0,N-1);
	int type;
	while(scanf("%d",&type)==1)
	{
		if(type==1)
		{
			scanf("%d%d%d",&X,&Y,&V);
			Add1D(ROOT,0,N-1);
		}
		else if(type==2)
		{
			int sum=0;
			scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
			Query1D(ROOT,0,N-1,sum);
			printf("%d\n",sum);
		}
		else assert(0);
	}
	return 0;
}
