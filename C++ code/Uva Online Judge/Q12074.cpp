#include<cstdio>
#include<vector>
//#include<cassert>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Bst
{
	struct Node2D
	{
		Node2D *ch[2];
		int mx;
		Node2D():ch{NULL,NULL},mx(0){}
	};
	struct Node1D
	{
		Node1D *ch[2];
		Node2D *ch2d;
		Node1D():ch{NULL,NULL},ch2d(NULL){}
	}*ROOT;
	Node2D *Lch(Node2D* &o){return o?o->ch[0]:NULL;}
	Node2D *Rch(Node2D* &o){return o?o->ch[1]:NULL;}
	int Mx(Node2D* &o){return o?o->mx:0;}
	void clear(){ROOT=NULL;}
	void ModifyLeaf(Node2D* &o,const int l,const int r,const int y,const int value)
	{
		assert(l<=y&&y<=r);
//		printf("y=%d,(%d,%d)leaf\n",y,l,r);
		if(!o)o=new Node2D();
		if(l==r){getmax(o->mx,value);return;}
		const int mid=(l+r)/2;
		if(y<=mid)ModifyLeaf(o->ch[0],l,mid,y,value);
		else ModifyLeaf(o->ch[1],mid+1,r,y,value);
		o->mx=max(Mx(o->ch[0]),Mx(o->ch[1]));
	}
	void Modify2D(Node2D* &o,Node2D *lch,Node2D *rch,const int l,const int r,const int y)
	{
		assert(l<=y&&y<=r);
//		printf("y=%d,(%d,%d)\n",y,l,r);
		assert(lch||rch);
		if(!o)o=new Node2D();
		if(l==r){o->mx=max(Mx(lch),Mx(rch));return;}
		const int mid=(l+r)/2;
		if(y<=mid)Modify2D(o->ch[0],Lch(lch),Lch(rch),l,mid,y);
		else Modify2D(o->ch[1],Rch(lch),Rch(rch),mid+1,r,y);
		o->mx=max(Mx(o->ch[0]),Mx(o->ch[1]));
	}
	void Modify1D(Node1D* &o,const int l,const int r,const int x,const int y,const int value)
	{
		assert(l<=x&&x<=r);
//		printf("x=%d,(%d,%d)\n",x,l,r);
		if(!o)o=new Node1D();
		if(l==r){ModifyLeaf(o->ch2d,0,2000000,y,value);return;}
		const int mid=(l+r)/2;
		if(x<=mid)Modify1D(o->ch[0],l,mid,x,y,value);
		else Modify1D(o->ch[1],mid+1,r,x,y,value);
		Modify2D(o->ch2d,o->ch[0]?o->ch[0]->ch2d:NULL,o->ch[1]?o->ch[1]->ch2d:NULL,0,2000000,y);
	}
	void Modify(const int x,const int y,const int value){Modify1D(ROOT,0,2000000,x,y,value);}
	int Query2D(Node2D* &o,const int l,const int r,const int y1,const int y2)
	{
		assert(y1<=y2);
		if(!o)return 0;
		if(l>y2||r<y1)return 0;
		if(y1<=l&&r<=y2)return o->mx;
		const int mid=(l+r)/2;
		return max(Query2D(o->ch[0],l,mid,y1,y2),Query2D(o->ch[1],mid+1,r,y1,y2));
	}
	int Query1D(Node1D* &o,const int l,const int r,const int x1,const int x2,const int y1,const int y2)
	{
		assert(x1<=x2);
		if(!o)return 0;
		if(l>x2||r<x1)return 0;
		if(x1<=l&&r<=x2)return Query2D(o->ch2d,0,2000000,y1,y2);
		const int mid=(l+r)/2;
		return max(Query1D(o->ch[0],l,mid,x1,x2,y1,y2),Query1D(o->ch[1],mid+1,r,x1,x2,y1,y2));
	}
	int Query(const int x1,const int x2,const int y1,const int y2){return Query1D(ROOT,0,2000000,x1,x2,y1,y2);}
}BST;
struct Land
{
	int x,y,tasty,count;
	Land(const int _x,const int _y,const int _t,const int _c):x(_x),y(_y),tasty(_t),count(_c){}
	bool operator<(const Land &l)const{return tasty<l.tasty;}
};
vector<Land>LAND;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d",&N)==1);
		LAND.clear();
		for(int i=0,x,y,w,l;i<N;i++)
		{
			assert(scanf("%d%d%d%d",&x,&y,&w,&l)==4);
			LAND.push_back(Land(x+y,x-y+1000000,w,l));
		}
		sort(LAND.begin(),LAND.end());
		BST.clear();
		int ans=0;
		for(const Land &l:LAND)
		{
			const int dis=l.count;
//			puts("a");
			const int mx=BST.Query(l.x-dis,l.x+dis,l.y-dis,l.y+dis);
//			puts("b");
			BST.Modify(l.x,l.y,mx+1);
//			puts("c");
			getmax(ans,mx+1);
		}
		static int kase=1;
		printf("Case %d: %d\n",kase++,ans);
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
