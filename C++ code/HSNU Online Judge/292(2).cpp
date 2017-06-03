#include<cstdio>
#define LL long long
LL gcd(LL a,LL b)
{
	if(a==0)return b;
	if(b==0)return a;
	return gcd(b,a%b);
}
struct Node
{
	Node *cl,*cr,*cu,*cd;
	LL px,py,pv;
	Node()
	{
		px=-2;
		cl=cr=cu=cd=NULL;
	}
};
Node *root=NULL;
LL pv(Node *a){return a?a->pv:0;}
void update(Node* &n,LL x1,LL x2,LL y1,LL y2,LL x,LL y,LL v)
{
	if(!n)
	{
		n=new Node();
		n->px=x;
		n->py=y;
		n->pv=v;
		return;
	}
	else if(n->px!=-1)
	{
		if(n->px==x&&n->py==y)
		{
			n->pv=v;
			return;
		}
		LL nx=n->px,ny=n->py,nv=n->pv;
		n->px=-1;
		LL midx=(x1+x2)/2,midy=(y1+y2)/2;
		//n->pv=0;
		if(x1<x2)
		{
			if(nx<=midx)update(n->cl,x1,midx,y1,y2,nx,ny,nv);
			else update(n->cr,midx+1,x2,y1,y2,nx,ny,nv);
			//n->pv=gcd(n->pv,gcd(pv(n->cl),pv(n->cr)));
		}
		if(y1<y2)
		{
			if(ny<=midy)update(n->cu,x1,x2,y1,midy,nx,ny,nv);
			else update(n->cd,x1,x2,midy+1,y2,nx,ny,nv);
			//n->pv=gcd(n->pv,gcd(pv(n->cu),pv(n->cd)));
		}
	}
	LL midx=(x1+x2)/2,midy=(y1+y2)/2;
	if(x1<x2)
	{
		if(x<=midx)update(n->cl,x1,midx,y1,y2,x,y,v);
		else update(n->cr,midx+1,x2,y1,y2,x,y,v);
	}
	if(y1<y2)
	{
		if(y<=midy)update(n->cu,x1,x2,y1,midy,x,y,v);
		else update(n->cd,x1,x2,midy+1,y2,x,y,v);
	}
	n->pv=gcd(gcd(pv(n->cl),pv(n->cr)),gcd(pv(n->cu),pv(n->cd)));
}
bool inrange(LL v,LL l,LL r){return v>=l&&v<=r;}
LL query(Node *n,LL x1,LL x2,LL y1,LL y2,LL qx1,LL qx2,LL qy1,LL qy2)
{
	if(!n)return 0;
	if(x1>qx2||x2<qx1||y1>qy2||y2<qy1)return 0;
	if(x1>=qx1&&x2<=qx2&&y1>=qy1&&y2<=qy2)return n->pv;
	if(n->px!=-1)
	{
		if(inrange(n->px,qx1,qx2)&&inrange(n->py,qy1,qy2))return n->pv;
		else return 0;
	}
	LL midx=(x1+x2)/2,midy=(y1+y2)/2;
	LL ql=0,qr=0,qu=0,qd=0;
	if(x1>=qx1&&x2<=qx2)
	{
		qu=query(n->cu,x1,x2,y1,midy,qx1,qx2,qy1,qy2);
		qd=query(n->cd,x1,x2,midy+1,y2,qx1,qx2,qy1,qy2);
		return gcd(qu,qd);
	}
	if(y1>=qy1&&y2<=qy2)
	{
		ql=query(n->cl,x1,midx,y1,y2,qx1,qx2,qy1,qy2);
		qr=query(n->cr,midx+1,x2,y1,y2,qx1,qx2,qy1,qy2);
		return gcd(ql,qr);
	}
	ql=query(n->cl,x1,midx,y1,y2,qx1,qx2,qy1,qy2);
	qr=query(n->cr,midx+1,x2,y1,y2,qx1,qx2,qy1,qy2);
	qu=query(n->cu,x1,x2,y1,midy,qx1,qx2,qy1,qy2);
	qd=query(n->cd,x1,x2,midy+1,y2,qx1,qx2,qy1,qy2);
	return gcd(gcd(ql,qr),gcd(qu,qd));
}
LL R,C,N;
int main()
{
	//freopen("IN.txt","r",stdin);
	while(scanf("%lld%lld%lld",&R,&C,&N)==3)
	{
		root=NULL;
		for(LL i=0;i<N;i++)
		{
			LL t;
			scanf("%lld",&t);
			if(t==1)
			{
				LL p,q,k;scanf("%lld%lld%lld",&p,&q,&k);
				update(root,0,R,0,C,p,q,k);
			}
			else
			{
				LL p,q,u,v;scanf("%lld%lld%lld%lld",&p,&q,&u,&v);
				printf("%lld\n",query(root,0,R,0,C,p,u,q,v));
			}
		}
		return 0;
	}
	return 0;
}
