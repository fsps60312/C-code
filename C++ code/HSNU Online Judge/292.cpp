#include<cstdio>
int gcd(int a,int b)
{
	if(a==0)return b;
	if(b==0)return a;
	return gcd(b,a%b);
}
struct Node
{
	Node *cl,*cr,*cu,*cd;
	int px,py,pv;
	Node()
	{
		px=-2;
		cl=cr=cu=cd=NULL;
	}
};
Node *root=NULL;
int pv(Node *a){return a?a->pv:0;}
void update(Node* &n,int x1,int x2,int y1,int y2,int x,int y,int v)
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
		int nx=n->px,ny=n->py,nv=n->pv;
		n->px=-1;
		int midx=(x1+x2)/2,midy=(y1+y2)/2;
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
	int midx=(x1+x2)/2,midy=(y1+y2)/2;
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
bool inrange(int v,int l,int r){return v>=l&&v<=r;}
int query(Node *n,int x1,int x2,int y1,int y2,int qx1,int qx2,int qy1,int qy2)
{
	if(!n)return 0;
	if(x1>qx2||x2<qx1||y1>qy2||y2<qy1)return 0;
	if(x1>=qx1&&x2<=qx2&&y1>=qy1&&y2<=qy2)return n->pv;
	if(n->px!=-1)
	{
		if(inrange(n->px,qx1,qx2)&&inrange(n->py,qy1,qy2))return n->pv;
		else return 0;
	}
	int midx=(x1+x2)/2;
	int ql=query(n->cl,x1,midx,y1,y2,qx1,qx2,qy1,qy2);
	int qr=query(n->cr,midx+1,x2,y1,y2,qx1,qx2,qy1,qy2);
	int midy=(y1+y2)/2;
	int qu=query(n->cu,x1,x2,y1,midy,qx1,qx2,qy1,qy2);
	int qd=query(n->cd,x1,x2,midy+1,y2,qx1,qx2,qy1,qy2);
	return gcd(gcd(ql,qr),gcd(qu,qd));
}
int R,C,N;
int main()
{
	//freopen("IN.txt","r",stdin);
	while(scanf("%d%d%d",&R,&C,&N)==3)
	{
		root=NULL;
		for(int i=0;i<N;i++)
		{
			int t;
			scanf("%d",&t);
			if(t==1)
			{
				int p,q,k;scanf("%d%d%d",&p,&q,&k);
				update(root,0,R,0,C,p,q,k);
			}
			else
			{
				int p,q,u,v;scanf("%d%d%d%d",&p,&q,&u,&v);
				printf("%d\n",query(root,0,R,0,C,p,u,q,v));
			}
		}
		return 0;
	}
	return 0;
}
