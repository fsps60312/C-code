#include<cstdio>
#define LL long long
bool inrange(int v,int l,int r){return v>=l&&v<=r;}
LL cal_gcd(LL a,LL b){return b==0?a:cal_gcd(b,a%b);}
LL gcd(LL a,LL b)
{
	if(!a||!b)return a?a:b;
	return cal_gcd(a,b);
}
struct Node2
{
	Node2 *cu,*cd;
	int py;
	LL pv;
	Node2(int y,LL v):py(y),pv(v)
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
int R,C,N;
LL pv(Node2 *a){return a?a->pv:0LL;}
LL query2(Node2* n,int y1,int y2,int qy1,int qy2)
{
	if(!n)return 0LL;
	if(y1>qy2||y2<qy1)return 0LL;
	if(n->py!=-1)
	{
		if(inrange(n->py,qy1,qy2))return n->pv;
		else return 0LL;
	}
	if(y1>=qy1&&y2<=qy2)return n->pv;
	int midy=(y1+y2)/2;
	LL qu=query2(n->cu,y1,midy,qy1,qy2);
	LL qd=query2(n->cd,midy+1,y2,qy1,qy2);
	return gcd(qu,qd);
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
LL query1(Node1* n,int x1,int x2,int qx1,int qx2,int qy1,int qy2)
{
	if(!n)return 0;
	if(x1>qx2||x2<qx1)return 0;
	if(x1>=qx1&&x2<=qx2)return query2(n->cud,0,C,qy1,qy2);
	int midx=(x1+x2)/2;
	LL ql=query1(n->cl,x1,midx,qx1,qx2,qy1,qy2);
	LL qr=query1(n->cr,midx+1,x2,qx1,qx2,qy1,qy2);
	return gcd(ql,qr);
}
LL update2(Node2* &n,int y1,int y2,int y,LL v)
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
		int ny=n->py;
		LL nv=n->pv;
		n->py=-1;
		update2(n,y1,y2,ny,nv);
	}
	int midy=(y1+y2)/2;
	if(y<=midy)update2(n->cu,y1,midy,y,v);
	else update2(n->cd,midy+1,y2,y,v);
	n->pv=gcd(pv(n->cu),pv(n->cd));
	return v;
}
LL update1(Node1* &n,int x1,int x2,int x,int y,LL v)
{
	if(!n)
	{
		n=new Node1();
	}
	LL ans=v;
	if(x1<x2)
	{
		int midx=(x1+x2)/2;
		if(x<=midx)ans=gcd(update1(n->cl,x1,midx,x,y,v),query1(n->cr,midx+1,x2,midx+1,x2,y,y));
		else ans=gcd(update1(n->cr,midx+1,x2,x,y,v),query1(n->cl,x1,midx,x1,midx,y,y));
	}
	return update2(n->cud,0,C,y,ans);
}
int main()
{
	//freopen("IN.txt","r",stdin);
	//freopen("OUT.txt","w",stdout);
	while(scanf("%d%d%d",&R,&C,&N)==3)
	{
		R--,C--;
		root=NULL;
		int p,q,u,v;
		LL k;
		for(int i=0;i<N;i++)
		{
			int t;
			scanf("%d",&t);
			if(t==1)
			{
				scanf("%d%d%lld",&p,&q,&k);
				update1(root,0,R,p,q,k);
			}
			else
			{
				scanf("%d%d%d%d",&p,&q,&u,&v);
				printf("%lld\n",query1(root,0,R,min(p,u),max(p,u),min(q,v),max(q,v)));
			}
		}
	}
	return 0;
}
