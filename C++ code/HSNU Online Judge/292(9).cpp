#include<cstdio>
#define LL long long
const bool inrange(const LL v,const LL l,const LL r){return v>=l&&v<=r;}
const LL cal_gcd(const LL a,const LL b){return b==0?a:cal_gcd(b,a%b);}
const LL gcd(const LL a,const LL b)
{
	if(!a||!b)return a?a:b;
	return cal_gcd(a,b);
}
struct Node2
{
	Node2 *cu,*cd;
	LL py,pv;
	Node2(LL y,LL v):py(y),pv(v)
	{
		cu=cd=NULL;
	}
};
struct Node1
{
	Node1 *cl,*cr;
	Node2 *cud;
	Node1()
	{
		cl=cr=NULL;
		cud=NULL;
	}
};
Node1 *root=NULL;
LL R,C,N;
const LL pv(const Node2 *a){return a?a->pv:0;}
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
const LL min(const LL a,const LL b){return a<b?a:b;}
const LL max(const LL a,const LL b){return a>b?a:b;}
const LL query1(const Node1* n,const LL x1,const LL x2,const LL qx1,const LL qx2,const LL qy1,const LL qy2)
{
	if(!n)return 0;
	if(x1>qx2||x2<qx1)return 0;
	if(x1>=qx1&&x2<=qx2)return query2(n->cud,0,C,qy1,qy2);
	const LL midx=(x1+x2)/2;
	const LL ql=query1(n->cl,x1,midx,qx1,qx2,qy1,qy2);
	const LL qr=query1(n->cr,midx+1,x2,qx1,qx2,qy1,qy2);
	return gcd(ql,qr);
}
LL update2(Node2* &n,const LL y1,const LL y2,const LL y,const LL v)
{
	if(!n)
	{
		n=new Node2(y,v);
		return v;
	}
	if(n->py!=-1)
	{
		if(n->py==y)
		{
			n->pv=v;
			return v;
		}
		const LL ny=n->py,nv=n->pv;
		n->py=-1;
		update2(n,y1,y2,ny,nv);
	}
	const LL midy=(y1+y2)/2;
	if(y<=midy)update2(n->cu,y1,midy,y,v);
	else update2(n->cd,midy+1,y2,y,v);
	n->pv=gcd(pv(n->cu),pv(n->cd));
	return v;
}
LL update1(Node1* &n,const LL x1,const LL x2,const LL x,const LL y,const LL v)
{
	if(!n)
	{
		n=new Node1();
	}
	LL ans=v;
	if(x1<x2)
	{
		const LL midx=(x1+x2)/2;
		if(x<=midx)ans=gcd(update1(n->cl,x1,midx,x,y,v),query1(n->cr,midx+1,x2,midx+1,x2,y,y));
		else ans=gcd(update1(n->cr,midx+1,x2,x,y,v),query1(n->cl,x1,midx,x1,midx,y,y));
	}
	return update2(n->cud,0,C,y,ans);
}
int main()
{
	freopen("IN.txt","r",stdin);
	freopen("OUT.txt","w",stdout);
	while(scanf("%lld%lld%lld",&R,&C,&N)==3)
	{
		R--,C--;
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
				printf("%lld\n",query1(root,0,R,min(p,u),max(p,u),min(q,v),max(q,v)));
			}
		}
	}
	return 0;
}
