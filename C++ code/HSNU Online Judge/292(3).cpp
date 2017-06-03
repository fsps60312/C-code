#include<cstdio>
#define LL long long
const LL gcd(const LL a,const LL b)
{
	if(a==0)return b;
	if(b==0)return a;
	return gcd(b,a%b);
}
struct Node2
{
	Node2 *cu,*cd;
	LL py,pv;
	Node2()
	{
		py=-1;
		cu=cd=NULL;
	}
};
struct Node1
{
	Node1 *cl,*cr;
	Node2 *cu,*cd;
	LL px,py,pv;
	Node1()
	{
		px=-1;
		cl=cr=NULL;
		cu=cd=NULL;
	}
};
Node1 *root=NULL;
const LL pv(const Node1 *a){return a?a->pv:0;}
const LL pv(const Node2 *a){return a?a->pv:0;}
void update2(Node2* &n,const LL y1,const LL y2,const LL y,const LL v)
{
	if(!n)
	{
		n=new Node2();
		n->py=y;
		n->pv=v;
		return;
	}
	else if(n->py!=-1)
	{
		if(n->py==y)
		{
			n->pv=v;
			return;
		}
		const LL ny=n->py,nv=n->pv;
		n->py=-1;
		const LL midy=(y1+y2)/2;
		//n->pv=0;
		if(ny<=midy)update2(n->cu,y1,midy,ny,nv);
		else update2(n->cd,midy+1,y2,ny,nv);
	}
	const LL midy=(y1+y2)/2;
	if(y<=midy)update2(n->cu,y1,midy,y,v);
	else update2(n->cd,midy+1,y2,y,v);
	n->pv=gcd(pv(n->cu),pv(n->cd));
}
LL R,C,N;
void update1(Node1* &n,const LL x1,const LL x2,const LL x,const LL y,const LL v)
{
	if(!n)
	{
		n=new Node1();
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
		const LL nx=n->px,ny=n->py,nv=n->pv;
		n->px=-1;
		if(x1<x2)
		{
			const LL midx=(x1+x2)/2;
			if(nx<=midx)update1(n->cl,x1,midx,nx,ny,nv);
			else update1(n->cr,midx+1,x2,nx,ny,nv);
		}
		const LL midy=(0+C)/2;
		if(ny<=midy)update2(n->cu,0,midy,ny,nv);
		else update2(n->cd,midy+1,C,ny,nv);
	}
	if(x1<x2)
	{
		const LL midx=(x1+x2)/2;
		if(x<=midx)update1(n->cl,x1,midx,x,y,v);
		else update1(n->cr,midx+1,x2,x,y,v);
	}
	const LL midy=(0+C)/2;
	if(y<=midy)update2(n->cu,0,midy,y,v);
	else update2(n->cd,midy+1,C,y,v);
}
const bool inrange(const LL v,const LL l,const LL r){return v>=l&&v<=r;}
const LL query2(const Node2* n,const LL y1,const LL y2,const LL qy1,const LL qy2)
{
	if(!n)return 0;
	if(y1>qy2||y2<qy1)return 0;
	if(n->py!=-1)
	{
		if(inrange(n->py,qy1,qy2))return n->pv;
		else return 0;
	}
	if(y1>=qy1&&y2<=qy2)return n->pv;
	const LL midy=(y1+y2)/2;
	const LL qu=query2(n->cu,y1,midy,qy1,qy2);
	const LL qd=query2(n->cd,midy+1,y2,qy1,qy2);
	return gcd(qu,qd);
}
const LL query1(const Node1* n,const LL x1,const LL x2,const LL qx1,const LL qx2,const LL qy1,const LL qy2)
{
	if(!n)return 0;
	if(x1>qx2||x2<qx1)return 0;
	if(n->px!=-1)
	{
		if(inrange(n->px,qx1,qx2)&&inrange(n->py,qy1,qy2))return n->pv;
		else return 0;
	}
	const LL midx=(x1+x2)/2,midy=(0+C)/2;
	if(x1>=qx1&&x2<=qx2)
	{
		const LL qu=query2(n->cu,0,midy,qy1,qy2);
		const LL qd=query2(n->cd,midy+1,C,qy1,qy2);
		return gcd(qu,qd);
	}
	const LL ql=query1(n->cl,x1,midx,qx1,qx2,qy1,qy2);
	const LL qr=query1(n->cr,midx+1,x2,qx1,qx2,qy1,qy2);
	return gcd(ql,qr);
}
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
				update1(root,0,R,p,q,k);
			}
			else
			{
				LL p,q,u,v;scanf("%lld%lld%lld%lld",&p,&q,&u,&v);
				printf("%lld\n",query1(root,0,R,p,u,q,v));
			}
		}
		//return 0;
	}
	return 0;
}
