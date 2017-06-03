#include<cstdio>
#include<cassert>
using namespace std;
struct Node1D
{
	Node1D *ch[2];
	LL sum;
	bool covered;
	Node1D():ch{NULL,NULL},sum(0LL),covered(false){}
};
struct Node2D
{
	Node2D *ch[2];
	Node1D *ch1d;
	Node2D():ch{NULL,NULL},ch1d(new Node1D()){}
};
LL Modify1D(Node1D* &o,const int l,const int r,const int y1,const int y2,const LL &w,LL &ans)
{
	if(o->covered||r<y1||y2<l)return;
	if(y1<=l&&r<=y2)
	{
		ans+=w*((r-l+1LL)-(o->sum));
		o->sum=w*(r-l+1LL);
		o->covered=true;
		return;
	}
	assert(!o->covered);
	assert((o->ch[0]==NULL)==(o->ch[1]==NULL));
	assert((o->sum==0LL)==(o->ch[0]==NULL));
	if(o->sum==0LL)o->ch[0]=new Node1D(),o->ch[1]=new Node1D();
	const int mid=(l+r)/2;
	Modify1D(o->ch[0],l,mid,y1,y2,w,ans);
	Modify1D(o->ch[1],mid+1,r,y1,y2,w,ans);
}
void PutDown1D(Node1D *o,Node1D* &lo,Node1D* &ro,const int l,const int r,const int y1,const int y2)
{
	if(r<y1||y2<l)return;
	if(!lo)lo=new Node1D();
	if(!ro)ro=new Node1D();
	if(o->covered)
	{
		lo->sum=ro->sum=r-l+1LL;
		lo->covered=ro->covered=true;
		return;
	}
	
}
LL Sum(Node1D *o){return o?o->sum:0LL;}
Node *Ch(Node1D *o,const int d){return o?o->ch[d]:0LL;}
void Maintain1D(Node1D* &o,Node1D *lo,Node1D *ro,const int l,const int r,const int y1,const int y2)
{
	if(r<y1||y2<l)return;
	if(y1<=l&&r<=y2)
	o->sum=Sum(lo)+Sum(ro);
	if(lo->covered&&ro->covered)o->covered=true;
	if(o->covered)return;
	const int mid=(l+r)/2;
	Maintain1D(o->ch[0],Ch(lo,0),Ch(ro,0),l,mid,y1,y2);
	Maintain1D(o->ch[1],Ch(lo,1),Ch(ro,1),mid+1,r,y1,y2);
}
void Modify2D(Node2D* &o,const int l,const int r,const int x1,const int x2,const int y1,const int y2,LL &ans)
{
	if(r<x1||x2<l)return;
	if(x1<=l&&r<=x2){Modify1D(o->ch1d,0,1e9,y1,y2,ans);return;}
	if(!o->ch[0])o->ch[0]=new Node2D();
	if(!o->ch[1])o->ch[1]=new Node2D();
	PutDown1D(o->ch1d,o->ch[0]->ch1d,o->ch[1]->ch1d,0,1e9,y1,y2);
	const int mid=(l+r)/2;
	Modify2D(o->ch[0],l,mid,x1,x2,y1,y2,ans);
	Modify2D(o->ch[1],mid+1,r,x1,x2,y1,y2,ans);
	Maintain1D(o->ch1d,o->ch[0]->ch1d,o->ch[1]->ch1d,0,1e9,y1,y2);
}
int N;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,x1,y1,x2,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		}
	}
	return 0;
}
