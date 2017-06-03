#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
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
LL Sum(Node1D *o){return o?o->sum:0LL;}
void Maintain(Node1D *o){o->sum=Sum(o->ch[0])+Sum(o->ch[1]);}
void Modify1D(Node1D* &o,const LL &l,const LL &r,const LL &x1,const LL &x2,const LL &y1,const LL &y2,LL &ans)
{
//	printf("Modify1D(%lld,%lld,%lld,%lld)\n",x1,x2,y1,y2);
	if(r<y1||y2<l)return;
	if(y1<=l&&r<=y2)
	{
		ans+=(x2-x1+1LL)*(r-l+1LL)-(o->sum);
//		printf("(%lld,%lld)(%lld,%lld),%lld-%lld\n",x1,x2,y1,y2,(x2-x1+1LL)*(r-l+1LL),o->sum);
		o->sum=(x2-x1+1LL)*(r-l+1LL);
		o->covered=true;
		return;
	}
	const LL &mid=(l+r)/2LL;
	for(int d=0;d<2;d++)
	{
//		printf("(y1,y2)=(%lld,%lld)\n",x1,x2);
//		printf("%lld,%lld,%lld,%lld,%lld,%lld\n",l,r,x1,x2,y1,y2);
		assert(o->ch[d]);//has been PutDown
		const LL &chl=(d==0?l:mid+1LL),chr=(d==0?mid:r);
		if(o->covered)
		{
			o->ch[d]->covered=true;
			o->ch[d]->sum=(x2-x1+1LL)*(chr-chl+1LL);
		}
		Modify1D(o->ch[d],chl,chr,x1,x2,y1,y2,ans);
	}
	Maintain(o);
}
void PutDown1D(Node1D* &o,Node1D* &lo,Node1D* &ro,const LL &l,const LL &r,const LL &x1,const LL &x2,const LL &y1,const LL &y2)
{
	if(!lo)lo=new Node1D();
	if(!ro)ro=new Node1D();
	if(r<y1||y2<l)return;
	if(o->covered)
	{
		const LL &xmid=(x1+x2)/2LL;
		lo->sum=(xmid-x1+1LL)*(r-l+1LL);
		ro->sum=(x2-xmid)*(r-l+1LL);
		lo->covered=ro->covered=true;
	}
	if(y1<=l&&r<=y2)return;
	const LL &mid=(l+r)/2LL;
	for(int d=0;d<2;d++)
	{
		if(!o->ch[d])o->ch[d]=new Node1D();
		const LL &chl=(d==0?l:mid+1LL),chr=(d==0?mid:r);
		if(o->covered)
		{
			o->ch[d]->covered=true;
			o->ch[d]->sum=(x2-x1+1LL)*(chr-chl+1LL);
		}
		else
		{
			o->ch[d]->sum=Sum(lo->ch[d])+Sum(ro->ch[d]);
		}
		PutDown1D(o->ch[d],lo->ch[d],ro->ch[d],chl,chr,x1,x2,y1,y2);
	}
	assert(o->sum==Sum(o->ch[0])+Sum(o->ch[1]));
	Maintain(lo),Maintain(ro);
}
Node1D *Ch(Node1D *o,const int d){return o?o->ch[d]:0LL;}
void Maintain1D(Node1D* &o,Node1D *lo,Node1D *ro,const LL &l,const LL &r,const LL &y1,const LL &y2)
{
	if(r<y1||y2<l)return;
	assert(o);
	o->sum=Sum(lo)+Sum(ro);
	if(y1<=l&&r<=y2)return;
	const LL &mid=(l+r)/2LL;
	Maintain1D(o->ch[0],Ch(lo,0),Ch(ro,0),l,mid,y1,y2);
	Maintain1D(o->ch[1],Ch(lo,1),Ch(ro,1),mid+1,r,y1,y2);
}
void Modify2D(Node2D* &o,const LL &l,const LL &r,const LL &x1,const LL &x2,const LL &y1,const LL &y2,LL &ans)
{
//	printf("Modify2D(%lld,%lld,%lld,%lld)\n",x1,x2,y1,y2);
	assert(o);
	if(r<x1||x2<l)return;
	if(x1<=l&&r<=x2){Modify1D(o->ch1d,0,2e9,l,r,y1,y2,ans);return;}
	if(!o->ch[0])o->ch[0]=new Node2D();
	if(!o->ch[1])o->ch[1]=new Node2D();
	PutDown1D(o->ch1d,o->ch[0]->ch1d,o->ch[1]->ch1d,0,2e9,l,r,y1,y2);
	const LL &mid=(l+r)/2LL;
	Modify2D(o->ch[0],l,mid,x1,x2,y1,y2,ans);
	Modify2D(o->ch[1],mid+1LL,r,x1,x2,y1,y2,ans);
	Maintain1D(o->ch1d,o->ch[0]->ch1d,o->ch[1]->ch1d,0,2e9,y1,y2);
}
int N;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		LL ans=0LL;
		Node2D *root=new Node2D();
		for(int i=0,x1,y1,x2,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x1>x2)swap(x1,x2);
			if(y1>y2)swap(y1,y2);
			x1+=1e9,x2+=1e9,y1+=1e9,y2+=1e9;
			Modify2D(root,0,2e9,x1,x2,y1,y2,ans);
			printf("Insert(%d,%d,%d,%d), ans=%lld\n",x1,x2,y1,y2,ans);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
