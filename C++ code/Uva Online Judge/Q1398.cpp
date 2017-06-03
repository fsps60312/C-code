#include<cstdio>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,W,H,N,UP,DOWN,LEFT,RIGHT;
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
bool AtRange(int v,int l,int r){return v>=l&&v<=r;}
struct Meteor
{
	Point p,v;
	void canf()
	{
		scanf("%d%d%d%d",&p.x,&p.y,&v.x,&v.y);
		p.x*=10,p.y*=10;
		getmax(UP,p.y);
		getmin(DOWN,p.y);
		getmax(RIGHT,p.x);
		getmin(LEFT,p.x);
	}
	Point GetInterval()
	{
		int inx,outx,iny,outy;
		if(v.x!=0)
		{
			inx=(v.x>0?0:W)-p.x;
			outx=(v.x>0?W:0)-p.x;
			if(inx%v.x)inx=inx/v.x+1;
			else inx=inx/v.x+1;
			if(outx%v.x)outx=outx/v.x;
			else outx=outx/v.x-1;
		}
		else if(AtRange(p.x,1,W-1))inx=-2147483647,outx=2147483647;
		else return Point(-1,-1);
		if(v.y!=0)
		{
			iny=(v.y>0?0:H)-p.y;
			outy=(v.y>0?H:0)-p.y;
			if(iny%v.y)iny=iny/v.y+1;
			else iny=iny/v.y+1;
			if(outy%v.y)outy=outy/v.y;
			else outy=outy/v.y-1;
		}
		else if(AtRange(p.y,1,H-1))iny=-2147483647,outy=2147483647;
		else return Point(-1,-1);
		//printf("sz(%d,%d)p(%d,%d)v(%d,%d)x(%d,%d)y(%d,%d)\n",W,H,p.x,p.y,v.x,v.y,inx,outx,iny,outy);
		return Point(max(inx,iny),min(outx,outy));
	}
}METEOR[100000];
struct Lt
{
	int v[20000000],tag[20000000];
	void putdown(int id)
	{
		if(!tag[id])return;
		v[id*2]+=tag[id];
		v[id*2+1]+=tag[id];
		tag[id*2]=tag[id*2+1]=tag[id];
		tag[id]=0;
	}
	void build(int id,int l,int r)
	{
		v[id]=tag[id]=0;
		if(l==r)return;
		int mid=(l+r)/2;
		build(id*2,l,mid);
		build(id*2+1,mid+1,r);
	}
	void add(int id,int l,int r,int L,int R)
	{
		if(l>=L&&r<=R)
		{
			v[id]++;
			tag[id]++;
			return;
		}
		else if(l>R||r<L)return;
		int mid=(l+r)/2;
		putdown(id);
		add(id*2,l,mid,L,R);
		add(id*2+1,mid+1,r,L,R);
		getmax(v[id],v[id*2]);
		getmax(v[id],v[id*2+1]);
	}
}LT;
int solve()
{
	int mxt=max(UP-DOWN,RIGHT-LEFT);
	LT.build(1,0,mxt);
	for(int i=0;i<N;i++)
	{
		Point p=METEOR[i].GetInterval();
		//printf("Meteor%d: %d, %d\n",i,p.x,p.y);
		if(p.x!=-1)LT.add(1,0,mxt,p.x,p.y);
	}
	return LT.v[1];
}
int main()
{
	//freopen("in.txt","r",stdin);
	//printf("%d%d",(int)1.5,(int)-1.5);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&W,&H,&N);
		W*=10,H*=10;
		UP=H,RIGHT=W,LEFT=DOWN=0;
		for(int i=0;i<N;i++)METEOR[i].canf();
		printf("%d\n",solve());
	}
	return 0;
}
